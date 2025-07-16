#include "Prerequisites.h"
#include "XOREncoder.h"
#include "FileProtector.h"

void 
mostrarMenu() {
  std::cout << "\n======== MENU ========" << std::endl;
  std::cout << "1. Cifrar archivo" << std::endl;
  std::cout << "2. Descifrar archivo" << std::endl;
  std::cout << "3. Salir" << std::endl;
  std::cout << "=====================" << std::endl;
  std::cout << "Opcion: ";
}

int 
main() {
  FileProtector protector;
  std::string opcion;

  //Carpeta de origen y destino
  const std::string CARPETA_CRUDOS = "bin/Datos crudos/"; // Carpeta donde se guardan los archivos sin cifrar
  const std::string CARPETA_CIFRADOS = "bin/Datos cif/";  // Carpeta donde se guardan los archivos cifrados

  std::cout << "\n*** SISTEMA DE CIFRADO XOR ***" << std::endl;
  std::cout << "Carpeta origen: " << CARPETA_CRUDOS << std::endl;
  std::cout << "Carpeta destino: " << CARPETA_CIFRADOS << std::endl;

  while (true) {
    mostrarMenu();
    std::getline(std::cin, opcion);

    if (opcion == "1") {
      // Cifrar archivo
      std::string nombreArchivo;  // Nombre del archivo a cifrar
      std::string nombreSalida;   // Nombre del archivo cifrado a guardar
      std::string clave;          // Clave de cifrado

      std::cout << "\n-- CIFRAR ARCHIVO --" << std::endl;
      std::cout << "Nombre del archivo con extension (.txt): ";
      std::getline(std::cin, nombreArchivo);  // Nombre del archivo a cifrar

      // Verifica que el nombre no esté vacío
      std::string rutaCompleta = CARPETA_CRUDOS + nombreArchivo;

      // Carga el archivo
      if (protector.CargarArchivo(rutaCompleta)) {
        std::cout << "Archivo cargado correctamente" << std::endl;

        std::cout << "\nNombre del nuevo archivo cifrado (sin extension): ";
        std::getline(std::cin, nombreSalida);

        std::cout << "Clave de cifrado: ";
        std::getline(std::cin, clave);

        // Agrega .txt y carpeta destino
        std::string rutaSalida = CARPETA_CIFRADOS + nombreSalida + ".txt";

        // Cifra y guarda
        if (protector.CifrarYGuardar(rutaSalida, clave)) {
          std::cout << "\nArchivo cifrado guardado como: " << rutaSalida << std::endl;
        }
      }
    }
    else if (opcion == "2") {
      // Descifrar archivo
      std::string nombreArchivo;
      std::string nombreSalida;
      std::string clave;

      std::cout << "\n-- DESCIFRAR ARCHIVO --" << std::endl;
      std::cout << "Nombre del archivo cifrado .txt: ";
      std::getline(std::cin, nombreArchivo);

      // Construye ruta completa
      std::string rutaCompleta = CARPETA_CIFRADOS + nombreArchivo;

      std::cout << "Clave de descifrado: ";
      std::getline(std::cin, clave);

      // Descifra
      if (protector.DescargarYDescifrar(rutaCompleta, clave)) {
        std::cout << "Archivo descifrado correctamente" << std::endl;

        std::cout << "\nNombre para guardar (sin extension): ";
        std::getline(std::cin, nombreSalida);

        // Guarda en carpeta de datos crudos
        std::string rutaSalida = CARPETA_CRUDOS + nombreSalida + ".txt";
        protector.GuardarEnArchivo(rutaSalida);

        std::cout << "Archivo guardado como: " << rutaSalida << std::endl;
      }
    }
    else if (opcion == "3") {
      std::cout << "\nCerrando programa..." << std::endl;
      break;
    }
    else {
      std::cout << "\nOpcion no valida" << std::endl;
    }
  }

  return 0;
}