#include "../include/dock.h"
#include "../include/token.h"
#include "../include/parser.h"

dock_t *init_dock_t(size_t size) {
	dock_t *dock = (dock_t*) malloc(sizeof(dock_t));
	
	if (!dock) error_t("error while creating dock");
	
	dock->ships = NULL;
	dock->max_size = size;
	dock->length = 0;
	
	return dock;
}

int insert_ship_t(dock_t *dock, void *item, enum TYPE_ITEM type) {	
	if (dock->length == dock->max_size) return 0;

	if (dock->ships == NULL) dock->ships = malloc(sizeof(ship_t));
	
	if (dock->length == 0) goto end;
	
	void *new_size = realloc(dock->ships, (dock->length + 1) * sizeof(ship_t));
	dock->ships = new_size;
	
	end:
	dock->ships[dock->length].item = item;
	dock->ships[dock->length].type = type;
	dock->length += 1;
	
	return 1;
}

void destroy_dock(dock_t *dock) {
	if (dock->length == 0) {
		free(dock);
		return;	
	}
	
	int tokens_i = 0;
	
	for (int i = 0; i < dock->length; i++) {
		switch (dock->ships[i].type) {
			case 0:
				free_token_t(dock->ships[i].item);
				break;
			case 1:
				tokens_i = i;
				break;
			case 2:
				fclose(dock->ships[i].item);
				break;
			case 3:
				free_ll(dock->ships[i].item);
				break;
			default:
				break;
		}
	}
	
	free(dock->ships[tokens_i].item);
	free_dock(dock);
}

static void free_dock(dock_t *dock) {
	free(dock->ships);
	free(dock);
}
