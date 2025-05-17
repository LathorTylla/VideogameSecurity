#include "CesarEncryption.h"

int main() {
  CaesarEncryption cripto;
  string textoOriginal;
  int clave;

  cout << "Enter the text to encrypt: ";
  getline(cin, textoOriginal);
  cout << "Enter the shift value: ";
  cin >> clave;

  string cifrado = cripto.EncryptionCaesar(textoOriginal, clave);
  string descifrado = cripto.decode(cifrado, clave);

  cout << "\nEncrypted text: " << cifrado << endl;
  cout << "Decrypted text: " << descifrado << endl;

  return 0;
}