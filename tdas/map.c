#include "map.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>

struct Map {
  int (*lower_than)(void *key1, void *key2);
  int (*is_equal)(void *key1, void *key2);
  List *ls;
};

typedef Map Map;

// Variable global para almacenar la función de comparación actual
int (*current_lt)(void *, void *) = NULL;

int pair_lt(void *pair1, void *pair2) {
  return (current_lt(((MapPair *)pair1)->key, ((MapPair *)pair2)->key));
}

Map *sorted_map_create(int (*lower_than)(void *key1, void *key2)) {
  Map *newMap = (Map *)malloc(sizeof(Map));
  newMap->lower_than = lower_than;
  newMap->is_equal = NULL;
  newMap->ls = list_create();

  return newMap;
}

Map *map_create(int (*is_equal)(void *key1, void *key2)) {
  Map *newMap = (Map *)malloc(sizeof(Map));
  newMap->lower_than = NULL;
  newMap->is_equal = is_equal;
  newMap->ls = list_create();

  return newMap;
}


void multimap_insert(Map *map, void *key, void *value) {
  MapPair *pair = (MapPair *)malloc(sizeof(MapPair));
  pair->key = key;
  pair->value = value;

  if (map->lower_than) {
    current_lt = map->lower_than;
    list_sortedInsert(map->ls, pair, pair_lt);
  } else
    list_pushBack(map->ls, pair);
}

void map_insert(Map *map, void *key, void *value) {
  if (map_search(map, key) != NULL) return;
  multimap_insert(map, key, value);
}

int _is_equal(Map *map, MapPair *pair, void *key) {
  return ((map->is_equal && map->is_equal(pair->key, key)) ||
          (map->lower_than && !map->lower_than(pair->key, key) &&
           !map->lower_than(key, pair->key)));
}

MapPair *map_remove(Map *map, void *key) {
  for (MapPair *pair = list_first(map->ls); pair != NULL;
       pair = list_next(map->ls))
    if (_is_equal(map, pair, key)) {
      list_popCurrent(map->ls);
      return pair;
    }
  return NULL;
}

MapPair *map_search(Map *map, void *key) {
  for (MapPair *pair = list_first(map->ls); pair != NULL;
       pair = list_next(map->ls)) {
    if (_is_equal(map, pair, key))
      return pair;
  }
  return NULL;
}

MapPair *map_first(Map *map) { return list_first(map->ls); }

MapPair *map_next(Map *map) { return list_next(map->ls); }

void map_clean(Map *map) { list_clean(map->ls); }
