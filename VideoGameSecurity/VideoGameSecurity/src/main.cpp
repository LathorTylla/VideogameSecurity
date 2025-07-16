#include "Prerequisites.h"
#include "XOREncoder.h"
#include "FileProtector.h"
#include "CesarEncryption.h"
#include "AsciiBinary.h"
#include "Vigenere.h"
#include "DES.h"

void
mostrarMenu() {
  std::cout << "\n======== MENU PRINCIPAL ========" << std::endl;
  std::cout << "1. Cifrar archivo" << std::endl;
  std::cout << "2. Descifrar archivo" << std::endl;
  std::cout << "3. Salir" << std::endl;
  std::cout << "================================" << std::endl;
  std::cout << "Opcion: ";
}

void
mostrarMenuCifrados() {
  std::cout << "\n--- TIPOS DE CIFRADO ---" << std::endl;
  std::cout << "1. XOR" << std::endl;
  std::cout << "2. Caesar" << std::endl;
  std::cout << "3. ASCII-Binary" << std::endl;
  std::cout << "4. Vigenere" << std::endl;
  std::cout << "------------------------" << std::endl;
  std::cout << "Seleccione tipo de cifrado: ";
}

int
main() {
  FileProtector protector;
  std::string opcion;

  //Carpeta de origen y destino
  const std::string CARPETA_CRUDOS = "bin/Datos crudos/";
  const std::string CARPETA_CIFRADOS = "bin/Datos cif/";

  std::cout << "\n*** SISTEMA DE CIFRADO MULTIPLE ***" << std::endl;
  std::cout << "Carpeta origen: " << CARPETA_CRUDOS << std::endl;
  std::cout << "Carpeta destino: " << CARPETA_CIFRADOS << std::endl;

  while (true) {
    mostrarMenu();
    std::getline(std::cin, opcion);

    if (opcion == "1") {
      // Cifrar archivo
      std::string nombreArchivo;
      std::string nombreSalida;
      std::string tipoCifrado;

      std::cout << "\n-- CIFRAR ARCHIVO --" << std::endl;
      std::cout << "Nombre del archivo con extension al final (.txt): ";
      std::getline(std::cin, nombreArchivo);

      // Verifica que el nombre no esté vacío
      std::string rutaCompleta = CARPETA_CRUDOS + nombreArchivo;

      // Carga el archivo
      if (protector.CargarArchivo(rutaCompleta)) {
        std::cout << "Archivo cargado correctamente" << std::endl;

        // Muestra menu de cifrados
        mostrarMenuCifrados();
        std::getline(std::cin, tipoCifrado);

        std::cout << "\nNombre del archivo cifrado (sin extension): ";
        std::getline(std::cin, nombreSalida);

        // Ruta de salida
        std::string rutaSalida = CARPETA_CIFRADOS + nombreSalida + ".txt";

        // Cifra segun el tipo seleccionado
        if (tipoCifrado == "1") {
          // XOR
          std::string clave;
          std::cout << "Clave de cifrado XOR: ";
          std::getline(std::cin, clave);

          if (protector.CifrarXOR(rutaSalida, clave)) {
            std::cout << "\nArchivo cifrado con XOR guardado como: " << rutaSalida << std::endl;
          }
        }
        else if (tipoCifrado == "2") {
          // Caesar
          std::string desplazamientoStr;
          std::cout << "Desplazamiento Caesar (numero): ";
          std::getline(std::cin, desplazamientoStr);

          int desplazamiento = 0;
          // Convertir string a int de manera simple
          for (char c : desplazamientoStr) {
            if (c >= '0' && c <= '9') {
              desplazamiento = desplazamiento * 10 + (c - '0');
            }
          }

          if (protector.CifrarCaesar(rutaSalida, desplazamiento)) {
            std::cout << "\nArchivo cifrado con Caesar guardado como: " << rutaSalida << std::endl;
          }
        }
        else if (tipoCifrado == "3") {
          // ASCII-Binary
          if (protector.CifrarASCIIBinary(rutaSalida)) {
            std::cout << "\nArchivo cifrado con ASCII-Binary guardado como: " << rutaSalida << std::endl;
          }
        }
        else if (tipoCifrado == "4") {
          // Vigenere
          std::string clave;
          std::cout << "Clave de cifrado Vigenere: ";
          std::getline(std::cin, clave);

          if (protector.CifrarVigenere(rutaSalida, clave)) {
            std::cout << "\nArchivo cifrado con Vigenere guardado como: " << rutaSalida << std::endl;
          }
        }
        else {
          std::cout << "Opcion de cifrado no valida" << std::endl;
        }
      }
    }
    else if (opcion == "2") {
      // Descifrar archivo
      std::string nombreArchivo;
      std::string nombreSalida;
      std::string tipoCifrado;

      std::cout << "\n-- DESCIFRAR ARCHIVO --" << std::endl;
      std::cout << "Nombre del archivo cifrado con extension al final (.txt): ";
      std::getline(std::cin, nombreArchivo);

      // Construye ruta completa
      std::string rutaCompleta = CARPETA_CIFRADOS + nombreArchivo;

      // Pregunta tipo de cifrado usado
      std::cout << "\nQue tipo de cifrado se uso?" << std::endl;
      mostrarMenuCifrados();
      std::getline(std::cin, tipoCifrado);

      bool descifradoExitoso = false;

      // Descifra segun el tipo
      if (tipoCifrado == "1") {
        // XOR
        std::string clave;
        std::cout << "Clave de descifrado XOR: ";
        std::getline(std::cin, clave);

        if (protector.DescifrarXOR(rutaCompleta, clave)) {
          descifradoExitoso = true;
        }
      }
      else if (tipoCifrado == "2") {
        // Caesar
        std::string desplazamientoStr;
        std::cout << "Desplazamiento Caesar usado: ";
        std::getline(std::cin, desplazamientoStr);

        int desplazamiento = 0;
        for (char c : desplazamientoStr) {
          if (c >= '0' && c <= '9') {
            desplazamiento = desplazamiento * 10 + (c - '0');
          }
        }

        if (protector.DescifrarCaesar(rutaCompleta, desplazamiento)) {
          descifradoExitoso = true;
        }
      }
      else if (tipoCifrado == "3") {
        // ASCII-Binary
        if (protector.DescifrarASCIIBinary(rutaCompleta)) {
          descifradoExitoso = true;
        }
      }
      else if (tipoCifrado == "4") {
        // Vigenere
        std::string clave;
        std::cout << "Clave de descifrado Vigenere: ";
        std::getline(std::cin, clave);

        if (protector.DescifrarVigenere(rutaCompleta, clave)) {
          descifradoExitoso = true;
        }
      }
      else {
        std::cout << "Opcion de cifrado no valida" << std::endl;
      }

      // Si descifro bien, guarda el archivo
      if (descifradoExitoso) {
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