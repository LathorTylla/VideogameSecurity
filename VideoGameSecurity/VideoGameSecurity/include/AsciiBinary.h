#pragma 
#include "Prerequisites.h"

/**
 * @brief Class for converting between ASCII characters and binary representations.
 */
class
AsciiBinary {
public:
  AsciiBinary() = default;  // Default constructor
  ~AsciiBinary() = default; // Default destructor

	/**
	 * @brief Converts a single character to its binary representation.
	 * @param c The character to convert.
	 * @return A string containing the binary representation of the character (8 bits).
	 */
	std::string
	bitset(char c) {
    std::string result(8, '0'); // Initialize a string of 8 '0's
    int value = static_cast<unsigned char>(c); // Use unsigned char to handle extended ASCII characters correctly
		for (int i = 7; i >= 0; --i) {
      result[i] = (value % 2) + '0'; // Convert to character '0' or '1'
			value /= 2;
		}
		return result;
	}

	/**
	 * @brief Converts a string to its binary representation.
	 * @param input The string to convert.
	 * @return A string containing the binary representation of the input string, with each character's binary value separated by spaces.
   */
	std::string
	stringToBinary(const std::string& input) {
    std::ostringstream oss; // Use ostringstream for efficient string concatenation
		for (char c : input) {
      oss << bitset(c) << " "; // Append the binary representation of each character followed by a space
		}

		std::string output = oss.str();
		if (!output.empty()) {
			output.pop_back(); // Remove the trailing space
		}

		return output;
	}

	/*
  * @brief Converts a binary string to its corresponding ASCII character.
  * @param binary The binary string to convert (must be 8 bits).
	* @return The ASCII character corresponding to the binary string.
	*/
	char 
	binaryToChar(const std::string& binary) {
		int value = 0;
		for (char bit : binary) {
      value = value * 2 + (bit - '0'); // Convert '0' or '1' to integer
		}

		return static_cast<char>(value);
	}

	/**
	 * @brief Converts a binary string (with space-separated binary values) to its corresponding ASCII string.
	 * @param binaryInput The binary string to convert.
	 * @return The ASCII string corresponding to the binary input.
   */
	std::string
	binaryToString(const std::string& binaryInput) {
		std::istringstream iss(binaryInput);
    std::string result;// Initialize an empty result string
    std::string binary;// Temporary string to hold each binary value

		while (iss >> binary) {
      result += binaryToChar(binary); // Convert each binary value to character and append to result
		}
		return result;
	}

private:

};