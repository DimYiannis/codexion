*This project has been created as part of the 42 curriculum by ydimitra.*

## Description

Codexion is a dining-philosophers variant where coder threads compete for shared USB dongles to compile quantum code. Each coder must acquire two adjacent dongles, compile for a fixed duration, then debug and refactor before repeating. A coder burns out if it does not start a compile within `time_to_burnout` milliseconds since its last compile (or simulation start). The simulation ends on first burnout or when every coder reaches the required compile count.

Two scheduling policies control which waiting coder gets a freed dongle:
- **fifo** — earliest request arrival wins
- **edf** — earliest deadline wins (deadline = `last_compile_start + time_to_burnout`); ties broken by coder ID

## Instructions

**Compile:**
```
make
```

**Run:**
```
./codexion <number_of_coders> <time_to_burnout> <time_to_compile> \
           <time_to_debug> <time_to_refactor> \
           <number_of_compiles_required> <dongle_cooldown> <scheduler>
```

All arguments are mandatory. `scheduler` must be `fifo` or `edf`. All time values are in milliseconds.

**Examples:**
```bash
# 5 coders, should never burn out
./codexion 5 800 200 200 200 5 0 fifo

# Cooldown stress with EDF scheduling
./codexion 3 2000 200 100 100 3 300 edf

# Force burnout — timeout too tight
./codexion 4 300 200 100 100 5 200 fifo
```

**Makefile targets:** `all`, `clean`, `fclean`, `re`

## Test Cases

### Clean run — no burnout

```bash
./codexion 5 800 200 200 200 5 0 fifo
```

5 coders with generous timing. All 5 complete 5 compiles; no burnout expected.

### Guaranteed burnout — structural impossibility

```bash
./codexion 1 800 200 200 200 5 0 fifo
```

1 coder, 1 dongle on the table — compiling requires 2. Structurally impossible; coder always burns out.

### Cooldown forces burnout

```bash
./codexion 2 800 200 100 100 5 300 fifo
```

300 ms cooldown: after coder A compiles, both dongles are locked until t+500 ms. A's next deadline is t+800 ms but the next available slot is t+1000 ms — burnout inevitable.

### EDF vs FIFO — scheduler comparison

```bash
./codexion 5 800 200 100 100 10 50 edf
./codexion 5 800 200 100 100 10 50 fifo
```

Same parameters, different policy. EDF grants contested dongles to the coder closest to burnout; FIFO grants by arrival order. Compare compile distribution across coders between both runs.

### Invalid input — rejected gracefully

```bash
./codexion 0 800 200 100 100 5 0 fifo    # zero coders
./codexion 3 800 200 100 100 5 0 random  # invalid scheduler
./codexion 3 800 abc 100 100 5 0 fifo    # non-integer argument
```

All three must print an error to stderr and exit non-zero with no simulation output.

### Stress — 50 coders

```bash
./codexion 50 800 200 100 100 3 0 fifo
```

50 coders, 3 compiles each. Tests mutex contention, min-heap performance under load, and absence of deadlock at scale.

## Resources

- [Dijkstra — Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX Threads Programming — Lawrence Livermore](https://hpc-tutorials.llnl.gov/posix/)
- [Earliest Deadline First Scheduling](https://en.wikipedia.org/wiki/Earliest_deadline_first_scheduling)
- [Min-Heap data structure](https://en.wikipedia.org/wiki/Binary_heap)
- [Queue in C](https://www.geeksforgeeks.org/c/queue-in-c/)
- [C Program to Implement Min Heap](https://www.geeksforgeeks.org/c/c-program-to-implement-min-heap/)
- [UNIX Threads in C](https://youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)

## Blocking cases handled

| Case | How it is handled |
|---|---|
| **Deadlock (Coffman conditions)** | Hold-and-wait broken by acquisition order: the last coder (ID = N) picks up the right dongle before the left, reversing the cycle and preventing circular wait |
| **Starvation** | EDF policy ensures the coder closest to burnout always wins a contested dongle; FIFO guarantees eventual service by strict arrival order |
| **Dongle cooldown** | Each dongle tracks `free_at = release_time + cooldown_ms`; `acquire_one` re-waits via `pthread_cond_wait` if the cooldown has not expired |
| **Burnout detection** | Monitor thread polls every 1 ms, compares `now - last_compile_start` against `time_to_burnout` for each coder; burnout is logged and the stop flag is set within ≤ 10 ms |
| **Log serialization** | All output goes through a single print mutex (`sim.print_mutex`); `log_event` acquires it before every `printf` so lines are never interleaved across threads |

## Thread synchronization mechanisms

**Dongle mutex + condition variable (`dongle.mutex` / `dongle.cond`)**
Each dongle has one mutex protecting `in_use`, `free_at`, and the scheduler queue. A coder calling `acquire_one` registers itself in the queue, then loops on `pthread_cond_wait` until three conditions hold simultaneously: dongle not in use, cooldown elapsed, and it is first in queue. `release_one` clears `in_use`, sets `free_at`, and broadcasts so all waiters re-evaluate. On stop, the monitor broadcasts to every dongle cond so blocked coders wake and exit cleanly.

**Scheduler queue (FIFO / EDF min-heap)**
Under `fifo`, the queue is a fixed-size circular array; enqueue appends, dequeue removes the front. Under `edf`, the queue is a min-heap ordered by deadline (`last_compile + time_to_burnout`), ties broken by coder ID. Both structures are allocated once per dongle and live inside `t_dongle.queue`. All access is under the dongle's mutex, so no additional lock is needed.

**State mutex (`coder.state_mutex`)**
Protects `last_compile` and `compile_count`, which are written by the coder thread and read by the monitor thread. The coder locks, writes, unlocks; the monitor locks, reads, unlocks — ensuring the monitor always sees a fully written value.

**Stop flag (`sim.stop` / `sim.print_mutex`)**
A single integer flag signals all threads to halt. The monitor sets it under `print_mutex` on burnout or completion, then broadcasts to all dongle conds. Coder threads check the flag via `get_stop()` at the top of their loop and inside `acquire_one`. `log_event` checks it inside the print mutex to prevent any output after the stop event.

**Print mutex (`sim.print_mutex`)**
Serializes all `printf` calls so log lines are never interleaved, and also protects the stop flag — `log_event` acquires it, checks stop, prints if still running, then releases.
