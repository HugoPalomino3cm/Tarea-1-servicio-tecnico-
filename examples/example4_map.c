// Para compilar:  gcc tdas/*.c examples/example4_map.c -o test
// Para ejecutar: ./test

#include "../tdas/map.h"
#include <stdio.h>
#include <stdlib.h>

int int_lower_than(void *key1, void *key2) {
  return *((int *)key1) < *((int *)key2);
}

int main() {
  Map *map = sorted_map_create(int_lower_than);
  char *values[] = {"value5", "value2", "value1", "value4", "value3"};
  int keys[] = {5, 2, 1, 4, 3};

  map_insert(map, &keys[0], values[0]);
  map_insert(map, &keys[1], values[1]);
  map_insert(map, &keys[2], values[2]);
  map_insert(map, &keys[3], values[3]);
  map_insert(map, &keys[4], values[4]);

  // Mostrar elementos del mapa
  for (MapPair *pair = map_first(map); pair != NULL; pair = map_next(map))
    printf("Key: %d, Value: %s\n", *((int *)pair->key), ((char *)pair->value));

  printf("Ingrese la clave que desea eliminar: ");
  int key;
  scanf("%d", &key);
  map_remove(map, &key);

  for (MapPair *pair = map_first(map); pair != NULL; pair = map_next(map))
    printf("Key: %d, Value: %s\n", *((int *)pair->key), ((char *)pair->value));

  printf("Ingrese la clave que desea buscar: ");
  scanf("%d", &key);
  char *value = map_search(map, &key);
  if (value != NULL)
    printf("%s\n ", value);
  else
    printf("No se encontró la clave %d\n", key);

  return 0;
}
