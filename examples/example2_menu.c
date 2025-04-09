#include <stdio.h>
#include <stdlib.h>

// Prototipos de funciones para el menú principal
void gestionarUsuarios();
void gestionarConfiguracion();

// Prototipos de funciones para el submenú de Usuarios
void agregarUsuario();
void eliminarUsuario();

// Prototipos de funciones para el submenú de Configuración
void cambiarIdioma();
void ajustarPrivacidad();

// Función para limpiar la pantalla
void limpiarPantalla() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif
}

// Menú principal
void mostrarMenuPrincipal() {
  limpiarPantalla();
  puts("========================================");
  puts("            Menú Principal");
  puts("========================================");

  puts("1) Gestionar Usuarios.");
  puts("2) Configuración.");
  puts("3) Salir.");
}

// Submenú de Usuarios
void mostrarMenuUsuarios() {
  puts("========================================");
  puts("           Gestionar Usuarios");
  puts("========================================");

  puts("1) Agregar Usuario.");
  puts("2) Eliminar Usuario.");
  puts("3) Volver al Menú Principal.");
}

// Submenú de Configuración
void mostrarMenuConfiguracion() {
  limpiarPantalla();
  puts("========================================");
  puts("             Configuración");
  puts("========================================");

  puts("1) Cambiar Idioma.");
  puts("2) Ajustar Privacidad.");
  puts("3) Volver al Menú Principal.");
}

void presioneTeclaParaContinuar() {
  puts("Presione una tecla para continuar...");
  getchar(); // Consume el '\n' del buffer de entrada
  getchar(); // Espera a que el usuario presione una tecla
}

int main() {
  char opcion;
  do {

    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf("%c", &opcion);

    switch (opcion) {
    case '1':
      gestionarUsuarios();
      break;
    case '2':
      gestionarConfiguracion();
      break;
    case '3':
      puts("Saliendo del programa...");
      break;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }

  } while (opcion != '3');

  return 0;
}

void gestionarUsuarios() {
  char opcion;
  do {
    limpiarPantalla();
    mostrarMenuUsuarios();
    printf("Ingrese su opción: ");
    scanf("%c", &opcion);

    switch (opcion) {
    case '1':
      agregarUsuario();
      break;
    case '2':
      eliminarUsuario();
      break;
    case '3':
      return;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }

  } while (opcion != '3');
}

void gestionarConfiguracion() {
  char opcion;
  do {
    limpiarPantalla();
    mostrarMenuConfiguracion();
    printf("Ingrese su opción: ");
    scanf("%c", &opcion);

    switch (opcion) {
    case '1':
      cambiarIdioma();
      break;
    case '2':
      ajustarPrivacidad();
      break;
    case '3':
      return;
    default:
      puts("Opción no válida. Por favor, intente de nuevo.");
    }

  } while (opcion != '3');
}

// Implementaciones de funciones auxiliares
void agregarUsuario() {
  puts("Agregar Usuario (función no implementada).");
  presioneTeclaParaContinuar();
}

void eliminarUsuario() {
  puts("Eliminar Usuario (función no implementada).");
  presioneTeclaParaContinuar();
}

void cambiarIdioma() {
  puts("Cambiar Idioma (función no implementada).");
  presioneTeclaParaContinuar();
}

void ajustarPrivacidad() {
  puts("Ajustar Privacidad (función no implementada).");
  presioneTeclaParaContinuar();
}
