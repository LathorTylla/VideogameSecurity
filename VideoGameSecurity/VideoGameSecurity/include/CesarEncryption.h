#include <iostream>
#include <string>
using namespace std;

/*
*  @brief This class implements the Caesar cipher encryption and decryption.
* It shifts letters and numbers by a specified amount.
* It handles both uppercase and lowercase letters, as well as digits.
*/
class CaesarEncryption {
public:
  CaesarEncryption() = default;
  ~CaesarEncryption() = default;

  /// Encrypts the input text using the Caesar cipher with a specified shift.
  string EncryptionCaesar(const string& text, int shift) {
    string result = "";

    // Ensure the shift is within the range of 0-25 for letters and 0-9 for digits
    for (int i = 0; i < text.size(); i++) {
      char posActual = text[i]; 

      //Ensure the shift is within the range of 0-25 for letters 
      if (posActual >= 'a' && posActual <= 'z') { 
        char newPos = ((posActual - 'a' + shift) % 26) + 'a';
        result += newPos;
      }
      // Ensure the shift is within the range of 0-25 for uppercase letters
      else if (posActual >= 'A' && posActual <= 'Z') {
        char newPos = ((posActual - 'A' + shift) % 26) + 'A';
        result += newPos;
      }

      // Ensure the shift is within the range of 0-9 for digits
      else if (posActual >= '0' && posActual <= '9') { 
        char newPos = ((posActual - '0' + shift) % 10) + '0';
        result += newPos;
      }
      // If the character is not a letter or digit, keep it unchanged
      else {
        result += posActual;
      }
    }
    return result;
  }

  /// Decrypts the input text using the Caesar cipher with a specified shift.
  string decode(const string& text, int shift) {
    return EncryptionCaesar(text, 26 - (shift % 26));
  }

  void bruteForceAttack(const string& text) {
    for (int i = 1; i < 26; i++) {
      cout << "Shift " << i << ": " << decode(text, i) << endl;
    }
  }
};