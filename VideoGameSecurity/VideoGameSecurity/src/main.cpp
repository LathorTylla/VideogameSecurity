#include "Prerequisites.h" 
#include "XOREncoder.h"    

/**
 * @brief Main function demonstrating XOR encryption, decryption, and brute force attacks.
 * @return Exit code of the program.
 */
int 
main() {
  XOREncoder XORencoder; // Create an instance of the XOR encoder

  // Original message and key for encryption
  std::string mensaje = "Hola Mundo";
  std::string clave = "clave";

  // Display the original message
  std::cout << "Mensaje original: " << mensaje << std::endl;

  std::cout << std::endl;
  std::cout << std::endl;

  // Encrypt the message using the XOR encoder
  std::string cifrado = XORencoder.encode(mensaje, clave);
  std::cout << "Texto cifrado (original): " << cifrado << std::endl;

  // Decrypt the message using the same key
  std::string descifrado = XORencoder.encode(cifrado, clave);

  // Display the encrypted message in hexadecimal format
  std::cout << "Texto cifrado (hex): ";
  XORencoder.printHex(cifrado);
  std::cout << std::endl;

  // Display the decrypted message
  std::cout << "Mensaje descifrado: " << descifrado << std::endl;

  // Convert the encrypted message to a vector of bytes for brute force operations
  std::vector<unsigned char> bytesCifrados(cifrado.begin(), cifrado.end());

  // Perform brute force attack with single-byte keys
  std::cout << "\n--- Fuerza bruta (1 byte) con filtro ---\n";
  XORencoder.bruteForce_1Byte(bytesCifrados);

  // Perform brute force attack with two-byte keys
  std::cout << "\n--- Fuerza bruta (2 bytes) con filtro ---\n";
  XORencoder.bruteForce_2Byte(bytesCifrados);

  // Perform brute force attack using a dictionary of common keys
  std::cout << "\n--- Fuerza bruta (diccionario de claves) ---\n";
  XORencoder.bruteForceByDictionary(bytesCifrados);

  return 0; // Return exit code
}