#pragma once
#include "Prerequisites.h"
#include "XOREncoder.h"

class 
FileProtector {
public:
  FileProtector() = default;
  ~FileProtector() = default;

  // Sólo carga y parseo de archivo
  bool 
  CargarArchivo(const std::string& filename) {
    registros.clear();
    std::ifstream archivo(filename);
    if (!archivo.is_open()) {
      std::cout << "ERROR: No se pudo abrir " << filename << std::endl;
      return false;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
      if (linea.empty()) continue;
      size_t pos1 = linea.find(':');
      size_t pos2 = linea.find(':', pos1 + 1);
      if (pos1 != std::string::npos && pos2 != std::string::npos) {
        SensitiveData dato;
        dato.user = linea.substr(0, pos1);
        dato.password = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        dato.others = linea.substr(pos2 + 1);
        registros.push_back(dato);
      }
    }

    archivo.close();
    return true;
  }

private:
  std::vector<SensitiveData> registros;
};