#pragma once // Ensures the header file is included only once during compilation
#include "Prerequisites.h" // Includes necessary prerequisites

/**
 * @brief Class for XOR-based encoding and decoding operations.
 */
class 
XOREncoder {
public:
  XOREncoder() = default; // Default constructor
  ~XOREncoder() = default; // Default destructor

  /**
   * @brief Encodes a string using XOR encryption with a given key.
   * @param input The input string to encode.
   * @param key The key used for XOR encryption.
   * @return The encoded string.
   */
  std::string 
    encode(const std::string& input, const std::string& key) {
    std::string output = input;
     // Perform XOR operation for each character in the input
    for (int i = 0; i < input.size(); i++) {
        output[i] = input[i] ^ key[i % key.size()];
    }
    return output;
  }

  /**
   * @brief Converts a hexadecimal string to a vector of bytes.
   * @param input The hexadecimal string to convert.
   * @return A vector of bytes representing the hexadecimal values.
   */
  std::vector<unsigned char> 
  HexToBytes(const std::string& input) {

    std::vector<unsigned char> bytes;
    std::istringstream iss(input);
    std::string hexValue;

        // Parse each hexadecimal value from the input string
        while (iss >> hexValue) {
            if (hexValue.size() == 1) {
                hexValue = "0" + hexValue; // Pad single-digit hex values
            }
            unsigned int byte;
            std::stringstream ss;
            ss << std::hex << hexValue;
            ss >> byte;
            bytes.push_back(static_cast<unsigned char>(byte));
        }
        return bytes;
    }

    /**
     * @brief Prints a string as hexadecimal values.
     * @param input The string to print in hexadecimal format.
     */
    void 
    printHex(const std::string& input) {
        for (unsigned char c : input) {
            // Print each character as a two-digit hexadecimal value
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";
        }
    }

    /**
     * @brief Checks if a string contains valid printable text.
     * @param data The string to validate.
     * @return True if the string contains valid text, false otherwise.
     */
    bool 
    isValidText(const std::string& data) {
        // Validate each character in the string
        return std::all_of(data.begin(), data.end(), [](unsigned char c) {
            return std::isprint(c) || std::isspace(c) || c == '\n' || c == ' ';
        });
    }

    /**
     * @brief Attempts to decode a XOR-encrypted string using a single-byte key.
     * @param cifrado The encrypted data as a vector of bytes.
     */
    void 
    bruteForce_1Byte(const std::vector<unsigned char>& cifrado) {
        for (int clave = 0; clave < 256; ++clave) {
            std::string result;

            // XOR each byte with the current key
            for (unsigned char c : cifrado) {
                result += static_cast<unsigned char>(c ^ clave);
            }

            // Check if the result is valid text
            if (isValidText(result)) {
                std::cout << "Clave 1 byte  : '" << static_cast<char>(clave)
                          << "' (0x" << std::hex << std::setw(2) << std::setfill('0') << clave << ")\n";
                std::cout << "Texto posible : " << result << "\n";
            }
        }
    }

    /**
     * @brief Attempts to decode a XOR-encrypted string using a two-byte key.
     * @param cifrado The encrypted data as a vector of bytes.
     */
    void 
    bruteForce_2Byte(const std::vector<unsigned char>& cifrado) {

      for (int b1 = 0; b1 < 256; ++b1) {
          for (int b2 = 0; b2 < 256; ++b2) {
              std::string result;
              unsigned char key[2] = { static_cast<unsigned char>(b1), static_cast<unsigned char>(b2) };

              // XOR each byte with the current two-byte key
              for (int i = 0; i < cifrado.size(); i++) {
                  result += cifrado[i] ^ key[i % 2];
              }

                // Check if the result is valid text
              if (isValidText(result)) {
                  std::cout << "Clave 2 bytes : '" << static_cast<char>(b1) << static_cast<char>(b2)
                            << "' (0x" << std::hex << std::setw(2) << std::setfill('0') << b1
                            << " 0x" << std::setw(2) << std::setfill('0') << b2 << ")\n";
                  std::cout << "Texto posible : " << result << "\n";
              }
          }
      }
    }

    /**
     * @brief Attempts to decode a XOR-encrypted string using a dictionary of common keys.
     * @param cifrado The encrypted data as a vector of bytes.
     */
    void 
    bruteForceByDictionary(const std::vector<unsigned char>& cifrado) {
      // List of common keys to try
      std::vector<std::string> clavesComunes = {
          "clave", "admin", "1234", "root", "test", "abc", "hola", "user",
          "pass", "12345", "0000", "password", "default"
      };

      for (const auto& clave : clavesComunes) {
         std::string result;

          // XOR each byte with the current dictionary key
          for (int i = 0; i < cifrado.size(); i++) {
              result += static_cast<unsigned char>(cifrado[i] ^ clave[i % clave.size()]);
          }

          // Check if the result is valid text
          if (isValidText(result)) {
              std::cout << "Clave de diccionario: '" << clave << "'\n";
              std::cout << "Texto posible : " << result << "\n";
          }
      }
    }

private:
    // No private members in this class
};