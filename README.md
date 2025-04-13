# Tarea 1: Sistema de Servicio Técnico

## Pasos para Compilar y Ejecutar el Programa

### Requisitos Previos
- **Git** instalado.
- **Compilador GCC**.
- **PowerShell** (para Windows; opcional para Linux/macOS).
- Sistema operativo: Windows, Linux o macOS.
- **Visual Studio Code** (recomendado).

### Descripción General del Sistema
Este sistema permite gestionar la atención de clientes en un servicio técnico, priorizando su atención según el nivel de urgencia del problema reportado.

### Instrucciones para Compilar

1. **Clonar el Repositorio en Visual Studio Code (VSCode):**
   - Asegúrate de tener la extensión de Git instalada en VSCode.
   - Haz clic en la pestaña "Source Control" (ícono de Git) en la barra lateral.
   - Selecciona "Clone Repository" e ingresa la URL del repositorio:
     ```bash
        https://github.com/HugoPalomino3cm/Tarea-1-servicio-tecnico-.git
   - Elige una carpeta local para guardar el proyecto y abre la carpeta clonada en VSCode.

2. **Compilar el Programa:**
   - Abre una terminal en VSCode (`Terminal -> New Terminal`) o usa PowerShell.
   - Ejecuta los siguientes comandos en la terminal:
     - Para generar el ejecutable:  
       ```bash
          gcc -o tarea1 tarea1.c tdas/list.c tdas/extra.c
       
     - Para mostrar correctamente las tildes (en PowerShell):
       ```bash
         $OutputEncoding = [Console]::OutputEncoding = [Text.UTF8Encoding]::new()
      
      - Para ejecutar el programa:
      ```bash
          ./tarea1


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

