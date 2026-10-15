#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/utils.h"
#include "../include/dock.h"

extern dock_t *dock;

int error_t(const char *msg) {
	fprintf(stderr, "%s\n", msg);
	
	destroy_dock(dock);
	
	exit(EXIT_FAILURE);
}
