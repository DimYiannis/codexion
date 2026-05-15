/* === header.h changes for v2c === */

/* ADD this prototype (acquire.c is a new file): */
int     acquire_pair(t_coder *coder, t_dongle *first, t_dongle *second);

/* KEEP all existing prototypes unchanged */

/* NOTE: acquire_one is now static void inside dongle.c — remove old prototype if present */
