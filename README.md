# Tarea-1-servicio-tecnico-
## Pasos para compilar y ejecutar el programa

### Requisitos Previos:
1) Git instalado
2) Compilador GCC
3) PowerShell
4) Sistema operativo (Windows, Linux o macOS)
5) Visual Studio Code

### Funcionalidad del sistema 'Descripción general'

Este sistema permite gestionar la atención de clientes en un servicio técnico, priorizando su atención según el nivel de urgencia del problema reportado.

### Compilar el programa:

1) Abre Visual Studio Code (VSCode):
   - Asegúrate de tener la extensión de Git instalada en VSCode.
   - Haz clic en la pestaña de "Source Control" (Control de Código Fuente) en la barra lateral (ícono de Git).
   - Selecciona "Clone Repository" e ingresa la URL del repositorio:`https://github.com/HugoPalomino3cm/Tarea-1-servicio-tecnico-.git`
   - Elige una carpeta local para guardar el proyecto y abre la carpeta clonada en VSCode.
2) Abre una terminal en VSCode o usa PowerShell:
   - En VSCode, selecciona `Terminal -> New Terminal` para abrir una terminal integrada.
   - Compila el programa ejecutando el siguiente comando en la terminal (genera el ejecutable):
   - En PowerShell, ejecuta los siguientes comandos
   - En la terminal ejecutar (nos genera el ejecutable) = `gcc -o tarea1 tarea1.c tdas/list.c tdas/extra.c`
   - Para que el programa muestre correctamente las tildes = `$OutputEncoding = [Console]::OutputEncoding = [Text.UTF8Encoding]::new()`
   - Para que empiece a compilar el codigo = `./tarea1`


## Uso del Programa

### Ejemplo de Uso

Un ejemplo de cómo interactuar con el sistema de servicio técnico:

---

#### **1) Registrar Cliente Nuevo**  
**Descripción:** Ingresa el ID y la descripción del problema.  
**Nota:** `Puedes registrar varios clientes, pero debe ser uno por uno.`  
- **Ingrese ID 'SIN GUION':** 232323232  
- **Descripción del problema:** Error en la RAM  
- **Resultado:** Cliente registrado con prioridad 'baja'.  

---

#### **2) Asignar Prioridad**  
**Descripción:** Escribe el ID del cliente y `cambia su prioridad a alta, media o baja` (si el ID existe).  
- **ID del cliente:** 232323232  
- **Nueva prioridad:** alta  
- **Resultado:** Prioridad actualizada.  

---

#### **3) Mostrar Lista de Espera**  
**Descripción:** Muestra todos los clientes, ordenados por prioridad y hora de llegada.  
- **ID:** 232323232  
- **Descripción:** Error en la RAM  
- **Prioridad:** alta  
- **Hora de ingreso:** 14:30:45  

---

#### **4) Atender Cliente**  
**Descripción:** Atiende al cliente con mayor prioridad. Si hay empate, se atiende al más antiguo según `hora de llegada`.  
- **Cliente atendido:**  
  - **ID:** 232323232  
  - **Descripción:** Error en la RAM  
  - **Prioridad:** alta  

---

#### **5) Buscar Cliente por ID**  
**Descripción:** Busca un cliente específico por su ID y muestra sus datos `si es que se encuentra`.  
- **Ingrese el ID del cliente:** 232323232  
- **Cliente encontrado:**  
  - **ID:** 232323232  
  - **Descripción:** Error en la RAM  
  - **Prioridad:** alta  
  - **Hora de registro:** 14:30:45  

---

#### **6) Salir**  
**Descripción:** `Finaliza el programa.`  
- **Resultado:** Saliendo del sistema de gestión de servicio técnico...  

---

