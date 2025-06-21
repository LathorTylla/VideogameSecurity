#include "Prerequisites.h"
#include "Vigenere.h"

int
main() {
	std::string text = "Dream away, This is a test";
	std::string key = "Lathor_Tylla18";

	std::cout << "Texto original: " << text << std::endl;
	std::cout << "Clave: " << key << std::endl;

	Vigenere vigenere(key);
	std::string encrypted = vigenere.encode(text);
	std::cout << "Texto cifrado: " << encrypted << std::endl;

	std::string decrypted = vigenere.decode(encrypted);
	std::cout << "Texto descifrado: " << decrypted << std::endl;


	return 0;
}