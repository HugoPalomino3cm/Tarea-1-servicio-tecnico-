# Tarea-1-servicio-tecnico-
## Pasos para compilar y ejecutar el programa

### Requisitos Previos:
1) Git instalado
2) Compilador GCC
3) PowerShell
4) Sistema operativo (Windows, Linux o macOS)
5) Visual Studio Code

### Compilar el programa:

1) Abre Visual Studio Code (VSCode) y clona el repositorio:
   - Asegúrate de tener la extensión de Git instalada en VSCode.
   - Haz clic en la pestaña de "Source Control" (Control de Código Fuente) en la barra lateral (ícono de Git).
   - Selecciona "Clone Repository" e ingresa la URL del repositorio:`https://github.com/HugoPalomino3cm/Tarea-1-servicio-tecnico-.git`.
   - Elige una carpeta local para guardar el proyecto y abre la carpeta clonada en VSCode.
2) Abre una terminal en VSCode o usa PowerShell:
   - En VSCode, selecciona `Terminal -> New Terminal` para abrir una terminal integrada.
   - Compila el programa ejecutando el siguiente comando en la terminal (genera el ejecutable):
   - En PowerShell, ejecuta los siguientes comandos
   - En la terminal ejecutar (nos genera el ejecutable) = `gcc -o tarea1 tarea1.c tdas/list.c tdas/extra.c`
   - Para que el programa muestre correctamente las tildes = `$OutputEncoding = [Console]::OutputEncoding = [Text.UTF8Encoding]::new()`
   - Para que empiece a compilar el codigo = `./tarea1`


### Funcionalidad del sistema 'Descripción general'

Este sistema permite gestionar la atención de clientes en un servicio técnico, priorizando su atención según el nivel de urgencia del problema reportado.

### Funcionalidades principales

1) Registrar cliente nuevo: Agrega un nuevo cliente a la lista de espera con prioridad inicial baja.

2) Asignar prioridad: Cambia el nivel de prioridad (alta, media, baja) de un cliente existente.

3) Mostrar lista de espera: Muestra todos los clientes en espera, ordenados por prioridad y hora de llegada.

4) Atender cliente: Atiende al cliente con mayor prioridad (y más antiguo en caso de empate).

5) Buscar cliente por ID: Permite buscar a un cliente específico mediante su identificador.

6) Salir: Finaliza el programa.
