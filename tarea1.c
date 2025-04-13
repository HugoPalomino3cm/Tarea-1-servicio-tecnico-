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

// Asigna un número a la prioridad para comparar más fácil
int obtenerValorPrioridad(const char *prioridad) {
  if (strcmp(prioridad, "alta") == 0) return 1;
  if (strcmp(prioridad, "media") == 0) return 2;
  return 3; // baja
}

// Pasa un texto a minúsculas para no preocuparse por mayúsculas
void convertirTextoAMinusculas(char *texto) {
  for (int i = 0; texto[i]; i++) texto[i] = tolower(texto[i]);
}

// Compara clientes primero por prioridad y luego por hora de llegada
int compararClientesPorPrioridadYHora(void *a, void *b) {
  Cliente *clienteA = (Cliente *)a;
  Cliente *clienteB = (Cliente *)b;

  int prioridadA = obtenerValorPrioridad(clienteA->nivelPrioridad);
  int prioridadB = obtenerValorPrioridad(clienteB->nivelPrioridad);

  if (prioridadA != prioridadB)
    return prioridadA < prioridadB;

  return clienteA->tiempoRegistro < clienteB->tiempoRegistro;
}

// Agrega un cliente nuevo con sus datos y lo pone en la lista ordenada
void registrarNuevoCliente(List *listaClientes) {
  char idIngresado[10];
  printf(BOLD "\nIngrese ID 'SIN GUION': " RESET);
  scanf(" %9[^\n]", idIngresado); 
  getchar();

  // Revisa si el ID ya existe
  Cliente *clienteActual = list_first(listaClientes);
  while (clienteActual != NULL) {
    if (strcmp(clienteActual->idCliente, idIngresado) == 0) {
      printf(RED "\nEste ID ya está registrado.\n" RESET);
      presioneTeclaParaContinuar();
      return;
    }
    clienteActual = list_next(listaClientes);
  }

  // Crea el cliente y pide sus datos
  Cliente *nuevoCliente = malloc(sizeof(Cliente));
  
  if (!nuevoCliente) return;

  strcpy(nuevoCliente->idCliente, idIngresado);
  printf(BOLD "Descripción del problema: " RESET);
  scanf(" %99[^\n]", nuevoCliente->descripcionProblema); getchar();

  time(&nuevoCliente->tiempoRegistro);
  strcpy(nuevoCliente->nivelPrioridad, "baja");

  // Lo inserta en el orden correcto
  list_sortedInsert(listaClientes, nuevoCliente, compararClientesPorPrioridadYHora);
  printf(GREEN "\nCliente registrado con prioridad 'baja'.\n" RESET);
  presioneTeclaParaContinuar();
}

// Enseña todos los clientes que están esperando
void mostrarListaClientes(List *listaClientes) {
  limpiarPantalla();
  Cliente *cliente = list_first(listaClientes);
  if (!cliente) {
    printf(RED "\nNo hay clientes en espera.\n" RESET);
    presioneTeclaParaContinuar();
    return;
  }

  printf(BOLD CYAN "\nClientes en espera:\n\n" RESET);

  // Recorre la lista y muestra cada cliente
  while (cliente) {
    char horaFormateada[9];
    strftime(horaFormateada, sizeof(horaFormateada), "%H:%M:%S", localtime(&cliente->tiempoRegistro));

    // Cambia el color según la prioridad
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

// Cambia la prioridad de un cliente y reordena la lista
void actualizarPrioridadCliente(List *listaClientes) {
  char idBuscado[10], nuevaPrioridad[10];
  printf("ID del cliente: ");
  scanf(" %9[^\n]", idBuscado); 
  getchar();
  printf("Escriba la nueva prioridad (alta, media, baja): ");
  scanf(" %9[^\n]", nuevaPrioridad); 
  getchar();
  convertirTextoAMinusculas(nuevaPrioridad);

  // Verifica que la prioridad sea válida
  if (strcmp(nuevaPrioridad, "alta") && strcmp(nuevaPrioridad, "media") && strcmp(nuevaPrioridad, "baja")) {
    printf("Prioridad inválida.\n");
    presioneTeclaParaContinuar();
    return;
  }

  // Busca el cliente y actualiza su prioridad
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

// Atiende al cliente más importante y lo saca de la lista
void atenderClienteConMayorPrioridad(List *listaClientes) {
  Cliente *cliente = list_first(listaClientes);
  if (!cliente) {
    printf("No hay clientes en espera.\n");
    presioneTeclaParaContinuar();
    return;
  }

  // Muestra quién fue atendido y libera memoria
  list_popFront(listaClientes);
  printf("Cliente atendido:\nID: %s\nDescripción: %s\nPrioridad: %s\n",
         cliente->idCliente, cliente->descripcionProblema, cliente->nivelPrioridad);
  free(cliente);
  presioneTeclaParaContinuar();
}

// Busca un cliente por su ID y muestra toda su info
void buscarClientePorID(List *listaClientes) {
  char idBuscado[10];
  printf("Ingrese el ID del cliente: ");
  scanf(" %9[^\n]", idBuscado); getchar();

  // Revisa si el cliente existe
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

  // Bucle principal con el menú
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

  // Limpia la lista antes de terminar
  list_clean(listaClientes);
  return 0;
}