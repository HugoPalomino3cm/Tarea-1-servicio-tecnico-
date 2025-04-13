// Importo librerias y enlaces para poder ocupar funciones 
#include "tdas/list.h" 
#include "tdas/extra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Códigos de color ANSI para darle color a los textos
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define CYAN    "\x1b[36m"
#define BOLD    "\x1b[1m"


// Estructura de cliente 
typedef struct {
  char idCliente[10];
  char descripcionProblema[100];
  char nivelPrioridad[10];
  time_t tiempoRegistro;
} Cliente;

// Muestra el menú principal con 6 opciones, usando colores y limpiando la pantalla
void mostrarMenuPrincipal() {
  limpiarPantalla();

  printf(BOLD CYAN "\n======= " RESET "%sSistema de Servicio Técnico%s" BOLD CYAN " =======" "\n\n", YELLOW, RESET);

  printf(BOLD GREEN  " 1. " RESET "Registrar cliente\n");
  printf(BOLD GREEN  " 2. " RESET "Asignar prioridad\n");
  printf(BOLD GREEN  " 3. " RESET "Mostrar lista de espera\n");
  printf(BOLD GREEN  " 4. " RESET "Atender cliente\n");
  printf(BOLD GREEN  " 5. " RESET "Buscar cliente por ID\n");
  printf(BOLD RED    " 6. " RESET "Salir\n");

  printf("\n" BOLD "Seleccione una opción: " RESET);
}

// Convierte una prioridad (alta, media, baja) en un valor numérico (1, 2, 3) para ordenar
int obtenerValorPrioridad(const char *prioridad) {
  if (strcmp(prioridad, "alta") == 0) return 1;
  if (strcmp(prioridad, "media") == 0) return 2;
  return 3; // baja
}

// Convierte una cadena de texto a minúsculas para facilitar comparaciones
void convertirTextoAMinusculas(char *texto) {
  for (int i = 0; texto[i]; i++) texto[i] = tolower(texto[i]);
}

// Compara clientes por prioridad (menor valor primero) y, si es igual por tiempo de registro (más antiguo primero)
int compararClientesPorPrioridadYHora(void *a, void *b) {
  Cliente *clienteA = (Cliente *)a;
  Cliente *clienteB = (Cliente *)b;

  int prioridadA = obtenerValorPrioridad(clienteA->nivelPrioridad);
  int prioridadB = obtenerValorPrioridad(clienteB->nivelPrioridad);

  if (prioridadA != prioridadB)
    return prioridadA < prioridadB;

  return clienteA->tiempoRegistro < clienteB->tiempoRegistro;
}

// Registra a un nuevo cliente con ID único, descripción y prioridad baja, verificando duplicados y ordenando la lista
void registrarNuevoCliente(List *listaClientes) {
  char idIngresado[10];
  printf(BOLD "\nIngrese ID 'SIN GUION': " RESET);
  scanf(" %9[^\n]", idIngresado); 
  getchar();


  Cliente *clienteActual = list_first(listaClientes);
  while (clienteActual != NULL) {
    if (strcmp(clienteActual->idCliente, idIngresado) == 0) {
      printf(RED "\nEste ID ya está registrado.\n" RESET);
      presioneTeclaParaContinuar();
      return;
    }
    clienteActual = list_next(listaClientes);
  }


  Cliente *nuevoCliente = malloc(sizeof(Cliente));
  
  if (!nuevoCliente) return;

  strcpy(nuevoCliente->idCliente, idIngresado);
  printf(BOLD "Descripción del problema: " RESET);
  scanf(" %99[^\n]", nuevoCliente->descripcionProblema); getchar();

  time(&nuevoCliente->tiempoRegistro);
  strcpy(nuevoCliente->nivelPrioridad, "baja");

  list_sortedInsert(listaClientes, nuevoCliente, compararClientesPorPrioridadYHora);
  printf(GREEN "\nCliente registrado con prioridad 'baja'.\n" RESET);
  presioneTeclaParaContinuar();
}

// Muestra la lista de clientes en espera con ID, descripción, prioridad (con colores) y hora de registro
void mostrarListaClientes(List *listaClientes) {
  limpiarPantalla();
  Cliente *cliente = list_first(listaClientes);
  if (!cliente) {
    printf(RED "\nNo hay clientes en espera.\n" RESET);
    presioneTeclaParaContinuar();
    return;
  }

  printf(BOLD CYAN "\nClientes en espera:\n\n" RESET);

  while (cliente) {
    char horaFormateada[9];
    strftime(horaFormateada, sizeof(horaFormateada), "%H:%M:%S", localtime(&cliente->tiempoRegistro));

    // Prioridad con color sutil
    const char *color = "";
    if (strcmp(cliente->nivelPrioridad, "alta") == 0) color = RED;
    else if (strcmp(cliente->nivelPrioridad, "media") == 0) color = YELLOW;
    else color = GREEN;

    printf(BOLD "ID: " RESET "%s\n", cliente->idCliente);
    printf(BOLD "Descripción: " RESET "%s\n", cliente->descripcionProblema);
    printf(BOLD "Prioridad: " RESET "%s%s%s\n", color, cliente->nivelPrioridad, RESET);
    printf(BOLD "Hora de ingreso: " RESET "%s\n\n", horaFormateada);

    cliente = list_next(listaClientes);
  }

  presioneTeclaParaContinuar();
}

// Actualiza la prioridad de un cliente por ID, valida la entrada y reordena la lista
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

// Atiende al cliente con mayor prioridad (primero en la lista), lo elimina y muestra sus datos
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

// Busca un cliente por ID y muestra sus datos (ID, descripción, prioridad, hora) si existe
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

// Función principal crea la lista de clientes, gestiona el menú y ejecuta opciones hasta salir
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
