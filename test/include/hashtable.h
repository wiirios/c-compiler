#ifndef HASHTABLE_H
#define HASHTABLE_H	

#include "utils.h"

#define MAX_CAPACITY 8
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

typedef struct ht ht_t;
typedef struct hte hte_t;

ht_t *ht_create(void);

hte_t *hte_create_entry(const char *key, int value);

static uint64_t hash_key(const char* key);

void ht_printall(ht_t *ht);
void ht_insert(ht_t *ht, hte_t *hte);
void ht_destroy(ht_t *ht);
void hte_destroy(ht_t *ht);
void get(ht_t *ht, const char *key);

#endif
