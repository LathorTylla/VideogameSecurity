#include "Prerequisites.h"
#include "AsciiBinary.h"

/*
* This program converts a string to its binary representation and vice versa.
* It uses the AsciiBinary class to perform the conversions.
*/
int 
main() {
	AsciiBinary AB;

  std::string input = "Hello, World!";	// Example input string
  std::string binary = AB.stringToBinary(input);	// Convert string to binary
  std::cout << "Text to binary: " << binary << std::endl;	// Output the binary representation
  std::string message = AB.binaryToString(binary);	// Convert binary back to string
	std::cout << "Bimary to text: " << message << std::endl; // Output the original string
  // Check if the conversion back to string is correct
  if (input == message) {
    std::cout << "The conversion is correct" << std::endl;	// Confirm the conversion is correct
  } else {
    std::cout << "The conversion is incorrect." << std::endl;	// Indicate an error in conversion
  }

	return 0;
}