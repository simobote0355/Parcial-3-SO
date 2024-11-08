# Parcial 3 SO

Este es el proyecto para el tercer parcial de Sistemas Operativos. El equipo está conformado por:

- Laura Danniela Zárate
- Pablo Moreno
- Miguel Ángel Martínez
- Simón Botero

# Proyecto de Compresión y Cifrado LZ78

Este proyecto implementa un programa en C++ que utiliza el algoritmo de compresión LZ78 para reducir el tamaño de archivos y el cifrado César para agregar una capa básica de seguridad. Este README explica los componentes principales del proyecto, cómo compilarlo, y cómo utilizar el programa.

## Descripción

### Compresión LZ78
La compresión LZ78 es un algoritmo sin pérdida que crea un diccionario dinámico de patrones repetidos mientras lee un archivo. Este diccionario permite representar subsecuencias repetidas con índices en lugar de repetir el contenido, lo que reduce el tamaño del archivo.

### Cifrado César
El cifrado César es un método de encriptación por sustitución en el cual cada byte del archivo es desplazado una cantidad fija de posiciones en el alfabeto o conjunto de caracteres, aumentando la seguridad del archivo comprimido.

### Orden del Proceso
Para maximizar la eficiencia y seguridad:
1. **Primero se comprime el archivo** utilizando LZ78.
2. **Luego se encripta** usando el cifrado César con un desplazamiento configurable.

Esta secuencia permite que la compresión sea efectiva al mantener patrones repetidos en el archivo original y que el cifrado se aplique sobre un archivo más pequeño, optimizando tiempo y almacenamiento.

## Estructura del Código

- **LZ78Compressor.cpp**: Contiene la implementación del algoritmo de compresión LZ78 y el cifrado César. Proporciona métodos para comprimir, descomprimir, cifrar y descifrar archivos.
- **LZ78Compressor.h**: Archivo de cabecera que declara los métodos de compresión y cifrado.
- **main.cpp**: Programa principal que gestiona la interacción con el usuario para seleccionar archivos de entrada y aplicar compresión y cifrado.
- **Makefile**: Script de compilación que facilita la creación de los archivos ejecutables necesarios para el proyecto.

## Compilación

Para compilar el proyecto, utiliza el comando `make` en la terminal dentro del directorio del proyecto. Esto generará un archivo ejecutable llamado `lz78_program`.

```bash
make
```

El `Makefile` incluye las siguientes reglas:

- **all**: Compila el programa completo.
- **clean**: Elimina los archivos objeto (.o) y el ejecutable para limpiar el proyecto.

## Uso del Programa

El programa permite comprimir, encriptar, descomprimir y desencriptar archivos. Las funciones principales incluyen:

1. **Compresión y Encriptación**:
   - Comprime un archivo de texto y luego aplica un cifrado César con un desplazamiento especificado.
   
2. **Encriptación y Compresión**:
   - Permite encriptar primero un archivo y luego comprimirlo, aunque generalmente es menos eficiente.

3. **Descompresión y Desencriptación**:
   - Proporciona la opción de revertir ambos procesos en el orden correcto para restaurar el archivo original.

### Ejecución

Para ejecutar el programa una vez compilado:

```bash
./lz78_program
```

## Ejemplo de Uso

1. Al iniciar el programa, este pedirá el **archivo de entrada** y el **desplazamiento** para el cifrado.
2. Luego, puedes elegir entre las opciones de compresión y encriptación, o encriptación y compresión.
3. Los archivos resultantes se guardarán en la misma carpeta, con nombres de salida que puedes especificar en la ejecución.

## Requerimientos

- **Compilador C++ compatible con C++17**
- **GCC** o cualquier compilador compatible con `g++`
  
