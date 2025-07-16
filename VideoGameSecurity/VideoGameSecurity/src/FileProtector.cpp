#include "FileProtector.h"

bool
FileProtector::CargarArchivo(const std::string& filename) {
  registros.clear();

  std::ifstream archivo(filename);
  if (!archivo.is_open()) {
    std::cout << "ERROR: No se pudo abrir " << filename << std::endl;
    return false;
  }

  std::string linea;

  while (std::getline(archivo, linea)) {
    // Salta lineas vacias
    if (linea.empty()) {
      continue;
    }

    // Busca los separadores
    size_t pos1 = linea.find(':');
    size_t pos2 = linea.find(':', pos1 + 1);

    if (pos1 != std::string::npos && pos2 != std::string::npos) {
      ImportantInfo dato;
      dato.user = linea.substr(0, pos1);
      dato.password = linea.substr(pos1 + 1, pos2 - pos1 - 1);
      dato.others = linea.substr(pos2 + 1);

      registros.push_back(dato);
    }
  }

  archivo.close();
  std::cout << "\n[OK] Se cargaron " << registros.size() << " registros del archivo." << std::endl;
  return true;
}

bool
FileProtector::CifrarXOR(const std::string& archivoSalida,
                         const std::string& clave) {
  // Verifica que haya datos para cifrar
  if (registros.empty()) {
    std::cout << "ERROR: No hay registros para cifrar" << std::endl;
    return false;
  }

  // Abre el archivo de salida
  std::ofstream salida(archivoSalida);
  if (!salida.is_open()) {
    std::cout << "ERROR: No se pudo crear " << archivoSalida << std::endl;
    return false;
  }

  // Crea el codificador XOR
  XOREncoder codificador;

  // Recorre los registros y los cifra
  int contador = 0;
  for (size_t i = 0; i < registros.size(); i++) {
    // Crea una linea con los datos
    std::string lineaOriginal = registros[i].user + ":" +
                                registros[i].password + ":" +
                                registros[i].others;

    // Cifra la linea
    std::string lineaCifrada = codificador.encode(lineaOriginal, clave);

    // Escribe al archivo
    salida << lineaCifrada << std::endl;
    contador++;
  }

  salida.close();
  std::cout << "\n[OK] Se cifraron " << contador << " registros con XOR" << std::endl;
  return true;
}

bool
FileProtector::CifrarCaesar(const std::string& archivoSalida,
                            int desplazamiento) {
  if (registros.empty()) {
    std::cout << "ERROR: No hay registros para cifrar" << std::endl;
    return false;
  }

  std::ofstream salida(archivoSalida);
  if (!salida.is_open()) {
    std::cout << "ERROR: No se pudo crear " << archivoSalida << std::endl;
    return false;
  }

  // Crea el codificador Caesar
  CesarEncryption cesar;
  int contador = 0;

  for (size_t i = 0; i < registros.size(); i++) {
    std::string lineaOriginal = registros[i].user + ":" +
                                registros[i].password + ":" +
                                registros[i].others;

    // Cifra con Caesar
    std::string lineaCifrada = cesar.encode(lineaOriginal, desplazamiento);

    salida << lineaCifrada << std::endl;
    contador++;
  }

  salida.close();
  std::cout << "\n[OK] Se cifraron " << contador << " registros con Caesar" << std::endl;
  return true;
}

bool
FileProtector::CifrarASCIIBinary(const std::string& archivoSalida) {
  if (registros.empty()) {
    std::cout << "ERROR: No hay registros para cifrar" << std::endl;
    return false;
  }

  std::ofstream salida(archivoSalida);
  if (!salida.is_open()) {
    std::cout << "ERROR: No se pudo crear " << archivoSalida << std::endl;
    return false;
  }

  // Crea el codificador ASCII-Binary
  AsciiBinary ascii;
  int contador = 0;

  for (size_t i = 0; i < registros.size(); i++) {
    std::string lineaOriginal = registros[i].user + ":" +
                                registros[i].password + ":" +
                                registros[i].others;

    // Convierte a binario
    std::string lineaCifrada = ascii.stringToBinary(lineaOriginal);

    salida << lineaCifrada << std::endl;
    contador++;
  }

  salida.close();
  std::cout << "\n[OK] Se cifraron " << contador << " registros con ASCII-Binary" << std::endl;
  return true;
}

bool
FileProtector::CifrarVigenere(const std::string& archivoSalida,
                              const std::string& clave) {
  if (registros.empty()) {
    std::cout << "ERROR: No hay registros para cifrar" << std::endl;
    return false;
  }

  std::ofstream salida(archivoSalida);
  if (!salida.is_open()) {
    std::cout << "ERROR: No se pudo crear " << archivoSalida << std::endl;
    return false;
  }

  // Crea el codificador Vigenere
  Vigenere vig(clave);
  int contador = 0;

  for (size_t i = 0; i < registros.size(); i++) {
    std::string lineaOriginal = registros[i].user + ":" +
                                registros[i].password + ":" +
                                registros[i].others;

    // Cifra con Vigenere
    std::string lineaCifrada = vig.encode(lineaOriginal);

    salida << lineaCifrada << std::endl;
    contador++;
  }

  salida.close();
  std::cout << "\n[OK] Se cifraron " << contador << " registros con Vigenere" << std::endl;
  return true;
}

