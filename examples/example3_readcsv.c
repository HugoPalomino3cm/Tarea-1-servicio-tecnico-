// Para compilar:  gcc tdas/*.c examples/example3_readcvs.c -o test
// Para ejecutar: ./test

#include "../tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 100

char **leer_linea_csv(FILE *archivo, char separador) {
  static char linea[MAX_LINE_LENGTH];
  static char *campos[MAX_FIELDS];
  char *ptr, *start;
  int idx = 0;

  if (fgets(linea, MAX_LINE_LENGTH, archivo) == NULL) {
    return NULL; // No hay más líneas para leer
  }

  ptr = start = linea;
  while (*ptr) {
    if (idx >= MAX_FIELDS - 1)
      break;

    if (*ptr == '\"') { // Inicio de un campo entrecomillado
      start = ++ptr;    // Saltar la comilla inicial
      while (*ptr && !(*ptr == '\"' && *(ptr + 1) == separador))
        ptr++;
    } else { // Campo sin comillas
      start = ptr;
      while (*ptr && *ptr != separador)
        ptr++;
    }

    if (*ptr) {
      *ptr = '\0'; // Reemplazar comilla final o separador por terminación
      ptr++;
      if (*ptr == separador)
        ptr++;
    }

    // Quitar comilla final si existe
    if (*(ptr - 2) == '\"') {
      *(ptr - 2) = '\0';
    }

    campos[idx++] = start;
  }

  campos[idx] = NULL; // Marcar el final del array
  return campos;
}

typedef struct {
  char autor[30];
  char titulo[30];
  char descripcion[100];
  int año;
} Libro;

int main() {
  FILE *archivo = fopen("examples/files/libros.csv", "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return 1;
  }

  List *libros = list_create();

  char **campos;
  leer_linea_csv(archivo, '|'); // encabezados
  while ((campos = leer_linea_csv(archivo, '|')) != NULL) {
    Libro *libro = (Libro *)malloc(sizeof(Libro));
    strcpy(libro->autor, campos[0]);
    strcpy(libro->titulo, campos[1]);
    strcpy(libro->descripcion, campos[2]);
    libro->año = atoi(campos[3]);
    list_pushBack(libros, libro);
  }
  fclose(archivo);

  // mostrar en formato bonito
  for (Libro *libro = list_first(libros); libro != NULL;
       libro = list_next(libros)) {
    printf("Titulo: %s\n", libro->titulo);
    printf("Autor: %s\n", libro->autor);
    printf("Descripcion: %s\n", libro->descripcion);
    printf("Año: %d\n", libro->año);
    printf("\n");
  }

  return 0;
}
