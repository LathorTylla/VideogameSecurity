#include "Prerequisites.h"
#include "XOREncoder.h"
#include "FileProtector.h"
#include "CesarEncryption.h"
#include "AsciiBinary.h"
#include "Vigenere.h"
#include "DES.h"

void
mostrarMenu() {
  std::cout << "\n**********************************************" << std::endl;
  std::cout << "      SISTEMA DE CIFRADO v2.0 " << std::endl;
  std::cout << "**********************************************" << std::endl;
  std::cout << "1. Cifrar archivo                " << std::endl;
  std::cout << "2. Descifrar archivo             " << std::endl;
  std::cout << "3. Salir                         " << std::endl;
  std::cout << "Seleccione una opcion: ";

}

void
mostrarMenuCifrados() {
  std::cout << "      TIPOS DE CIFRADO      " << std::endl;
  std::cout << "1. XOR " << std::endl;
  std::cout << "2. Caesar " << std::endl;
  std::cout << "3. ASCII-Binary " << std::endl;
  std::cout << "4. Vigenere " << std::endl;
  std::cout << "5. DES " << std::endl;
  std::cout << "Seleccione tipo de cifrado: ";
}

void
mostrarInfoCifrado(const std::string& tipo) {
  if (tipo == "1") {
    std::cout << "CIFRADO XOR SELECCIONADO" << std::endl;
    std::cout << "******************************************" << std::endl;
    std::cout << "Requisitos de la clave:" << std::endl;
    std::cout << "Puede contener letras, numeros y simbolos" << std::endl;
    std::cout << "Se recomienda minimo 8 caracteres" << std::endl;
    std::cout << "Ejemplo: MyPass@2024!" << std::endl;
  }
  else if (tipo == "2") {
    std::cout << "CIFRADO CAESAR SELECCIONADO" << std::endl;
    std::cout << "******************************************" << std::endl;
    std::cout << "Requisitos del desplazamiento:" << std::endl;
    std::cout << "Debe ser un numero entero" << std::endl;
    std::cout << "Rango recomendado: 1-25" << std::endl;
    std::cout << "Ejemplo: 13" << std::endl;
  }
  else if (tipo == "3") {
    std::cout << "CIFRADO ASCII-BINARY SELECCIONADO" << std::endl;
    std::cout << "******************************************" << std::endl;
    std::cout << "Informacion:" << std::endl;
    std::cout << "No requiere clave" << std::endl;
    std::cout << "Convierte texto a codigo binario" << std::endl;
    std::cout << "El archivo resultante sera mas grande" << std::endl;
  }
  else if (tipo == "4") {
    std::cout << "CIFRADO VIGENERE SELECCIONADO" << std::endl;
    std::cout << "******************************************" << std::endl;
    std::cout << "Requisitos de la clave:" << std::endl;
    std::cout << "Solo debe contener LETRAS" << std::endl;
    std::cout << "Sin espacios ni numeros" << std::endl;
    std::cout << "Ejemplo: SECRETKEY" << std::endl;
  }
  else if (tipo == "5") {
    std::cout << "CIFRADO DES SELECCIONADO" << std::endl;
    std::cout << "******************************************" << std::endl;
    std::cout << "Requisitos de la clave:" << std::endl;
    std::cout << "Debe tener EXACTAMENTE 8 caracteres" << std::endl;
    std::cout << "Puede contener letras, numeros y simbolos" << std::endl;
    std::cout << "Ejemplo: Pass1234" << std::endl;
  }
  std::cout << "******************************************\n" << std::endl;
}

void
mostrarAdvertencia() {
  std::cout << "\n******************************************" << std::endl;
  std::cout << "*             IMPORTANTE               *" << std::endl;
  std::cout << "******************************************" << std::endl;
  std::cout << "* Guarde su clave en un lugar seguro   *" << std::endl;
  std::cout << "* Sin la clave NO podra descifrar      *" << std::endl;
  std::cout << "* La clave es sensible a mayusculas    *" << std::endl;
  std::cout << "******************************************" << std::endl;
}

