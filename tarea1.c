#include "tdas/list.h" 
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct {
  char idCliente[10];
  char descripcionProblema[100];
  char nivelPrioridad[10];
  time_t tiempoRegistro;
} Cliente;

void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("===== Sistema de Servicio Técnico =====");
  puts("1) Registrar cliente");
  puts("2) Asignar prioridad");
  puts("3) Mostrar lista de espera");
  puts("4) Atender cliente");
  puts("5) Buscar cliente por ID");
  puts("6) Salir");
}

int obtenerValorPrioridad(const char *prioridad) {
  if (strcmp(prioridad, "alta") == 0) return 1;
  if (strcmp(prioridad, "media") == 0) return 2;
  return 3; // baja
}

void convertirTextoAMinusculas(char *texto) {
  for (int i = 0; texto[i]; i++) texto[i] = tolower(texto[i]);
}

int compararClientesPorPrioridadYHora(void *a, void *b) {
  Cliente *clienteA = (Cliente *)a;
  Cliente *clienteB = (Cliente *)b;

  int prioridadA = obtenerValorPrioridad(clienteA->nivelPrioridad);
  int prioridadB = obtenerValorPrioridad(clienteB->nivelPrioridad);

  if (prioridadA != prioridadB)
    return prioridadA < prioridadB;

  return clienteA->tiempoRegistro < clienteB->tiempoRegistro;
}



void registrarNuevoCliente(List *listaClientes) {
  char idIngresado[10];
  printf("\nIngrese ID: ");
  scanf(" %9[^\n]", idIngresado); getchar();
  
  Cliente *clienteActual = list_first(listaClientes);

  while (clienteActual != NULL) {
    if (strcmp(clienteActual->idCliente, idIngresado) == 0) break;
    clienteActual = list_next(listaClientes);
  }
  
  if (clienteActual != NULL){
    return;
  }

  Cliente *nuevoCliente = malloc(sizeof(Cliente));
  if (!nuevoCliente) return;

  strcpy(nuevoCliente->idCliente, idIngresado);
  printf("Descripción del problema: ");
  scanf(" %99[^\n]", nuevoCliente->descripcionProblema); getchar();

  time(&nuevoCliente->tiempoRegistro);
  strcpy(nuevoCliente->nivelPrioridad, "baja");

  list_sortedInsert(listaClientes, nuevoCliente, compararClientesPorPrioridadYHora);
  printf("Cliente registrado con prioridad 'baja'.\n");
  presioneTeclaParaContinuar();
}


void mostrarListaClientes(List *listaClientes) {
  limpiarPantalla();
  Cliente *cliente = list_first(listaClientes);
  if (!cliente) {
    printf("No hay clientes en espera.\n");
  }

  while (cliente) {
    char horaFormateada[9];
    strftime(horaFormateada, sizeof(horaFormateada), "%H:%M:%S", localtime(&cliente->tiempoRegistro));
    printf("ID: %s\nDescripción: %s\nPrioridad: %s\nHora de ingreso: %s\n\n",
           cliente->idCliente, cliente->descripcionProblema, cliente->nivelPrioridad, horaFormateada);
    cliente = list_next(listaClientes);
  }
  presioneTeclaParaContinuar();
}

void actualizarPrioridadCliente(List *listaClientes) {
  char idBuscado[10], nuevaPrioridad[10];
  printf("ID del cliente: ");
  scanf(" %9[^\n]", idBuscado); 
  getchar();
  printf("Nueva prioridad (alta, media, baja): ");
  scanf(" %9[^\n]", nuevaPrioridad); 
  getchar();
  convertirTextoAMinusculas(nuevaPrioridad);

  if (strcmp(nuevaPrioridad, "alta") && strcmp(nuevaPrioridad, "media") && strcmp(nuevaPrioridad, "baja")) {
    printf("Prioridad inválida.\n");
    presioneTeclaParaContinuar();
    return;
  }

  Cliente *cliente = list_first(listaClientes);
  while (cliente) {
    if (strcmp(cliente->idCliente, idBuscado) == 0) {
      list_popCurrent(listaClientes);
      strcpy(cliente->nivelPrioridad, nuevaPrioridad);
      list_sortedInsert(listaClientes, cliente, compararClientesPorPrioridadYHora);
      printf("Prioridad actualizada.\n");
      presioneTeclaParaContinuar();
      return;
    }
    cliente = list_next(listaClientes);
  }

  printf("Cliente no encontrado.\n");
  presioneTeclaParaContinuar();
}

void atenderClienteConMayorPrioridad(List *listaClientes) {
  Cliente *cliente = list_first(listaClientes);
  if (!cliente) {
    printf("No hay clientes en espera.\n");
    presioneTeclaParaContinuar();
    return;
  }

  list_popFront(listaClientes);
  printf("Cliente atendido:\nID: %s\nDescripción: %s\nPrioridad: %s\n",
         cliente->idCliente, cliente->descripcionProblema, cliente->nivelPrioridad);
  free(cliente);
  presioneTeclaParaContinuar();
}

void buscarClientePorID(List *listaClientes) {
  char idBuscado[10];
  printf("Ingrese el ID del cliente: ");
  scanf(" %9[^\n]", idBuscado); getchar();

  Cliente *cliente = list_first(listaClientes);
  while (cliente) {
    if (strcmp(cliente->idCliente, idBuscado) == 0) {
      char horaFormateada[9];
      strftime(horaFormateada, sizeof(horaFormateada), "%H:%M:%S", localtime(&cliente->tiempoRegistro));
      printf("\nCliente encontrado:\n");
      printf("ID: %s\n", cliente->idCliente);
      printf("Descripción: %s\n", cliente->descripcionProblema);
      printf("Prioridad: %s\n", cliente->nivelPrioridad);
      printf("Hora de registro: %s\n", horaFormateada);
      presioneTeclaParaContinuar();
      return;
    }
    cliente = list_next(listaClientes);
  }

  printf("No se encontró ningún cliente con ese ID.\n");
  presioneTeclaParaContinuar();
}

int main() {
  List *listaClientes = list_create();
  char opcion;

  do {
    mostrarMenuPrincipal();
    printf("Opción: ");
    scanf(" %c", &opcion); getchar();

    switch (opcion) {
      case '1': 
        registrarNuevoCliente(listaClientes); 
        break;
      case '2': 
        actualizarPrioridadCliente(listaClientes); 
        break;
      case '3': 
        mostrarListaClientes(listaClientes); 
        break;
      case '4': 
        atenderClienteConMayorPrioridad(listaClientes); 
        break;
      case '5': 
        buscarClientePorID(listaClientes); 
        break;
      case '6': 
        puts("Saliendo del sistema de gestión de servicio técnico...");
        break;
      default:
        puts("Opción no válida. Por favor, intente de nuevo.");
    }
  } while (opcion != '6');

  list_clean(listaClientes);
  return 0;
}
