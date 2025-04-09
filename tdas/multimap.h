#ifndef MULTIMAP_H
#define MULTIMAP_H
#include "map.h"
#include <stdio.h>
#include <stdlib.h>

typedef Map MultiMap;

MultiMap *multimap_create(int (*is_equal)(void *key1, void *key2)){
  return map_create(is_equal);
}

MultiMap *sorted_multimap_create(int (*lower_than)(void *key1, void *key2)){
  return sorted_map_create(lower_than);
}

void multimap_insert(MultiMap *map, void *key, void *value);

MapPair *multimap_remove(MultiMap *map, void *key){
  return map_remove(map, key);
}

MapPair *multimap_search(MultiMap *map, void *key){
  return map_search(map, key);
}

MapPair *multimap_first(MultiMap *map){
  return map_first(map);
}

MapPair *multimap_next(MultiMap *map){
  return map_next(map);
}

void multimap_clean(MultiMap *map){
  return map_clean(map);
}

#endif /* MULTIMAP_H */