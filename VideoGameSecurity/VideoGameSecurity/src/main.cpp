#include "Prerequisites.h" // Includes necessary prerequisites
#include "DES.h"           // Includes the DES class for encryption and decryption

/**
 * @brief Main function demonstrating DES encryption and decryption of a string.
 * @return Exit code of the program.
 */
int 
main() {
    // Define a 64-bit key for DES encryption
    std::bitset<64> key("0001001100110100010101110111100110011011101111001101111111110001");

    // Original phrase to encrypt
    std::string phrase = "$Hola DES!";

    // Pad the phrase with null characters to ensure its length is a multiple of 8 bytes
    while (phrase.size() % 8 != 0) {
    phrase += '\0'; // Add null space for padding
    }

    // Vector to store encrypted blocks
    std::vector<std::bitset<64>> cipherBlocks;

    // Display the original text
    std::cout << "Texto original: " << phrase << std::endl;

    // Display the encrypted text in hexadecimal format
    std::cout << "Cifrado en hexadecimal:\n";

    // Create an instance of the DES class with the provided key
    DES des(key);

    // Encrypt the phrase block by block (8 bytes per block)
    for (size_t i = 0; i < phrase.size(); i += 8) {
        // Extract an 8-byte block from the phrase
        std::string block = phrase.substr(i, 8);

        // Convert the block to a 64-bit bitset
        auto blockBits = des.stringToBitset64(block);

        // Encrypt the block using DES
        auto encrypted = des.encode(blockBits);

        // Store the encrypted block in the vector
        cipherBlocks.push_back(encrypted);

        // Display the encrypted block in hexadecimal format
        std::cout << std::hex << std::uppercase << std::setw(16) << std::setfill('0') << encrypted.to_ullong() << " ";
    }

    std::cout << std::endl;

    // String to store the decrypted output
    std::string output;

    // Decrypt each encrypted block and reconstruct the original phrase
    for (const auto& block : cipherBlocks) {
        // Decrypt the block using DES
        auto decrypted = des.decode(block);

        // Convert the decrypted block back to a string and append it to the output
        output += des.bitset64ToString(decrypted);
    }

    // Display the decrypted text
    std::cout << "Texto descifrado: " << phrase << std::endl;

    return 0; // Return exit code
}