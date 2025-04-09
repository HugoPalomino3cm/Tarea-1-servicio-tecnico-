#include "../tdas/map.h"
#include "../tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

List *split_string(const char *str, const char *delim) {
  List *result = list_create();
  char *token = strtok((char *)str, delim);

  while (token != NULL) {
    // Eliminar espacios en blanco al inicio del token
    while (*token == ' ') {
      token++;
    }

    // Eliminar espacios en blanco al final del token
    char *end = token + strlen(token) - 1;
    while (*end == ' ' && end > token) {
      *end = '\0';
      end--;
    }

    // Copiar el token en un nuevo string
    char *new_token = strdup(token);

    // Agregar el nuevo string a la lista
    list_pushBack(result, new_token);

    // Obtener el siguiente token
    token = strtok(NULL, delim);
  }

  return result;
}

int main() {
  char input[] = "Comedy, Action, Adventure,Thriller,Comedy,Romance";
  List *result = split_string(input, ",");

  for (char *str = list_first(result); str != NULL; str = list_next(result))
    printf("%s\n", str);

  return 0;
}
