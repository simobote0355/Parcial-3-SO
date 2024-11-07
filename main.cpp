// main.cpp
#include <iostream>
#include <string>
#include "LZ78Compressor.h"

void showMenu() {
    std::cout << "\nSeleccione una opción:\n";
    std::cout << "1 - Comprimir archivo\n";
    std::cout << "2 - Descomprimir archivo\n";
    std::cout << "3 - Encriptar archivo\n";
    std::cout << "4 - Desencriptar archivo\n";
    std::cout << "5 - Comprimir y luego encriptar archivo\n";
    std::cout << "6 - Encriptar y luego comprimir archivo\n";
    std::cout << "0 - Salir\n";
    std::cout << "Seleccione una opción: ";
}

int main() {
    LZ78Compressor compressor;
    int option;
    
    while (true) {
        showMenu();
        std::cin >> option;

        if (option == 0) {
            std::cout << "Saliendo del programa...\n";
            break;
        }

        std::string inputFilePath, outputFilePath, compressedFilePath, encryptedFilePath;
        int shift = 0;

        switch (option) {
            case 1:  // Comprimir archivo
                std::cout << "Ingrese el archivo de entrada a comprimir: ";
                std::cin >> inputFilePath;
                std::cout << "Ingrese el archivo de salida para guardar el comprimido: ";
                std::cin >> outputFilePath;
                
                if (compressor.compress(inputFilePath, outputFilePath)) {
                    std::cout << "Archivo comprimido correctamente en: " << outputFilePath << "\n";
                } else {
                    std::cerr << "Error en la compresión.\n";
                }
                break;

            case 2:  // Descomprimir archivo
                std::cout << "Ingrese el archivo comprimido a descomprimir: ";
                std::cin >> inputFilePath;
                std::cout << "Ingrese el archivo de salida para guardar el descomprimido: ";
                std::cin >> outputFilePath;
                
                if (compressor.decompress(inputFilePath, outputFilePath)) {
                    std::cout << "Archivo descomprimido correctamente en: " << outputFilePath << "\n";
                } else {
                    std::cerr << "Error en la descompresión.\n";
                }
                break;

            case 3:  // Encriptar archivo
                std::cout << "Ingrese el archivo de entrada a encriptar: ";
                std::cin >> inputFilePath;
                std::cout << "Ingrese el archivo de salida para guardar el encriptado: ";
                std::cin >> outputFilePath;
                std::cout << "Ingrese el desplazamiento para la encriptación: ";
                std::cin >> shift;
                
                if (compressor.encryptFile(inputFilePath, outputFilePath, shift)) {
                    std::cout << "Archivo encriptado correctamente en: " << outputFilePath << "\n";
                } else {
                    std::cerr << "Error en la encriptación.\n";
                }
                break;

            case 4:  // Desencriptar archivo
                std::cout << "Ingrese el archivo encriptado a desencriptar: ";
                std::cin >> inputFilePath;
                std::cout << "Ingrese el archivo de salida para guardar el desencriptado: ";
                std::cin >> outputFilePath;
                std::cout << "Ingrese el desplazamiento utilizado en la encriptación: ";
                std::cin >> shift;
                
                if (compressor.decryptFile(inputFilePath, outputFilePath, shift)) {
                    std::cout << "Archivo desencriptado correctamente en: " << outputFilePath << "\n";
                } else {
                    std::cerr << "Error en la desencriptación.\n";
                }
                break;

            case 5:  // Comprimir y luego encriptar
                std::cout << "Ingrese el archivo de entrada a comprimir y encriptar: ";
                std::cin >> inputFilePath;
                std::cout << "Ingrese el archivo de salida para el comprimido: ";
                std::cin >> compressedFilePath;
                std::cout << "Ingrese el archivo de salida para el encriptado: ";
                std::cin >> encryptedFilePath;
                std::cout << "Ingrese el desplazamiento para la encriptación: ";
                std::cin >> shift;
                
                if (compressor.compressAndEncrypt(inputFilePath, compressedFilePath, encryptedFilePath, shift)) {
                    std::cout << "Archivo comprimido en: " << compressedFilePath << " y encriptado en: " << encryptedFilePath << "\n";
                } else {
                    std::cerr << "Error en la compresión y encriptación.\n";
                }
                break;

            case 6:  // Encriptar y luego comprimir
                std::cout << "Ingrese el archivo de entrada a encriptar y comprimir: ";
                std::cin >> inputFilePath;
                std::cout << "Ingrese el archivo de salida para el encriptado: ";
                std::cin >> encryptedFilePath;
                std::cout << "Ingrese el archivo de salida para el comprimido: ";
                std::cin >> compressedFilePath;
                std::cout << "Ingrese el desplazamiento para la encriptación: ";
                std::cin >> shift;
                
                if (compressor.encryptAndCompress(inputFilePath, encryptedFilePath, compressedFilePath, shift)) {
                    std::cout << "Archivo encriptado en: " << encryptedFilePath << " y comprimido en: " << compressedFilePath << "\n";
                } else {
                    std::cerr << "Error en la encriptación y compresión.\n";
                }
                break;

            default:
                std::cout << "Opción no válida.\n";
                break;
        }
    }
    return 0;
}
