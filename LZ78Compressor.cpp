// LZ78Compressor.cpp
#include "LZ78Compressor.h"
#include <algorithm>
#include <iostream>
#include <chrono> // Para medir el tiempo de ejecución
#include <fstream> // Para manejo de archivos
#include <unordered_map>
#include <vector>
#include <string>

bool LZ78Compressor::compressAndEncrypt(const std::string& inputFilePath, const std::string& compressedFilePath, const std::string& encryptedFilePath, int shift) {
    // Medir tiempo de ejecución de todo el proceso
    auto start = std::chrono::high_resolution_clock::now();

    // Paso 1: Comprimir el archivo
    if (!compress(inputFilePath, compressedFilePath)) {
        std::cerr << "Error: No se pudo comprimir el archivo.\n";
        return false;
    }

    // Paso 2: Encriptar el archivo comprimido
    if (!encryptFile(compressedFilePath, encryptedFilePath, shift)) {
        std::cerr << "Error: No se pudo encriptar el archivo.\n";
        return false;
    }

    // Medir tiempo de ejecución al final
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tiempo total (Comprimir + Encriptar): " << duration.count() << " segundos.\n";

    return true;
}

bool LZ78Compressor::encryptAndCompress(const std::string& inputFilePath, const std::string& encryptedFilePath, const std::string& compressedFilePath, int shift) {
    // Medir tiempo de ejecución de todo el proceso
    auto start = std::chrono::high_resolution_clock::now();

    // Paso 1: Encriptar el archivo
    if (!encryptFile(inputFilePath, encryptedFilePath, shift)) {
        std::cerr << "Error: No se pudo encriptar el archivo.\n";
        return false;
    }

    // Paso 2: Comprimir el archivo encriptado
    if (!compress(encryptedFilePath, compressedFilePath)) {
        std::cerr << "Error: No se pudo comprimir el archivo.\n";
        return false;
    }

    // Medir tiempo de ejecución al final
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tiempo total (Encriptar + Comprimir): " << duration.count() << " segundos.\n";

    return true;
}

// Métodos de compresión, descompresión, encriptación y desencriptación (sin cambios, como en el código original)

bool LZ78Compressor::compress(const std::string& inputFilePath, const std::string& outputFilePath) {
    std::ifstream inputFile(inputFilePath, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo de entrada.\n";
        return false;
    }

    std::ofstream outputFile(outputFilePath, std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo de salida.\n";
        return false;
    }

    std::unordered_map<std::string, int> dictionary;
    std::string buffer;
    int dictIndex = 1;
    char symbol;
    while (inputFile.get(symbol)) {
        std::string combined = buffer + symbol;
        if (dictionary.count(combined) == 0) {
            int index = buffer.empty() ? 0 : dictionary[buffer];
            outputFile.write(reinterpret_cast<const char*>(&index), sizeof(index));
            outputFile.put(symbol);
            dictionary[combined] = dictIndex++;
            buffer.clear();
        } else {
            buffer = combined;
        }
    }

    if (!buffer.empty()) {
        int index = dictionary[buffer];
        outputFile.write(reinterpret_cast<const char*>(&index), sizeof(index));
        outputFile.put(0);
    }

    inputFile.close();
    outputFile.close();
    return true;
}

// Método decompress
// Este método toma un archivo comprimido y lo descomprime usando el algoritmo LZ78
// Recibe: inputFilePath (ruta del archivo comprimido), outputFilePath (ruta del archivo descomprimido)
bool LZ78Compressor::decompress(const std::string& inputFilePath, const std::string& outputFilePath) {
    std::ifstream inputFile(inputFilePath, std::ios::binary); // Abre el archivo comprimido en modo binario
    if (!inputFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo comprimido.\n";
        return false;
    }

    std::ofstream outputFile(outputFilePath, std::ios::binary); // Abre el archivo de salida en modo binario
    if (!outputFile.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo de salida.\n";
        return false;
    }

    std::vector<std::string> dictionary = {""}; // Inicializa el diccionario con una entrada vacía para el índice 0
    int index; // Índice leído del archivo comprimido
    char symbol; // Símbolo leído del archivo comprimido

    // Descomprime cada par (índice, símbolo) del archivo comprimido
    while (inputFile.read(reinterpret_cast<char*>(&index), sizeof(index)) && inputFile.get(symbol)) {
        std::string entry = dictionary[index] + symbol; // Genera la subcadena original
        outputFile << entry; // Escribe la subcadena en el archivo de salida

        dictionary.push_back(entry); // Agrega la subcadena al diccionario para futuras referencias
    }

    inputFile.close(); // Cierra el archivo comprimido
    outputFile.close(); // Cierra el archivo de salida
    return true; // Indica éxito en la descompresión
}

bool LZ78Compressor::decryptFile(const std::string& encryptedFilePath, const std::string& decryptedFilePath, int shift) {
    std::ifstream inputFile(encryptedFilePath, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo encriptado.\n";
        return false;
    }

    std::ofstream decryptedFile(decryptedFilePath, std::ios::binary);
    if (!decryptedFile.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo desencriptado.\n";
        return false;
    }

    char byte;
    while (inputFile.get(byte)) {
        char decryptedByte = byte - shift;
        decryptedFile.put(decryptedByte);
    }

    inputFile.close();
    decryptedFile.close();
    return true;
}

bool LZ78Compressor::encryptFile(const std::string& compressedFilePath, const std::string& encryptedFilePath, int shift) {
    std::ifstream inputFile(compressedFilePath, std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo comprimido.\n";
        return false;
    }

    std::ofstream encryptedFile(encryptedFilePath, std::ios::binary);
    if (!encryptedFile.is_open()) {
        std::cerr << "Error: No se pudo crear el archivo encriptado.\n";
        return false;
    }

    char byte;
    while (inputFile.get(byte)) {
        char encryptedByte = byte + shift;
        encryptedFile.put(encryptedByte);
    }

    inputFile.close();
    encryptedFile.close();
    return true;
}

void LZ78Compressor::displayWordCodeTable(const std::unordered_map<std::string, int>& dictionary) const {
    std::vector<std::pair<int, std::string>> sortedEntries;
    for (const auto& entry : dictionary) {
        sortedEntries.emplace_back(entry.second, entry.first);
    }

    std::sort(sortedEntries.begin(), sortedEntries.end());
    std::cout << "Tabla de Códigos de Palabras (Word Code Table) en formato de tupla:\n";
    for (const auto& entry : sortedEntries) {
        std::cout << "(" << entry.first << ", [" << entry.second << "])\n";
    }
}
