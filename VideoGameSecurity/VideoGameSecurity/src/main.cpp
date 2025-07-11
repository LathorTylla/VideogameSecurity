#include "FileProtector.h"

int 
main() {
  FileProtector protector;
  std::string nombreArchivo;

  std::cout << "\n*** Menu ***\n";
  std::cout << "Nombre del archivo .txt (en bin/Datos crudos/): ";
  std::getline(std::cin, nombreArchivo);

  const std::string ruta = "bin/Datos crudos/" + nombreArchivo;
  if (protector.CargarArchivo(ruta)) {
    std::cout << "Archivo cargado correctamente: " << ruta << std::endl;
  }

  return 0;
}