

#include "header.h"


int queue[256];
int count = 0;

void push_to_queue(int x)
{
  queue[count] = x;
  count++;
}

int pop_from_queue()
{
  int res = queue[0];
  int i;

  for (i = 0; i < count - 1; i++)
  {
    queue[i] = queue[i + 1];
  }
  count--;
  return res;
}

int main(int argc, char *argv[])
{
  push_to_queue(2);
  push_to_queue(5);
  push_to_queue(10);
  push_to_queue(15);

  int i;
  for (i=0; i < 4; i++)
  {
    printf("%d\n", pop_from_queue());
  }
  return 0;
}