bool
FileProtector::DescifrarXOR(const std::string& archivoCifrado,
                            const std::string& clave) {
  registros.clear();

  std::ifstream entrada(archivoCifrado);
  if (!entrada.is_open()) {
    std::cout << "ERROR: No se pudo abrir " << archivoCifrado << std::endl;
    return false;
  }

  XOREncoder codificador;
  std::string lineaCifrada;
  int contador = 0;

  while (std::getline(entrada, lineaCifrada)) {
    if (lineaCifrada.empty()) {
      continue;
    }

    // Descifra la linea
    std::string lineaOriginal = codificador.encode(lineaCifrada, clave);

    // Extrae los campos
    size_t pos1 = lineaOriginal.find(':');
    size_t pos2 = lineaOriginal.find(':', pos1 + 1);

    if (pos1 != std::string::npos && pos2 != std::string::npos) {
      ImportantInfo dato;
      dato.user = lineaOriginal.substr(0, pos1);
      dato.password = lineaOriginal.substr(pos1 + 1, pos2 - pos1 - 1);
      dato.others = lineaOriginal.substr(pos2 + 1);

      registros.push_back(dato);
      contador++;
    }
  }

  entrada.close();
  std::cout << "\n[OK] Se descifraron " << contador << " registros con XOR" << std::endl;
  return true;
}

bool
FileProtector::DescifrarCaesar(const std::string& archivoCifrado,
  int desplazamiento) {
  registros.clear();

  std::ifstream entrada(archivoCifrado);
  if (!entrada.is_open()) {
    std::cout << "ERROR: No se pudo abrir " << archivoCifrado << std::endl;
    return false;
  }

  CesarEncryption cesar;
  std::string lineaCifrada;
  int contador = 0;

  while (std::getline(entrada, lineaCifrada)) {
    if (lineaCifrada.empty()) {
      continue;
    }

    // Descifra la linea
    std::string lineaOriginal = cesar.decode(lineaCifrada, desplazamiento);

    // Extrae los campos
    size_t pos1 = lineaOriginal.find(':');
    size_t pos2 = lineaOriginal.find(':', pos1 + 1);

    if (pos1 != std::string::npos && pos2 != std::string::npos) {
      ImportantInfo dato;
      dato.user = lineaOriginal.substr(0, pos1);
      dato.password = lineaOriginal.substr(pos1 + 1, pos2 - pos1 - 1);
      dato.others = lineaOriginal.substr(pos2 + 1);

      registros.push_back(dato);
      contador++;
    }
  }

  entrada.close();
  std::cout << "\n[OK] Se descifraron " << contador << " registros con Caesar" << std::endl;
  return true;
}

bool
FileProtector::DescifrarASCIIBinary(const std::string& archivoCifrado) {
  registros.clear();

  std::ifstream entrada(archivoCifrado);
  if (!entrada.is_open()) {
    std::cout << "ERROR: No se pudo abrir " << archivoCifrado << std::endl;
    return false;
  }

  AsciiBinary ascii;
  std::string lineaCifrada;
  int contador = 0;

  while (std::getline(entrada, lineaCifrada)) {
    if (lineaCifrada.empty()) {
      continue;
    }

    // Convierte de binario a string
    std::string lineaOriginal = ascii.binaryToString(lineaCifrada);

    // Extrae los campos
    size_t pos1 = lineaOriginal.find(':');
    size_t pos2 = lineaOriginal.find(':', pos1 + 1);

    if (pos1 != std::string::npos && pos2 != std::string::npos) {
      ImportantInfo dato;
      dato.user = lineaOriginal.substr(0, pos1);
      dato.password = lineaOriginal.substr(pos1 + 1, pos2 - pos1 - 1);
      dato.others = lineaOriginal.substr(pos2 + 1);

      registros.push_back(dato);
      contador++;
    }
  }

  entrada.close();
  std::cout << "\n[OK] Se descifraron " << contador << " registros con ASCII-Binary" << std::endl;
  return true;
}

bool
FileProtector::DescifrarVigenere(const std::string& archivoCifrado,
  const std::string& clave) {
  registros.clear();

  std::ifstream entrada(archivoCifrado);
  if (!entrada.is_open()) {
    std::cout << "ERROR: No se pudo abrir " << archivoCifrado << std::endl;
    return false;
  }

  Vigenere vig(clave);
  std::string lineaCifrada;
  int contador = 0;

  while (std::getline(entrada, lineaCifrada)) {
    if (lineaCifrada.empty()) {
      continue;
    }

    // Descifra la linea
    std::string lineaOriginal = vig.decode(lineaCifrada);

    // Extrae los campos
    size_t pos1 = lineaOriginal.find(':');
    size_t pos2 = lineaOriginal.find(':', pos1 + 1);

    if (pos1 != std::string::npos && pos2 != std::string::npos) {
      ImportantInfo dato;
      dato.user = lineaOriginal.substr(0, pos1);
      dato.password = lineaOriginal.substr(pos1 + 1, pos2 - pos1 - 1);
      dato.others = lineaOriginal.substr(pos2 + 1);

      registros.push_back(dato);
      contador++;
    }
  }

  entrada.close();
  std::cout << "\n[OK] Se descifraron " << contador << " registros con Vigenere" << std::endl;
  return true;
}

bool
FileProtector::GuardarEnArchivo(const std::string& nombreArchivo) {
  if (registros.empty()) {
    std::cout << "ERROR: No hay datos para guardar" << std::endl;
    return false;
  }

  std::ofstream salida(nombreArchivo);
  if (!salida.is_open()) {
    std::cout << "ERROR: No se pudo crear " << nombreArchivo << std::endl;
    return false;
  }

  // Escribe cada registro
  int contador = 0;
  for (size_t i = 0; i < registros.size(); i++) {
    salida << registros[i].user << ":"
      << registros[i].password << ":"
      << registros[i].others << std::endl;
    contador++;
  }

  salida.close();
  std::cout << "\n[OK] Se guardaron " << contador << " registros en el archivo" << std::endl;
  return true;
}