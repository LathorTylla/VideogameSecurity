#pragma once
#include "Prerequisites.h"
#include "XOREncoder.h"

class 
FileProtector {
public:
  /*
  * Constructor y Destructor por defecto
  */
  FileProtector() = default;
  ~FileProtector() = default;

  /*
  * @brief Carga informacion desde un archivo de texto
  * @param filename Ruta del archivo a cargar
  * @return true si cargo correctamente
  */
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
    return true;
  }

  /*
  * @brief Cifra los datos y los guarda en un archivo
  * @param archivoSalida Nombre del archivo cifrado
  * @param clave Clave para cifrar
  * @return true si se guardo correctamente
  */
  bool 
  CifrarYGuardar(const std::string& archivoSalida, 
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

    // Crea el codificador
    XOREncoder codificador;

    // Recorre los registros y los cifra
    for (size_t i = 0; i < registros.size(); i++) {
      // Crea una linea con los datos
      std::string lineaOriginal = registros[i].user + ":" +
                                  registros[i].password + ":" +
                                  registros[i].others;

      // Cifra la linea
      std::string lineaCifrada = codificador.encode(lineaOriginal, clave);

      // Escribe al archivo
      salida << lineaCifrada << std::endl;
    }

    salida.close();
    return true;
  }

  /*
  * @brief Carga y descifra un archivo protegido
  * @param archivoCifrado Ruta del archivo cifrado
  * @param clave Clave para descifrar
  * @return true si descifro correctamente
  */
  bool 
  DescargarYDescifrar(const std::string& archivoCifrado, 
                      const std::string& clave) {
    // Limpia los registros previos
    registros.clear();

    // Verifica que el archivo exista
    std::ifstream entrada(archivoCifrado);
    if (!entrada.is_open()) {
      std::cout << "ERROR: No se pudo abrir " << archivoCifrado << std::endl;
      return false;
    }
    // Crea el codificador
    XOREncoder codificador; 
    // Recorre el archivo y descifra cada linea
    std::string lineaCifrada;

    // Lee linea por linea
    while (std::getline(entrada, 
                        lineaCifrada)) {
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
      }
    }

    entrada.close();
    return true;
  }

  /*
  * @brief Guarda los registros actuales en un archivo
  * @param nombreArchivo Donde guardar los datos
  * @return true si se guardo bien
  */
  bool 
  GuardarEnArchivo(const std::string& nombreArchivo) {
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
    for (size_t i = 0; i < registros.size(); i++) {
      salida << registros[i].user << ":"
             << registros[i].password << ":"
             << registros[i].others << std::endl;
    }

    salida.close();
    return true;
  }

private:
  std::vector<ImportantInfo> registros;
};