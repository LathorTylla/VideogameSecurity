#pragma once 
#include "Prerequisites.h"
/**
 * @brief Implements Caesar cipher encryption and decryption.
 * @details This class provides methods to encode and decode text using the Caesar cipher,
 *          shifting letters and digits by a specified amount. It supports both uppercase
 *          and lowercase letters, as well as digits. Additional methods allow brute-force
 *          attacks and key evaluation based on frequency analysis.
 */
class 
CesarEncryption {
public:
  /**
   * @brief Default constructor.
   * @summary Initializes a new instance of the CesarEncryption class.
   */
  CesarEncryption() = default;

  /**
   * @brief Default destructor.
   * @summary Cleans up resources used by the CesarEncryption instance.
   */
  ~CesarEncryption() = default;

    /**
     * @brief Encodes a string using the Caesar cipher.
     * @summary Shifts each letter and digit in the input string by the specified amount.
     *          Non-alphanumeric characters are not modified.
     * @param texto The input string to encode.
     * @param desplazamiento The number of positions to shift each character.
     * @return The encoded string.
     */
    std::string 
    encode(const std::string& texto, int desplazamiento) {
        std::string result = "";

        for (char c : texto) {
            if (c >= 'A' && c <= 'Z') {
                result += (char)(((c - 'A' + desplazamiento) % 26) + 'A');
            }
            else if (c >= 'a' && c <= 'z') {
                result += (char)(((c - 'a' + desplazamiento) % 26) + 'a');
            }
            else if (c >= '0' && c <= '9') {
                result += (char)(((c - '0' + desplazamiento) % 10) + '0');
            }
            else {
                result += c;
            }
        }

        return result;
    }

    /**
     * @brief Decodes a string encoded with the Caesar cipher.
     * @summary Reverses the Caesar cipher encoding by shifting characters in the opposite direction.
     * @param texto The encoded string to decode.
     * @param desplazamiento The number of positions originally used to shift each character.
     * @return The decoded string.
     */
    std::string 
    decode(const std::string& texto, int desplazamiento) {
        return encode(texto, 26 - (desplazamiento % 26));
    }

    /**
     * @brief Attempts to decode a string using all possible Caesar cipher keys.
     * @summary Performs a brute-force attack by trying all 26 possible shifts and outputs each result.
     * @param texto The encoded string to attempt to decode.
     * @return void
     */
    void 
    bruteForceAttack(const std::string& texto) {
        std::cout << "\nIntentos de descifrado por fuerza bruta:\n";
        for (int clave = 0; clave < 26; clave++) {
            std::string intento = encode(texto, 26 - clave);
            std::cout << "Clave " << clave << ": " << intento << std::endl;
        }
    }

    /**
     * @brief Evaluates the most probable key for decoding a Caesar ciphered string.
     * @summary Uses frequency analysis and common Spanish words to estimate the most likely key.
     * @param texto The encoded string to analyze.
     * @return The most probable key for decoding the string.
     */
    int 
    evaluatePossibleKey(const std::string& texto) {
        int frecuencias[26] = { 0 };

        for (char c : texto) {
            if (c >= 'a' && c <= 'z') {
                frecuencias[c - 'a']++;
            }
            else if (c >= 'A' && c <= 'Z') {
                frecuencias[c - 'A']++;
            }
        }

        const char letrasEsp[] = { 'e', 'a', 'o', 's', 'r', 'n', 'i', 'd', 'l', 'c' };

        int indiceMax = 0;
        for (int i = 1; i < 26; ++i) {
            if (frecuencias[i] > frecuencias[indiceMax]) {
                indiceMax = i;
            }
        }

        int mejorClave = 0;
        int mejorPuntaje = -1;

        for (char letraRef : letrasEsp) {
            int clave = (indiceMax - (letraRef - 'a') + 26) % 26;
            int puntaje = 0;

            std::string descifrado = encode(texto, 26 - clave);

            std::string comunes[] = { "el", "de", "la", "que", "en", "y", "los", "se" };

            for (std::string palabra : comunes) {
                if (descifrado.find(palabra) != std::string::npos) {
                    puntaje++;
                }
            }

            if (puntaje > mejorPuntaje) {
                mejorPuntaje = puntaje;
                mejorClave = clave;
            }
        }

        return mejorClave;
    }

private:

};