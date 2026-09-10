#ifndef DOCK_H
#define DOCK_H	

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

enum TYPE_ITEM {
	TYPEITEM_TOKEN,
	TYPEITEM_TOKENS,
	TYPEITEM_FILE,
	TYPEITEM_LL
};

typedef struct dock dock_t;
typedef struct ship ship_t;

struct ship {
	void *item;
	enum TYPE_ITEM type;
};

struct dock {
	ship_t *ships;
	int max_size;
	int length;
};

dock_t *init_dock_t(size_t size);

int insert_ship_t(dock_t *dock, void *item, enum TYPE_ITEM type);

void destroy_dock(dock_t *dock);
static void free_dock(dock_t *dock);

#endif
