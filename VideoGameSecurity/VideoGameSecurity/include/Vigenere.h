#pragma once
#include "Prerequisites.h"

/**
 * @class Vigenere
 * @brief Implements the Vigenere cipher for encoding and decoding text.
 *
 * The Vigenere cipher is a method of encrypting alphabetic text using a series of Caesar ciphers
 * based on the letters of a keyword. This class provides methods to encode and decode text using
 * a given key.
 */
class 
Vigenere {
public:
  /**
   * @brief Default constructor.
   *
   * Creates an instance of the Vigenere class without initializing a key.
   */
  Vigenere() = default;

  /**
   * @brief Constructor with key initialization.
   *
   * @param key The encryption key used for encoding and decoding text.
   * @throws std::invalid_argument If the key is empty or contains no alphabetic characters.
   */
  Vigenere(const std::string& key) : key(normalizeKey(key)) {
    if (key.empty()) {
      throw std::invalid_argument("The key cannot be empty or contain no letters.");
    }
  }

  /**
   * @brief Normalizes the encryption key.
   *
   * Converts the key to uppercase and removes non-alphabetic characters.
   *
   * @param rawKey The raw key provided by the user.
   * @return A normalized key containing only uppercase alphabetic characters.
   */
  static std::string
  normalizeKey(const std::string& rawKey) {
    std::string k;
    for (char c : rawKey) {
      if (std::isalpha(static_cast<unsigned char>(c))) {
        k += std::toupper(static_cast<unsigned char>(c));
      }
    }
    return k;
  }

  /**
   * @brief Encodes a given text using the Vigenere cipher.
   *
   * Each alphabetic character in the text is shifted based on the corresponding character
   * in the key. Non-alphabetic characters remain unchanged.
   *
   * @param text The text to be encoded.
   * @return The encoded text.
   */
  std::string
  encode(const std::string& text) {
    std::string result;
    result.reserve(text.size());
    unsigned int i = 0;

    for (char c : text) {
      if (std::isalpha(static_cast<unsigned char>(c))) {
        bool isLower = std::islower(static_cast<unsigned char>(c));
        char base = isLower ? 'a' : 'A';
        int shift = key[i % key.size()] - 'A';
        char encodedChar = static_cast<char>((c - base + shift) % 26 + base);
        result += encodedChar;
        ++i;
      }
      else {
        result += c;
      }
    }
    return result;
  }

  /**
   * @brief Decodes a given text using the Vigenere cipher.
   *
   * Each alphabetic character in the text is shifted back based on the corresponding character
   * in the key. Non-alphabetic characters remain unchanged.
   *
   * @param text The text to be decoded.
   * @return The decoded text.
   */
  std::string
  decode(const std::string& text) {
    std::string result;
    result.reserve(text.size());
    unsigned int i = 0;

    for (char c : text) {
      if (std::isalpha(static_cast<unsigned char>(c))) {
        bool isLower = std::islower(static_cast<unsigned char>(c));
        char base = isLower ? 'a' : 'A';
        int shift = key[i % key.size()] - 'A';
        char decodedChar = static_cast<char>(((c - base) - shift + 26) % 26 + base);
        result += decodedChar;
        ++i;
      }
      else {
        result += c;
      }
    }
    return result;
  }

  /*
  * @brief Calculates the fitness score of a given text based on the frequency of common words.
  * 
  * @summary This function evaluates how well a decoded text matches common English words.
  * @param text The text to be evaluated.
  */
  static double 
  fitness(const std::string& text) {
    static const std::vector<std::string> commonWords = {
      "THE", "AND", "TO", "OF", "A", "IN", "IS", "IT", "THAT", "HE",
      "WAS", "FOR", "ON", "ARE", "AS", "WITH", "HIS", "AT", "BY", "NEW",
    };

    double score = 0.0;
    for (auto& word : commonWords) {
      size_t pos = 0;
      while ((pos = text.find(word, pos)) != std::string::npos) {
        score += word.length(); // Increment score for each occurrence of a common word
        pos += word.length();
      }
    }

  }

  /*
  * @brief Breaks the Vigenere cipher encryption using a brute-force attack.
  * 
  * @summary This function attempts to find the best key for decrypting a given text by trying all possible keys up to a specified length.
  * @param text The encrypted text to be decoded.
  * @param maxKeyLenght The maximum length of the key to be tested.
  * 
  */
  static std::string 
  breakEncryption(const std::string& text, int maxKeyLenght) {
    std::string bestKey;
    std::string bestText;
    std::string trailKey;
    
    double bestScore = std::numeric_limits<double>::infinity(); // Initialize to infinity for minimization

    std::function<void(int, int)>dfs=[&](int pos, int maxLen) {
      if (pos == maxLen) {
        Vigenere v(trailKey);
        std::string decodedText = v.decode(text);
        double score = fitness(decodedText);
        if (score < bestScore) {
          bestScore = score;
          bestKey = trailKey;
          bestText = decodedText;
        }
        return;
      }
      for (char c = 'A'; c <= 'Z'; ++c) {
        trailKey[pos] = c;
        dfs(pos + 1, maxLen);
      }
    };

    for (int len = 1; len <= maxKeyLenght; ++len) {
      trailKey.assign(len, 'A');
      dfs(0, len);
    }

    std::cout << "***BRUTE FORCE ATTACK VIGENERE ***\n";
    std::cout << "Best key: " << bestKey << "\n";
    std::cout << "Best decoded text: " << bestText << "\n";
    return bestKey;
  }

private:
  /**
   * @brief The encryption key used for encoding and decoding text.
   *
   * The key is normalized to contain only uppercase alphabetic characters.
   */
  std::string key;
};
