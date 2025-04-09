// Para compilar:  gcc tdas/*.c examples/example1_list.c -o test
// Para ejecutar: ./test

#include "../tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char nombre[30];
  int edad;
} Persona;

int main() {
  // Crear una lista
  List *myList = list_create();
  if (myList == NULL) {
    printf("No se pudo crear la lista.\n");
    return 1;
  }

  // Agregar elementos
  Persona *persona = (Persona *)malloc(sizeof(Persona));
  strcpy(persona->nombre, "Juan");
  persona->edad = 25;
  list_pushBack(myList, persona);

  persona = (Persona *)malloc(sizeof(Persona));
  strcpy(persona->nombre, "Javiera");
  persona->edad = 31;
  list_pushBack(myList, persona);

  persona = (Persona *)malloc(sizeof(Persona));
  strcpy(persona->nombre, "Manuel");
  persona->edad = 25;
  list_pushBack(myList, persona);

  persona = (Persona *)malloc(sizeof(Persona));
  strcpy(persona->nombre, "Daniela");
  persona->edad = 29;
  list_pushBack(myList, persona);

  // Mostrar elementos (recorrido desde el principio)
  printf("Elementos de la lista: ");
  for (Persona *p = list_first(myList); p != NULL; p = list_next(myList))
    printf("%s, ", p->nombre);

  printf("\n");

  // Eliminar el primer y último elemento
  list_popFront(myList);
  list_popBack(myList);

  // Mostrar elementos después de las eliminaciones
  printf("Elementos después de popFront y popBack: ");
  for (Persona *p = list_first(myList); p != NULL; p = list_next(myList))
    printf("%s, ", p->nombre);

  printf("\n");

  // Limpiar la lista
  list_clean(myList);
  free(myList);
}