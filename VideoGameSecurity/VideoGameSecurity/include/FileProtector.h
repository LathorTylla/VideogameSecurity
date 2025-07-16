#pragma once
#include "Prerequisites.h"
#include "XOREncoder.h"
#include "CesarEncryption.h"
#include "AsciiBinary.h"
#include "Vigenere.h"
#include "DES.h"

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
  CargarArchivo(const std::string& filename);

  /*
  * @brief Cifra con XOR y guarda en un archivo
  * @param archivoSalida Nombre del archivo cifrado
  * @param clave Clave para cifrar
  * @return true si se guardo correctamente
  */
  bool 
  CifrarXOR(const std::string& archivoSalida,
            const std::string& clave);

  /*
  * @brief Cifra con Caesar y guarda en un archivo
  * @param archivoSalida Nombre del archivo cifrado
  * @param desplazamiento Numero de posiciones a desplazar
  * @return true si se guardo correctamente
  */
  bool 
  CifrarCaesar(const std::string& archivoSalida,
               int desplazamiento);

  /*
  * @brief Cifra con ASCII-Binary y guarda en un archivo
  * @param archivoSalida Nombre del archivo cifrado
  * @return true si se guardo correctamente
  */
  bool 
  CifrarASCIIBinary(const std::string& archivoSalida);

  /*
  * @brief Cifra con Vigenere y guarda en un archivo
  * @param archivoSalida Nombre del archivo cifrado
  * @param clave Clave para cifrar
  * @return true si se guardo correctamente
  */
  bool 
  CifrarVigenere(const std::string& archivoSalida,
                 const std::string& clave);

  /*
  * @brief Descifra un archivo XOR
  * @param archivoCifrado Ruta del archivo cifrado
  * @param clave Clave para descifrar
  * @return true si descifro correctamente
  */
  bool 
  DescifrarXOR(const std::string& archivoCifrado,
               const std::string& clave);

  /*
  * @brief Descifra un archivo Caesar
  * @param archivoCifrado Ruta del archivo cifrado
  * @param desplazamiento Numero de posiciones
  * @return true si descifro correctamente
  */
  bool 
  DescifrarCaesar(const std::string& archivoCifrado,
                  int desplazamiento);

  /*
  * @brief Descifra un archivo ASCII-Binary
  * @param archivoCifrado Ruta del archivo cifrado
  * @return true si descifro correctamente
  */
  bool 
  DescifrarASCIIBinary(const std::string& archivoCifrado);

  /*
  * @brief Descifra un archivo Vigenere
  * @param archivoCifrado Ruta del archivo cifrado
  * @param clave Clave para descifrar
  * @return true si descifro correctamente
  */
  bool 
  DescifrarVigenere(const std::string& archivoCifrado,
                    const std::string& clave);
  /*
  * @brief Guarda los registros actuales en un archivo
  * @param nombreArchivo Donde guardar los datos
  * @return true si se guardo bien
  */
  bool 
  GuardarEnArchivo(const std::string& nombreArchivo);

private:
  std::vector<ImportantInfo> registros;
};