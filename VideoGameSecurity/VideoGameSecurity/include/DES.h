#pragma once
#include "Prerequisites.h"

/**
 * @brief Class implementing the DES (Data Encryption Standard) algorithm.
 */
class 
DES {
public:
  DES() = default; // Default constructor

    /**
     * @brief Constructor that initializes the DES key and generates subkeys.
     * @param key The 64-bit key used for encryption and decryption.
     */
    DES(const std::bitset<64>& key) : key(key) {
    generateSubkeys(); // Generate subkeys for the DES algorithm
    }

  ~DES() = default; // Default destructor

    /**
     * @brief Generates 16 subkeys from the main key for DES rounds.
     */
    void 
    generateSubkeys() {
    for (int i = 0; i < 16; ++i) {
      // Generate a 48-bit subkey by shifting the main key
      std::bitset<48> subkey((key.to_ullong() >> i) & 0xFFFFFFFFFFFF);
      subkeys.push_back(subkey); // Store the subkey
        }
    }

    /**
     * @brief Performs the initial permutation on a 64-bit block.
     * @param input The 64-bit block to permute.
     * @return The permuted 64-bit block.
     */
    std::bitset<64> 
    iPermutation(const std::bitset<64>& input) {
    std::bitset<64> output;
    for (int i = 0; i < 64; i++) {
      output[i] = input[i]; // Copy input bits directly (simplified permutation)
    }
    return output;
    }

    /**
     * @brief Expands a 32-bit block to 48 bits using the expansion table.
     * @param halfBlock The 32-bit block to expand.
     * @return The expanded 48-bit block.
     */
    std::bitset<48> 
    expand(const std::bitset<32>& halfBlock) {
      std::bitset<48> output;
      for (int i = 0; i < 48; i++) {
        output[i] = halfBlock[32 - EXPANSION_TABLE[i]]; // Map bits using the expansion table
      }
      return output;
    }

    /**
     * @brief Substitutes a 48-bit block using S-Boxes to produce a 32-bit block.
     * @param input The 48-bit block to substitute.
     * @return The substituted 32-bit block.
     */
    std::bitset<32> 
    substitute(const std::bitset<48>& input) {
      std::bitset<32> output;
      for (int i = 0; i < 8; i++) {
          // Calculate row and column indices for the S-Box
          int row = (input[i * 6] << 1) | input[i * 6 + 5];
          int col = (input[i * 6 + 1] << 3) | (input[i * 6 + 2] << 2) |
                    (input[i * 6 + 3] << 1) | input[i * 6 + 4];
          int sboxValue = SBOX[row % 4][col % 16]; // Get value from S-Box

          // Extract bits from the S-Box value
          for (int j = 0; j < 4; j++) {
              output[i * 4 + j] = (sboxValue >> (3 - j)) & 1;
          }
      }
      return output;
    }

    /**
     * @brief Permutes a 32-bit block using the P-Table.
     * @param input The 32-bit block to permute.
     * @return The permuted 32-bit block.
     */
    std::bitset<32> 
    permuteP(const std::bitset<32>& input) {
      std::bitset<32> output;
      for (int i = 0; i < 32; i++) {
        output[i] = input[32 - P_TABLE[i]]; // Map bits using the P-Table
      }
      return output;
    }

    /**
     * @brief Performs the Feistel function on a 32-bit block.
     * @param right The 32-bit block to process.
     * @param subkey The 48-bit subkey for the current round.
     * @return The resulting 32-bit block after the Feistel function.
     */
    std::bitset<32> 
    feistel(const std::bitset<32>& right, const std::bitset<48>& subkey) {
      auto expanded = expand(right); // Expand the block
      auto xored = expanded ^ subkey; // XOR with the subkey
      auto substituted = substitute(xored); // Substitute using S-Boxes
      auto permuted = permuteP(substituted); // Permute using P-Table
      return permuted;
    }

    /**
     * @brief Performs the final permutation on a 64-bit block.
     * @param input The 64-bit block to permute.
     * @return The permuted 64-bit block.
     */
    std::bitset<64> 
    fPermutation(const std::bitset<64>& input) {
      std::bitset<64> output;
      for (int i = 0; i < 64; i++) {
          output[i] = input[i]; // Copy input bits directly (simplified permutation)
      }
      return output;
    }

    /**
     * @brief Encrypts a 64-bit plaintext block using DES.
     * @param plaintext The 64-bit plaintext block to encrypt.
     * @return The encrypted 64-bit block.
     */
    std::bitset<64> 
    encode(const std::bitset<64>& plaintext) {
      auto data = iPermutation(plaintext); // Initial permutation
      std::bitset<32> left(data.to_ullong() >> 32); // Split into left and right halves
      std::bitset<32> right(data.to_ullong());

      // Perform 16 rounds of DES
      for (int round = 0; round < 16; round++) {
          auto newRight = left ^ feistel(right, subkeys[round]); // Feistel function
          left = right; // Swap halves
          right = newRight;
      }

      // Combine left and right halves and apply final permutation
      uint64_t combined = (static_cast<uint64_t>(right.to_ullong()) << 32) | left.to_ullong();
      return fPermutation(std::bitset<64>(combined));
    }

    /**
     * @brief Decrypts a 64-bit ciphertext block using DES.
     * @param plaintext The 64-bit ciphertext block to decrypt.
     * @return The decrypted 64-bit block.
     */
    std::bitset<64> 
    decode(const std::bitset<64>& plaintext) {
      auto data = iPermutation(plaintext); // Initial permutation
      std::bitset<32> left(data.to_ullong() >> 32); // Split into left and right halves
      std::bitset<32> right(data.to_ullong());

      // Perform 16 rounds of DES in reverse order
      for (int round = 15; round >= 0; --round) {
          auto newRight = left ^ feistel(right, subkeys[round]); // Feistel function
          left = right; // Swap halves
          right = newRight;
      }

      // Combine left and right halves and apply final permutation
      uint64_t combined = (static_cast<uint64_t>(right.to_ullong()) << 32) | left.to_ullong();
      return fPermutation(std::bitset<64>(combined));
    }

    /**
     * @brief Converts a string to a 64-bit bitset.
     * @param block The string to convert (must be 8 characters).
     * @return The 64-bit bitset representation of the string.
     */
    std::bitset<64> 
    stringToBitset64(const std::string& block) {
      uint64_t bits = 0;
      for (int i = 0; i < block.size(); i++) {
          bits |= (uint64_t)(unsigned char)block[i] << ((7 - i) * 8); // Map each character to its position
      }
      return std::bitset<64>(bits);
    }

    /**
     * @brief Converts a 64-bit bitset to a string.
     * @param bits The 64-bit bitset to convert.
     * @return The string representation of the bitset.
     */
    std::string 
    bitset64ToString(const std::bitset<64>& bits) {
      std::string result(8, '\0');
      uint64_t val = bits.to_ullong();

      for (int i = 0; i < 8; i++) {
          result[7 - i] = (val >> (i * 8)) & 0xFF; // Extract each byte
      }

      return result;
    }

private:
  std::bitset<64> key; // The main 64-bit key
  std::vector<std::bitset<48>> subkeys; // Subkeys for DES rounds

    // Simplified expansion table (E)
    const int EXPANSION_TABLE[48] = {
        32, 1, 2, 3, 4, 5,
        4, 5, 6, 7, 8, 9,
        8, 9,10,11,12,13,
        12,13,14,15,16,17,
        16,17,18,19,20,21,
        20,21,22,23,24,25,
        24,25,26,27,28,29,
        28,29,30,31,32,1
    };

    // Simplified permutation table (P)
    const int P_TABLE[32] = {
        16, 7, 20, 21,29,12,28,17,
         1,15,23,26, 5,18,31,10,
         2, 8,24,14,32,27, 3, 9,
        19,13,30, 6,22,11, 4,25
    };

    // Example S-Box (simplified)
    const int SBOX[4][16] = {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    };
};
