#include "../include/hashtable.h"

typedef struct ht {
	size_t capacity;
	int length;
	hte_t *entries[MAX_CAPACITY];
} ht_t;

typedef struct hte {
	char *key;
	int value;
} hte_t;

ht_t *ht_create(void) {
	ht_t *ht;
	ht = (ht_t*) malloc(sizeof(ht_t));
	
	if (!ht) error_t("error while allocated hashtable");

	ht->capacity = MAX_CAPACITY;
	ht->length = 0;
	
	return ht;
}

hte_t *hte_create_entry(const char *key, int value) {
	hte_t *hte;
	hte = (hte_t*) malloc(sizeof(hte_t));
	
	if (!hte) error_t("error while allocated hash entry");
	
	hte->key = (char*) malloc(strlen(key) + 1);
	
	if (!hte->key) error_t("error while allocanting key");
	
	memcpy(hte->key, key, strlen(key) + 1);
	hte->value = value;
	
	return hte;
}

void ht_insert(ht_t *ht, hte_t *hte) {
	if (!ht) error_t("ht not created");
	
	if (ht->length == ht->capacity) error_t("ht is full");
	
	int hash = hash_key(hte->key) % MAX_CAPACITY;
	
	if (ht->entries[hash] != NULL) {
		for (; hash < ht->capacity; hash++) if (ht->entries[hash] == NULL) {
				ht->entries[hash] = hte;
				return;
			}
		
		hash = hash_key(hte->key) % MAX_CAPACITY;
		
		if (hash == 0) error_t("colision");
		else {
				int i = 0;
				for (; i < hash; i++) if (ht->entries[i] == NULL) {
						ht->entries[i] = hte;
						return;
					}
				
				error_t("colision 2 loop");
			}
		
	}
	else ht->entries[hash] = hte;
	
	ht->length++;
}

static uint64_t hash_key(const char* key) {
    uint64_t hash = FNV_OFFSET;
    
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    
    return hash;
}

// only for testing
void ht_printall(ht_t *ht) {
	int i = 0;
	
	for (; i < ht->capacity; i++) if (ht->entries[i]) printf("%d %s\n", i, ht->entries[i]->key);
}

void ht_destroy(ht_t *ht) {
	free(ht);
}

// first call hte_destroy before call ht_destroy
void hte_destroy(ht_t *ht) {
	int i = 0;
	
	for (; i < ht->capacity; i++) {
		if (ht->entries[i]) {
			free(ht->entries[i]->key);
			free(ht->entries[i]);
		}
	}
	
}

void get(ht_t *ht, const char *key) {
	int hash = hash_key(key) % MAX_CAPACITY;

	printf("%d\n", ht->entries[hash]->value);
}
