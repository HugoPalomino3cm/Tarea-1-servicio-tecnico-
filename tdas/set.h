#ifndef SET_H
#define SET_H
#include "map.h"
#include <stdio.h>
#include <stdlib.h>

typedef Map Set;

Map *set_create(int (*is_equal)(void *key1, void *key2)) {
  map_create(is_equal);
}

Map *sorted_set_create(int (*lower_than)(void *key1, void *key2)){
  sorted_map_create(lower_than);
}

void set_insert(Set *set, void *value) { map_insert(set, value, value); }

void *set_remove(Set *set, void *value) { return map_remove(set, value); }

void *set_search(Set *set, void *value) { return map_search(set, value); }

void set_clean(Set *set) { map_clean(set); }

#endif /* SET_H */