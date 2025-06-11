# Videogame Security++

Este repositorio contiene implementaciones educativas de distintos algoritmos y conceptos criptográficos utilizando el lenguaje C++. Tiene como objetivo comprender cómo funcionan los cifrados más importantes 

## Contenido

### 1. **Cifrado César**
Una de las técnicas de cifrado más antiguas. Implementamos:
- Codificación con desplazamiento sobre letras, números y símbolos.
- Descifrado por fuerza bruta.
- Análisis de frecuencia para deducción automática de la clave.
  
**Archivo relevante:** `CesarEncryption.h`

### 2. **Cifrado XOR**
Una técnica simétrica moderna y sencilla basada en la operación lógica XOR:
- Codificación con claves de uno o más caracteres.
- Conversión entre texto y bytes en hexadecimal.
- Ataques por fuerza bruta de 1 y 2 bytes.
- Diccionario de claves comunes.
- Validación de texto legible.

**Archivo relevante:** `XOREncoder.h`

### 3. **Codificación ASCII y Binaria**
Convertimos entre texto legible y su representación binaria:
- Cada carácter ASCII.
- Texto completo a binario separado por espacios.
- Decodificación inversa desde binario a texto.

**Archivo relevante:** `AsciiBinary.h`

### 4. **Cifrado DES (Data Encryption Standard)**
Implementación simplificada del cifrado por bloques :
- Permutaciones iniciales y finales.
- Generación de subclaves.
- Funciones de expansión, sustitución (S-boxes) y permutación (P-table).
- Rondas de Feistel (16 rondas).
- Conversión texto ↔ bits.
- Codificación y decodificación completas.

**Archivo relevante:** `DES.h`

---


## Estructura del Repositorio

/include

├── CesarEncryption.h

├── XOREncoder.h

├── AsciiBinary.h

├── DES.h

/source

├──main.cpp

## Propósito Educativo

Este proyecto no está orientado a la producción, sino al aprendizaje de cómo funcionan los algoritmos criptográficos desde cero. Se recomienda no usar estas implementaciones en sistemas reales de seguridad.

