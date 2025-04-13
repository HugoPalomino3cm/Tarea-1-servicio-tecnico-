# Tarea-1-servicio-tecnico-
## Pasos para compilar y ejecutar el programa

1) Clonar el repositorio desde GitHub:
    -Asegúrate de tener git instalado.
    -Inicia sesión en tu cuenta de GitHub 

2) Compilar el programa:
    -En PowerShell, ejecuta los siguientes comandos
    -En la terminal ejecutar (nos genera el ejecutable) = gcc -o tarea1 tarea1.c tdas/list.c tdas/extra.c
    -Para que el programa muestre correctamente las tildes = $OutputEncoding = [Console]::OutputEncoding = [Text.UTF8Encoding]::new()
    -Para que empiece a compilar el codigo = ./tarea1


## Funcionalidad del sistema 'Descripción general'


Este sistema permite gestionar la atención de clientes en un servicio técnico, priorizando su atención según el nivel de urgencia del problema reportado.

## Funcionalidades principales

1) Registrar cliente nuevo: Agrega un nuevo cliente a la lista de espera con prioridad inicial baja.

2) Asignar prioridad: Cambia el nivel de prioridad (alta, media, baja) de un cliente existente.

3) Mostrar lista de espera: Muestra todos los clientes en espera, ordenados por prioridad y hora de llegada.

4) Atender cliente: Atiende al cliente con mayor prioridad (y más antiguo en caso de empate).

5) Buscar cliente por ID: Permite buscar a un cliente específico mediante su identificador.

6) Salir: Finaliza el programa.