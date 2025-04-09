#include "tdas/list.h"
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("     Sistema de Servicio Técnico");
  puts("========================================");

  puts("1) Registrar cliente");
  puts("2) Asignar prioridad a cliente");
  puts("3) Mostrar lista de espera");
  puts("4) Atender al siguiente cliente");
  puts("5) Mostrar clientes por prioridad");
  puts("6) Salir");
}

typedef struct{
  char ID[10];            // ID del cliente
  char descripcion[100];  // Descripción del problema del dispositivo
  unsigned short prioridad; // Prioridad del servicio
  time_t hora_ingresada;
} tipoRegistro;

void registrar_Cliente(List *clientes) {
  printf("Registrar nuevo cliente\n");
  tipoRegistro *registroNuevo = malloc(sizeof(tipoRegistro));
  if (registroNuevo == NULL) return;
  printf("Ingrese ID del cliente\n");
  scanf(" %9[^\n]s", &registroNuevo->ID);
  printf("Ingrese descripción del problema del dispositivo\n");
  scanf(" %99[^\n]s", &registroNuevo->descripcion);
  
  time(&registroNuevo->hora_ingresada);
  registroNuevo->prioridad = 3; // Valor por defecto de prioridad

  list_pushBack(clientes, registroNuevo);
}

void mostrar_lista_clientes(List *clientes) {
  printf("Clientes en espera: \n\n");
  tipoRegistro *actual = list_first(clientes);
  while(actual != NULL){
    printf("ID: %s\n", actual->ID);
    printf("Descripción del problema: %s\n", actual->descripcion);
    printf("Prioridad: %d\n\n", actual->prioridad);
    printf("Hora ingresada %s",ctime(&actual->hora_ingresada));
    actual = list_next(clientes);
  }
}

void asignar_prioridad(List *clientes) {
  unsigned short prioridad_nueva;
  char ID[10];
  printf("Ingrese el ID del cliente que quiere modificar: ");
  scanf(" %9[^\n]", ID);
  printf("Ingrese la nueva prioridad (1: alta, 2: media, 3: baja): ");
  scanf("%hu", &prioridad_nueva);

  tipoRegistro *actual = list_first(clientes);

  while(actual != NULL){
    if(strcmp(actual->ID, ID) == 0) break;
    actual = list_next(clientes);
  }

  if(actual != NULL){
    actual->prioridad = prioridad_nueva;
    list_popCurrent(clientes);
    printf("Prioridad del cliente actualizada con éxito.\n");
  }
  else{
    printf("Cliente no encontrado.\n");
    return;
  }

  tipoRegistro *aux = list_first(clientes);

  while(aux != NULL){
    if(aux->prioridad > prioridad_nueva){
      if(aux == list_first(clientes)){
        list_pushFront(clientes, actual);
      } else {
        list_pushCurrent(clientes, actual);
      }
      return;
    }
    aux = list_next(clientes);
  }

  list_pushBack(clientes, actual);
}

int main() {
  char opcion;
  List *clientes = list_create(); // Lista para gestionar clientes
  
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion); // Nota el espacio antes de %c para consumir el
                           // newline anterior

    switch (opcion) {
    case '1':
      registrar_Cliente(clientes);
      break;
    case '2':
      asignar_prioridad(clientes);
      break;
    case '3':
      mostrar_lista_clientes(clientes);
      break;
    case '4':
      // Lógica para atender al siguiente cliente
      break;
    case '5':
      // Lógica para mostrar clientes por prioridad
      break;
    case '6':
      puts("Saliendo del sistema de gestión de servicio técnico...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();

  } while (opcion != '6');

  // Liberar recursos, si es necesario
  list_clean(clientes);

  return 0;
}
