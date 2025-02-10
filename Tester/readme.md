# **Programa de pruebas**

## **Descripción del programa:**

Este programa permite revisar los resultados obtenidos por el programa de simulación de temperatura del proyecto 2.

## **Manual de uso:**

Para poder utilizar el programa es necesario compilar los archivos de código que se encuentran en la carpeta src, para realizar esto se puede hacer uso del makefile que se encuentra en la carpeta principal del programa, al utilizarlo solo basta con escribir el comando `make release`, lo cual generara el archivo ejecutable del programa.

Una vez generado el ejecutable del programa se necesita ejecutar dicho archivo, el cual se ubica en la carpeta bin/ creada durante la compilación, esto se puede lograr de la siguiente forma:

```Shell
$ ./bin/Tester tests/Plate001.bin tests/Plate001-1.bin 10
```

En este programa es necesario el proporcionar 3 argumentos además de la dirección del programa en sí.

- El primer argumento es la dirección del primer archivo a analizar `tests/Plate001.bin`.
- El segundo argumento es la dirección del segundo archivo a analizar `tests/Plate001-1.bin`.
- El tercer argumento es la precisión con la cual se quiere realizar la prueba `10`.

Una vez proporcionados los argumentos el programa analizará los archivos y al final dirá si son iguales o por el contrario son diferentes.

## **Creditos:**

Realizado por Oscar Fernández  Jiménez - OSCAR.FERNANDEZJIMENEZ@ucr.ac.cr
Fecha de realización: 21-02-2023.
