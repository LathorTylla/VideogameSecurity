#include "Prerequisites.h"
#include "CryptoGenerator.h"

int 
main() {
	CryptoGenerator cryptoGen;
	cryptoGen.generatePassword(16); 

	auto randomBytes = cryptoGen.generateBytes(16);
	std::cout << "Random Bytes (hex): " << cryptoGen.toHex(randomBytes) << std::endl;

	auto key128 = cryptoGen.generateKey(128);
	std::cout << "Key 128-bit (hex): " << cryptoGen.toHex(key128) << std::endl;

	auto iv = cryptoGen.generateIV(16);
	std::cout << "IV 128-bit (hex): " << cryptoGen.toHex(iv) << "\n";

	auto salt = cryptoGen.generateSalt(16);
	std::cout << "Salt (Base64): " << cryptoGen.toBase64(salt) << "\n";

	
	std::string base64String = cryptoGen.toBase64(salt); 
	std::cout << "Base64: " << base64String << "\n";

	auto fromBase64 = cryptoGen.fromBase64(base64String);
	std::cout << "From Base64: " << cryptoGen.toHex(fromBase64) << "\n";


	return 0;
}
