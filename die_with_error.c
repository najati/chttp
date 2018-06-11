#include <stdlib.h>
#include <stdio.h>

void die_with_error(const char* message) {
	perror(message);
	exit(1);
}