int
main() {
  FileProtector protector;
  std::string opcion;

  //Carpeta de origen y destino
  const std::string CARPETA_CRUDOS = "archivos/Datos crudos/";
  const std::string CARPETA_CIFRADOS = "archivos/Datos cif/";

  std::cout << "\n**********************************************" << std::endl;
  std::cout << "*     SISTEMA DE CIFRADO DE ARCHIVOS         *" << std::endl;
  std::cout << "**********************************************" << std::endl;
  std::cout << "\nCarpetas configuradas:" << std::endl;
  std::cout << "Origen: " << CARPETA_CRUDOS << std::endl;
  std::cout << "Destino: " << CARPETA_CIFRADOS << std::endl;


  while (true) {
    mostrarMenu();
    std::getline(std::cin, opcion);

    if (opcion == "1") {
      // Cifrar archivo
      std::string nombreArchivo;
      std::string nombreSalida;
      std::string tipoCifrado;

      std::cout << "\n******** CIFRAR ARCHIVO ********" << std::endl;
      std::cout << "\nIngrese el nombre del archivo (.txt): ";
      std::getline(std::cin, nombreArchivo);

      std::string rutaCompleta = CARPETA_CRUDOS + nombreArchivo;

      // Carga el archivo
      if (protector.CargarArchivo(rutaCompleta)) {
        // Muestra menu de cifrados
        mostrarMenuCifrados();
        std::getline(std::cin, tipoCifrado);

        // Muestra informacion del cifrado seleccionado
        mostrarInfoCifrado(tipoCifrado);

        std::cout << "Nombre del archivo cifrado (sin extension): ";
        std::getline(std::cin, nombreSalida);

        // Ruta de salida
        std::string rutaSalida = CARPETA_CIFRADOS + nombreSalida + ".txt";

        // Cifra segun el tipo seleccionado
        if (tipoCifrado == "1") {
          // XOR
          std::string clave;
          mostrarAdvertencia();
          std::cout << "\nIngrese la clave de cifrado: ";
          std::getline(std::cin, clave);

          if (protector.CifrarXOR(rutaSalida, clave)) {
            std::cout << "\nArchivo cifrado exitosamente!" << std::endl;
            std::cout << "Guardado como: " << rutaSalida << std::endl;
            std::cout << "Clave utilizada: " << std::string(clave.length(), '*') << std::endl;
          }
        }
        else if (tipoCifrado == "2") {
          // Caesar
          std::string desplazamientoStr;
          std::cout << "\nIngrese el desplazamiento (1-25): ";
          std::getline(std::cin, desplazamientoStr);

          int desplazamiento = 0;
          for (char c : desplazamientoStr) {
            if (c >= '0' && c <= '9') {
              desplazamiento = desplazamiento * 10 + (c - '0');
            }
          }

          if (protector.CifrarCaesar(rutaSalida, desplazamiento)) {
            std::cout << "\nArchivo cifrado exitosamente!" << std::endl;
            std::cout << "Guardado como: " << rutaSalida << std::endl;
            std::cout << " Desplazamiento: " << desplazamiento << std::endl;
          }
        }
        else if (tipoCifrado == "3") {
          // ASCII-Binary
          if (protector.CifrarASCIIBinary(rutaSalida)) {
            std::cout << "\nArchivo cifrado exitosamente!" << std::endl;
            std::cout << "Guardado como: " << rutaSalida << std::endl;
            std::cout << "Tipo: Binario" << std::endl;
          }
        }
        else if (tipoCifrado == "4") {
          // Vigenere
          std::string clave;
          mostrarAdvertencia();
          std::cout << "\nIngrese la clave (solo letras): ";
          std::getline(std::cin, clave);

          if (protector.CifrarVigenere(rutaSalida, clave)) {
            std::cout << "\nArchivo cifrado exitosamente!" << std::endl;
            std::cout << "Guardado como: " << rutaSalida << std::endl;
            std::cout << "Clave utilizada: " << std::string(clave.length(), '*') << std::endl;
          }
        }
        else if (tipoCifrado == "5") {
          // DES
          std::string clave;
          mostrarAdvertencia();
          std::cout << "\nIngrese la clave (EXACTAMENTE 8 caracteres): ";
          std::getline(std::cin, clave);

          if (protector.CifrarDES(rutaSalida, clave)) {
            std::cout << "\nArchivo cifrado exitosamente!" << std::endl;
            std::cout << "Guardado como: " << rutaSalida << std::endl;
          }
        }
        else {
          std::cout << "\nOpcion de cifrado no valida" << std::endl;
        }
      }
    }
    else if (opcion == "2") {
      // Descifrar archivo
      std::string nombreArchivo;
      std::string nombreSalida;
      std::string tipoCifrado;

      std::cout << "\nDESCIFRAR ARCHIVO " << std::endl;
      std::cout << "\nIngrese el nombre del archivo cifrado (.txt): ";
      std::getline(std::cin, nombreArchivo);

      std::string rutaCompleta = CARPETA_CIFRADOS + nombreArchivo;

      std::cout << "\n¿Que tipo de cifrado se uso?" << std::endl;
      mostrarMenuCifrados();
      std::getline(std::cin, tipoCifrado);

      bool descifradoExitoso = false;

      // Descifra segun el tipo
      if (tipoCifrado == "1") {
        // XOR
        std::string clave;
        std::cout << "\nDESCIFRADO XOR" << std::endl;
        std::cout << "Ingrese la clave de descifrado: ";
        std::getline(std::cin, clave);

        if (protector.DescifrarXOR(rutaCompleta, clave)) {
          descifradoExitoso = true;
        }
      }
      else if (tipoCifrado == "2") {
        // Caesar
        std::string desplazamientoStr;
        std::cout << "\nDESCIFRADO CAESAR" << std::endl;
        std::cout << "Ingrese el desplazamiento usado: ";
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
        std::cout << "\nDESCIFRADO ASCII-BINARY" << std::endl;
        if (protector.DescifrarASCIIBinary(rutaCompleta)) {
          descifradoExitoso = true;
        }
      }
      else if (tipoCifrado == "4") {
        // Vigenere
        std::string clave;
        std::cout << "\nDESCIFRADO VIGENERE" << std::endl;
        std::cout << "Ingrese la clave de descifrado: ";
        std::getline(std::cin, clave);

        if (protector.DescifrarVigenere(rutaCompleta, clave)) {
          descifradoExitoso = true;
        }
      }
      else if (tipoCifrado == "5") {
        // DES
        std::string clave;
        std::cout << "\nDESCIFRADO DES" << std::endl;
        std::cout << "Ingrese la clave de 8 caracteres: ";
        std::getline(std::cin, clave);

        if (protector.DescifrarDES(rutaCompleta, clave)) {
          descifradoExitoso = true;
        }
      }
      else {
        std::cout << "\nOpcion de cifrado no valida" << std::endl;
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