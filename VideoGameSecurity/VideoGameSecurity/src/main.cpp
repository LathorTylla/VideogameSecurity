#include "Prerequisites.h"
#include "CryptoGenerator.h"

/*
 * Step 1) Create an instance of CryptoGenerator.
 *         This object provides all cryptographic utility functions used below.
 */
int 
main() {
  CryptoGenerator cryptoGen;
  /*
   * Step 2) Generate a random password of 16 characters.
   *         By default, it uses uppercase, lowercase, and digits.
   *         (The result is not printed here, but the password is generated.)
   */
  cryptoGen.generatePassword(16); 
  /*
   * Step 3) Generate 16 random bytes.
   *         Print these bytes as a hexadecimal string.
   */
  auto randomBytes = cryptoGen.generateBytes(16);
  std::cout << "Random Bytes (hex): " << cryptoGen.toHex(randomBytes) << std::endl;
  /*
   * Step 4) Generate a 128-bit (16 bytes) cryptographic key.
   *         Print the key as a hexadecimal string.
   */
  auto key128 = cryptoGen.generateKey(128);
  std::cout << "Key 128-bit (hex): " << cryptoGen.toHex(key128) << std::endl;

  /*
   * Step 5) Generate a 128-bit (16 bytes) initialization vector (IV).
   *         Print the IV as a hexadecimal string.
   */
  auto iv = cryptoGen.generateIV(16);
  std::cout << "IV 128-bit (hex): " << cryptoGen.toHex(iv) << "\n";

  /*
   * Step 6) Generate a 16-byte random salt.
   *         Print the salt encoded in Base64 format.
   */
  auto salt = cryptoGen.generateSalt(16);
  std::cout << "Salt (Base64): " << cryptoGen.toBase64(salt) << "\n";

  /*
   * Step 7) Encode the salt to Base64 again and print it.
   *         (This is a repeat of the previous step for demonstration.)
   */
  std::string base64String = cryptoGen.toBase64(salt); 
  std::cout << "Base64: " << base64String << "\n";

  /*
   * Step 8) Decode the Base64 string back to bytes.
   *         Print the decoded bytes as a hexadecimal string.
   */
  auto fromBase64 = cryptoGen.fromBase64(base64String);
  std::cout << "From Base64: " << cryptoGen.toHex(fromBase64) << "\n";

  /*
   * Step 9) Estimate the entropy (randomness) of the Base64 string.
   *         Print a new random password and the estimated entropy and strength of the Base64 string.
   */
  std::string pwd = base64String;
  auto entropy = cryptoGen.estimateEntropy(pwd);
  std::cout << "Password 1: " << cryptoGen.generatePassword(16) << "\n";
  std::cout << "Estimated Entropy 1: " << entropy << " | " << cryptoGen.passwordStrength(pwd) << "\n";

  /*
   * Step 10) Estimate the entropy and strength of a custom password ("LathorPassword@234.").
   *          Print the password, its estimated entropy, and its strength.
   */
  auto entropy2 = cryptoGen.estimateEntropy("LathorPassword@234.");
  std::cout << "Password 2: " << "LathorPassword@23" << "\n";
  std::cout << "Estimated Entropy 2: " << entropy2 << " | " << cryptoGen.passwordStrength("LathorPassword@23") << "\n";

  /*
   * Step 11) Generate high entropy passwords and display the top 3 results.
   *          Show each password with its entropy value and strength rating.
   */
  std::cout << "\n******** High Entropy Passwords ********\n";
  auto topPasswords = cryptoGen.generateHighEntropyPasswords(16, 20, 3);
  for (size_t i = 0; i < topPasswords.size(); ++i) {
    // Access the password and entropy directly from the struct
    std::string password = topPasswords[i].password;
    double entropyValue = topPasswords[i].entropy;

    std::cout << "Password " << (i + 1) << ": " << password << "\n";
    std::cout << "Entropy: " << entropyValue << " bits | Strength: "
      << cryptoGen.passwordStrength(password) << "\n\n";
  }
    return 0;
}
