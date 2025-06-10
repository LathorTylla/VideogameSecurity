#include <iostream> 
#include <string>   
#include "CesarEncryption.h" 
using namespace std;

/**
 * @brief Encodes a string using a Caesar cipher with the specified rotation.
 * @param texto The input string to encode.
 * @param rotacion The number of positions to rotate each character.
 * @return The encoded string.
 */
string 
Cesardecode(const string& texto, int rotacion) {
  string resultado = "";

  // Iterate through each character in the input string
  for (char c : texto) {
    if (c >= 'A' && c <= 'Z') {
      // Rotate uppercase letters
      resultado += (char)(((c - 'A' + rotacion) % 26) + 'A');
    }
    else if (c >= 'a' && c <= 'z') {
      // Rotate lowercase letters
      resultado += (char)(((c - 'a' + rotacion) % 26) + 'a');
    }
    else if (c >= '0' && c <= '9') {
      // Rotate digits
      resultado += (char)(((c - '0' + rotacion) % 10) + '0');
    }
    else {
      // Keep non-alphanumeric characters unchanged
      resultado += c;
    }
  }

  return resultado;
}

/**
 * @brief Decodes a string encoded with a Caesar cipher using the specified rotation.
 * @param texto The encoded string to decode.
 * @param rotacion The number of positions the characters were rotated.
 * @return The decoded string.
 */
string 
descifrarCesar(const string& texto, int rotacion) {
  // Reverse the rotation to decode the string
  return Cesardecode(texto, 26 - (rotacion % 26));
}

/**
 * @brief Attempts to decode a Caesar cipher using brute force by trying all possible keys.
 * @param cifrado The encoded string to decode.
 */
void 
ataqueFuerzaBruta(const string& cifrado) {
  cout << "\nIntentos de descifrado por fuerza bruta:\n";
  for (int clave = 1; clave < 26; ++clave) {
    // Try decoding with each possible key
    string intento = Cesardecode(cifrado, 26 - clave);
    cout << "Clave " << clave << ": " << intento << endl;
  }
}

/**
 * @brief Calculates the most probable key for decoding a Caesar cipher based on letter frequency analysis.
 * @param texto The encoded string to analyze.
 * @return The most probable key for decoding.
 */
int 
calcularClaveProbable(const string& texto) {
  int frecuencias[26] = { 0 };

  // Count the frequency of each letter in the string
  for (char c : texto) {
    if (c >= 'a' && c <= 'z') {
      frecuencias[c - 'a']++;
    }
    else if (c >= 'A' && c <= 'Z') {
      frecuencias[c - 'A']++;
    }
  }

  // Find the letter with the highest frequency
  int indiceMax = 0;
  for (int i = 1; i < 26; ++i) {
    if (frecuencias[i] > frecuencias[indiceMax]) {
      indiceMax = i;
    }
  }

  // Calculate the probable key based on the frequency of 'e'
  int claveProbable = (indiceMax - ('e' - 'a') + 26) % 26;
  return claveProbable;
}

/**
 * @brief Main function demonstrating Caesar cipher encoding, decoding, and key evaluation.
 * @return Exit code of the program.
 */
int 
main() {
  // Original message to encode
  string mensaje = "Bienvenidos a la clase de seguridad para videojuegos. En esta materia, aprenderan a cifrar mensajes y descifrar codigos ocultos";
  int rotacion = 4; // Rotation value for the cipher

  // Create an instance of CesarEncryption
  CesarEncryption cesar;

  // Encode the message
  string cifrado = cesar.encode(mensaje, rotacion);
  cout << "Texto cifrado: " << cifrado << endl;

  // Decode the message
  string descifrado = cesar.decode(cifrado, rotacion);
  cout << "Texto descifrado: " << descifrado << endl;

  // Evaluate the probable key for the encoded message
  cout << "Posible Clave:" + std::to_string(cesar.evaluatePossibleKey(cifrado)) << endl;

  return 0;
}