#pragma once
#include "Prerequisites.h"

/**
 * @brief Provides cryptographic utility functions for password and key generation, encoding, and validation.
 *
 * @details
 * The CryptoGenerator class offers a set of methods for generating random passwords, cryptographic keys,
 * initialization vectors (IVs), salts, and for encoding/decoding data in hexadecimal and Base64 formats.
 * It also includes password validation, entropy estimation, and secure memory wiping utilities.
 * All random data is generated using a Mersenne Twister engine seeded with a random device.
 */
class 
CryptoGenerator {
public:
  /**
   * @brief Constructs a CryptoGenerator and seeds the random engine.
   *
   * @details
   * Uses std::random_device to seed the Mersenne Twister engine for secure random number generation.
   */
  CryptoGenerator() {
    std::random_device rd;      // Hardware entropy source
    m_engine.seed(rd());        // Seed the random engine
  }

  /**
   * @brief Default destructor.
   */
  ~CryptoGenerator() = default;

  /**
   * @brief Generates a random password with customizable character sets.
   *
   * @param length The desired length of the password.
   * @param useUpper Whether to include uppercase letters (A-Z).
   * @param useLower Whether to include lowercase letters (a-z).
   * @param useDigits Whether to include digits (0-9).
   * @param useSymbols Whether to include symbols (e.g., !@#$).
   * @return std::string The generated password.
   *
   * @throws std::runtime_error If no character types are enabled.
   *
   * @details
   * Builds a character pool based on the enabled options, then randomly selects characters
   * from this pool to construct the password. Throws if the pool is empty.
   */
  std::string 
  generatePassword(unsigned int length,
                   bool useUpper = true,
                   bool useLower = true,
                   bool useDigits = true,
                   bool useSymbols = false) {
    const std::string uppers = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string lowers = "abcdefghijklmnopqrstuvwxyz";
    const std::string digits = "0123456789";
    const std::string symbols = "!@#$%^&*()-_=+[]{}|;:',.<>?/";

    std::string pool;
    if (useUpper) pool += uppers;
    if (useLower) pool += lowers;
    if (useDigits) pool += digits;
    if (useSymbols) pool += symbols;

    if (pool.empty()) {
      throw std::runtime_error("No character types enabled for password generation.");
    }

    std::uniform_int_distribution<unsigned int> dist(0, pool.size() - 1);
    std::string password;
    password.reserve(length);  // Reserve memory for efficiency

    // Randomly select characters from the pool
    for (unsigned int i = 0; i < length; ++i) {
      password += pool[dist(m_engine)];
    }
    return password;
  }

  /**
   * @brief Generates a vector of random bytes.
   *
   * @param numBytes Number of bytes to generate.
   * @return std::vector<uint8_t> Vector containing random bytes.
   *
   * @details
   * Each byte is generated using a uniform distribution in the range [0, 255].
   */
  std::vector<uint8_t> 
  generateBytes(unsigned int numBytes) {
    std::vector<uint8_t> bytes(numBytes);
    std::uniform_int_distribution<int> dist(0, 255);
    for (unsigned int i = 0; i < numBytes; ++i) {
      bytes[i] = static_cast<uint8_t>(dist(m_engine));
    }
    return bytes;
  }

  /**
   * @brief Converts a byte vector to a hexadecimal string.
   *
   * @param data The input byte vector.
   * @return std::string Hexadecimal representation of the data.
   *
   * @details
   * Each byte is converted to two hexadecimal characters.
   */
  std::string 
  toHex(const std::vector<uint8_t>& data) {
    std::ostringstream oss;
    for (const auto& byte : data) {
      oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }
    return oss.str();
  }

  /**
   * @brief Converts a hexadecimal string to a byte vector.
   *
   * @param hex The input hexadecimal string.
   * @return std::vector<uint8_t> The decoded byte vector.
   *
   * @throws std::runtime_error If the hex string has an odd length.
   *
   * @details
   * Parses each pair of hex characters into a byte.
   */
  std::vector<uint8_t> 
  fromHex(const std::string& hex) {
    if (hex.size() % 2 != 0)
      throw std::runtime_error("Invalid hex (odd length).");

    std::vector<uint8_t> data(hex.size() / 2);
    for (size_t i = 0; i < data.size(); ++i) {
      unsigned int byte;
      std::istringstream(hex.substr(2 * i, 2)) >> std::hex >> byte;
      data[i] = static_cast<uint8_t>(byte);
    }
    return data;
  }

  /**
   * @brief Generates a cryptographic key of the specified bit length.
   *
   * @param bits The length of the key in bits (must be a multiple of 8).
   * @return std::vector<uint8_t> The generated key as a byte vector.
   *
   * @throws std::runtime_error If bits is not a multiple of 8.
   *
   * @details
   * Calls generateBytes with the corresponding byte length.
   */
  std::vector<uint8_t> 
  generateKey(unsigned int bits) {
    if (bits % 8 != 0) {
      throw std::runtime_error("Bits must be a multiple of 8.");
    }
    return generateBytes(bits / 8);
  }

  /**
   * @brief Generates a random initialization vector (IV).
   *
   * @param blockSize The size of the IV in bytes.
   * @return std::vector<uint8_t> The generated IV.
   *
   * @details
   * Calls generateBytes with the specified block size.
   */
  std::vector<uint8_t> 
  generateIV(unsigned int blockSize) {
    return generateBytes(blockSize);
  }

  /**
   * @brief Generates a random salt.
   *
   * @param length The length of the salt in bytes.
   * @return std::vector<uint8_t> The generated salt.
   *
   * @details
   * Calls generateBytes with the specified length.
   */
  std::vector<uint8_t> 
  generateSalt(unsigned int length) {
    return generateBytes(length);
  }

  /**
   * @brief Encodes a byte vector to a Base64 string.
   *
   * @param data The input byte vector.
   * @return std::string The Base64-encoded string.
   *
   * @details
   * Processes input in 3-byte blocks, encoding each to 4 Base64 characters.
   * Pads the output with '=' if the input is not a multiple of 3 bytes.
   */
  std::string 
  toBase64(const std::vector<uint8_t>& data) {
    static const char* table =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
      "abcdefghijklmnopqrstuvwxyz"
      "0123456789+/";
    std::string b64;
    unsigned int i = 0;

    // Process input in 3-byte blocks
    while (i + 2 < data.size()) {
      unsigned int block = (data[i] << 16) | (data[i + 1] << 8) | data[i + 2];
      b64 += table[(block >> 18) & 0x3F];
      b64 += table[(block >> 12) & 0x3F];
      b64 += table[(block >> 6) & 0x3F];
      b64 += table[(block) & 0x3F];
      i += 3;
    }

    // Handle padding for remaining bytes
    if (i < data.size()) {
      uint32_t block = data[i] << 16;
      b64 += table[(block >> 18) & 0x3F];
      if (i + 1 < data.size()) {
        block |= data[i + 1] << 8;
        b64 += table[(block >> 12) & 0x3F];
        b64 += table[(block >> 6) & 0x3F];
        b64 += '=';
      }
      else {
        b64 += table[(block >> 12) & 0x3F];
        b64 += "==";
      }
    }

    return b64;
  }

  /**
   * @brief Decodes a Base64 string to a byte vector.
   *
   * @param b64 The Base64-encoded string.
   * @return std::vector<uint8_t> The decoded byte vector.
   *
   * @details
   * Uses a decoding table to map Base64 characters to their values.
   * Ignores invalid characters and handles padding.
   * Thread-safe via mutex.
   */
  std::vector<uint8_t> 
  fromBase64(const std::string& b64) {
    std::lock_guard<std::mutex> lock(_mtx); // Ensure thread safety
    std::vector<uint8_t> out;
    size_t len = b64.size();
    size_t pad = 0;

    // Count padding characters
    if (len >= 1 && b64[len - 1] == '=') pad++;
    if (len >= 2 && b64[len - 2] == '=') pad++;
    out.reserve(((len / 4) * 3) - pad);

    unsigned int i = 0;
    while (i < len) {
      uint32_t block = 0;
      unsigned int chars = 0;
      // Decode up to 4 Base64 characters into a 24-bit block
      for (unsigned int j = 0; j < 4 && i < len; ++j, ++i) {
        uint8_t v = _decTable[(unsigned char)b64[i]];
        if (v == 0xFF) { j--; continue; } // Skip invalid chars
        block = (block << 6) | v;
        chars++;
      }
      // Extract bytes from the block
      for (unsigned int k = 0; k < chars - 1; ++k) {
        out.push_back((block >> (8 * (chars - 2 - k))) & 0xFF);
      }
    }
    return out;
  }

  /**
   * @brief Securely wipes the contents of a byte vector.
   *
   * @param data The byte vector to wipe.
   *
   * @details
   * Overwrites all bytes with zero to prevent sensitive data from lingering in memory.
   */
  void 
  secureWipe(std::vector<uint8_t>& data) {
    std::fill(data.begin(), data.end(), 0);
  }

  /**
   * @brief Validates a password for minimum security requirements.
   *
   * @param password The password to validate.
   * @return bool True if the password meets all requirements, false otherwise.
   *
   * @details
   * Checks for minimum length (8), and presence of uppercase, lowercase, digit, and symbol.
   */
  bool 
  validatePassword(const std::string& password) {
    if (password.size() < 8) return false;
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSymbols = false;
    for (char c : password) {
      if (std::isupper((unsigned char)c)) {
        hasUpper = true;
      }
      else if (std::islower((unsigned char)c)) {
        hasLower = true;
      }
      else if (std::isdigit((unsigned char)c)) {
        hasDigit = true;
      }
      else if (std::ispunct((unsigned char)c)) {
        hasSymbols = true;
      }
    }
    return hasUpper && hasLower && hasDigit && hasSymbols;
  }

  /**
   * @brief Estimates the entropy of a password in bits.
   *
   * @param password The password to analyze.
   * @return double The estimated entropy in bits.
   *
   * @details
   * Calculates entropy as log2(poolSize) * password length, where poolSize is the number of unique character types used.
   */
  double 
  estimateEntropy(const std::string& password) {
    if (password.size() == 0) {
      return 0.0;
    }
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSymbols = false;
    for (char c : password) {
      if (std::isupper((unsigned char)c)) {
        hasUpper = true;
      }
      else if (std::islower((unsigned char)c)) {
        hasLower = true;
      }
      else if (std::isdigit((unsigned char)c)) {
        hasDigit = true;
      }
      else if (std::ispunct((unsigned char)c)) {
        hasSymbols = true;
      }
    }
    unsigned int poolSize = 0;
    if (hasLower) {
      poolSize += 26;  // 26 lowercase letters
    }
    if (hasUpper) {
      poolSize += 26;  // 26 uppercase letters
    }
    if (hasDigit) {
      poolSize += 10;  // 10 digits (0-9)
    }
    if (hasSymbols) {
      poolSize += 32;  // Approx. 32 common symbols
    }
    if (poolSize == 0) {
      std::cout << "No character types enabled for entropy estimation." << std::endl;
      return 0.0;  // No valid characters, entropy is 0
    }
    double entropy = password.size() * std::log2(static_cast<double>(poolSize));  // Entropy formula
    return entropy;
  }

  /**
   * @brief Returns a human-readable password strength based on entropy.
   *
   * @param password The password to evaluate.
   * @return std::string The strength description ("Very Weak", "Weak", "Moderate", "Strong", "Very Strong").
   *
   * @details
   * Uses entropy thresholds to classify password strength.
   */
  std::string 
  passwordStrength(const std::string& password) {
    double entropy = estimateEntropy(password);
    if (entropy < 28) {
      return "Very Weak";  // Entropy < 28 bits
    }
    else if (entropy < 40) {
      return "Weak";       // Entropy 28-40 bits
    }
    else if (entropy < 60) {
      return "Moderate";   // Entropy 40-60 bits
    }
    else if (entropy < 80) {
      return "Strong";     // Entropy 60-80 bits
    }
    else {
      return "Very Strong"; // Entropy >= 80 bits
    }


  }

  /**
   * @brief Generates multiple passwords and returns the ones with highest entropy.
   *
   * @param length The desired length of the passwords.
   * @param count The number of candidates to generate.
   * @param topResults The number of top results to return.
   * @return std::vector<PasswordWithEntropy> Vector of top passwords with their entropy values.
   *
   * @details
   * Generates 'count' password candidates using all character sets to maximize entropy,
   * then selects the 'topResults' passwords with the highest calculated entropy.
   * Always includes uppercase, lowercase, digits, and symbols to maximize entropy.
   */

  struct 
  PasswordWithEntropy {
    std::string password;  // The generated password
    double entropy;        // The entropy of the password
  };

  std::vector<PasswordWithEntropy>
  generateHighEntropyPasswords(unsigned int length,
                               unsigned int count = 20,
                               unsigned int topResults = 3) {
    // Create a vector to hold password candidates
    std::vector<PasswordWithEntropy> candidates;

    // Generate multiple password candidates
    for (unsigned int i = 0; i < count; i++) {
      // Generate a password with all character types to make it strong
      std::string password = generatePassword(length, true, true, true, true);

      // Calculate the entropy of this password
      double entropy = estimateEntropy(password);

      // Create a PasswordWithEntropy object
      PasswordWithEntropy passwordData;
      passwordData.password = password;
      passwordData.entropy = entropy;

      // Add this password and its entropy to our candidates list
      candidates.push_back(passwordData);
    }

    // Find the passwords with the highest entropy
    // Sort the candidates by entropy (highest to lowest)
    for (unsigned int i = 0; i < candidates.size() - 1; i++) {
      for (unsigned int j = 0; j < candidates.size() - i - 1; j++) {
        // If this password has lower entropy than the next one, swap them
        if (candidates[j].entropy < candidates[j + 1].entropy) {
          PasswordWithEntropy temp = candidates[j];
          candidates[j] = candidates[j + 1];
          candidates[j + 1] = temp;
        }
      }
    }

    // Vector for top results
    std::vector<PasswordWithEntropy> topPasswords;

    // Get the top 'topResults' passwords (or fewer if we didn't generate that many)
    unsigned int resultCount = (topResults < candidates.size()) ? topResults : candidates.size();

    // Add the top passwords to results
    for (unsigned int i = 0; i < resultCount; i++) {
      topPasswords.push_back(candidates[i]);
    }

    return topPasswords;
  }

private:
  std::mt19937 m_engine;                // Mersenne Twister random number engine.
  std::mutex _mtx;                      // Mutex for thread-safe Base64 decoding.
  std::array<uint8_t, 256> _decTable;   // Base64 decoding table.
};