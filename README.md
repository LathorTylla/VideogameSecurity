# Sistema de Cifrado de Archivos

Este proyecto implementa un sistema para cifrar y descifrar archivos de texto utilizando varios algoritmos de cifrado, como XOR, Caesar, ASCII-Binary, Vigenere y DES. Está diseñado para proteger datos sensibles, como usuarios, contraseñas y correos electrónicos, mediante la encriptación.

## Descripción

El sistema toma un archivo de texto (con formato `.txt`), lo cifra utilizando uno de los métodos de cifrado disponibles y guarda el archivo cifrado en una carpeta de salida. Los datos a cifrar deben estar en el formato:

usuario:contraseña:correo

Por ejemplo:

admin:pass123:correo@admin.com

Los archivos de texto se deben almacenar en la carpeta **`bin/Datos crudos/`** y los archivos cifrados se guardarán en la carpeta **`bin/Datos cif/`**.

## Estructura de las Carpetas

El proyecto requiere que las siguientes carpetas estén presentes en la raíz de tu proyecto:

archivos/

├── Datos crudos/

└── Datos cif/

- **`archivos/Datos crudos/`**: Aquí debes colocar los archivos `.txt` que deseas cifrar (sin encriptar).
- **`archivos/Datos cif/`**: Aquí se guardarán los archivos cifrados resultantes.

### Creación de Carpetas

Si las carpetas **`archivos/Datos crudos/`** y **`archivos/Datos cif/`** no existen, puedes crearlas manualmente 

## Requisitos

- C++ con soporte para las librerías estándar.
- Compilador compatible con C++ 

## Uso

1. **Configuración Inicial:**

   Asegúrate de que las carpetas `archivos/Datos crudos/` y `archivos/Datos cif/` existan antes de ejecutar el programa.

   Si deseas cambiar las rutas de los archivos, puedes hacerlo modificando las siguientes líneas de código en `main.cpp`:

   ```cpp
   const std::string CARPETA_CRUDOS = "bin/Datos crudos/";
   const std::string CARPETA_CIFRADOS = "bin/Datos cif/";
Estas líneas especifican las rutas de las carpetas donde se encuentran los archivos de entrada y salida.

### Cifrado:

Ejecuta el programa.

Selecciona 1 para cifrar un archivo.

Ingresa el nombre del archivo .txt a cifrar (debe estar en bin/Datos crudos/).

Selecciona el tipo de cifrado que deseas usar: XOR, Caesar, ASCII-Binary, Vigenere o DES.

Ingresa la clave o parámetro necesario (por ejemplo, clave para XOR o desplazamiento para Caesar).

El archivo cifrado será guardado en bin/Datos cif/ con el sufijo .txt.

### Descifrado:

Ejecuta el programa.

Selecciona 2 para descifrar un archivo.

Ingresa el nombre del archivo cifrado (debe estar en bin/Datos cif/).

Selecciona el tipo de cifrado usado en el archivo.

Ingresa la clave o parámetro necesario para descifrar el archivo (por ejemplo, clave de cifrado o desplazamiento).

El archivo descifrado será guardado en bin/Datos crudos/.

## Notas
El sistema solo admite archivos .txt.

Los archivos deben seguir el formato de registro usuario:contraseña:correo para ser correctamente cifrados y descifrados.

### Recomendaciones para los Archivos de Entrada
Los archivos de entrada deben contener registros en el siguiente formato:

usuario:contraseña:correo

Por ejemplo:

admin:pass123:correo@admin.com

El sistema tomará cada línea y la cifrará utilizando el algoritmo seleccionado.

