/*
 * syscallminimal.c
 *
 *  Created on: 16-Sept-2026
 *      Author: manoj_kumar
 */

#ifndef SYSCALLMINIMAL_C_
#define SYSCALLMINIMAL_C_

#include <sys/stat.h>

int _close(int file) {
    return -1;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _read(int file, char *ptr, int len) {
    return 0;
}

int _write(int file, char *ptr, int len) {
    return len;
}


#endif /* SYSCALLMINIMAL_C_ */
