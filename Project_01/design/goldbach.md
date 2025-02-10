# *Tarea #1*

## *Descripción del problema:*

*¿Que es la conjetura de Goldbach?*

En 1742 Christian Goldbach de Prusia le escribió una carta al matemático suizo Leonhard Euler con una conjetura:

Todo número entero mayor que 5:

  1. Si es par se puede escribir como suma de dos números primos (conjetura fuerte). Por ejemplo: 6=3+3, 8=3+5, 14=3+11=7+7.

  2. Si es impar se puede escribir como suma de tres números primos (conjetura débil). Por ejemplo.: 7=2+2+3, 9=2+2+5, 9=3+3+3.

Euler no pudo demostrar la conjetura, ni tampoco cientos de matemáticos convirtiéndolo en el problema abierto más intrigante en la historia de la teoría de números. Algunas novelas y películas hacen alusión a la conjetura, y entre los años 2000 y 2002 se ofreció un premio de un millón de dólares a quien lograse demostrarla, premio que no fue reclamado. En el 2013, tras 271 años de su aparición, el matemático peruano Harald Helfgott propuso una demostración para la conjetura débil que está actualmente sometida a revisión de pares, y en caso de validarse convertiría la conjetura débil en teorema.

El presente código es un programa procedimental en C, que a partir de una lista de números de tipo entero recibida por la entrada estándar, realizara una serie de cálculos para determinar las posibles sumas de Golbach que como resultado dan cada uno de los números de la lista.

Este programa es de carácter serial, y tiene como objetivo imprimir los resultados en la salida estándar, junto a la cantidad de números ingresados y la suma total de las sumas encontradas por el programa.

Una vez impresas las sumas y total de números, el programa se dedicará a pedir los números, para posteriormente imprimir en cada línea el número, junto a la cantidad de suma de dicho número. En caso de que el número sea negativo se imprimirá además de la información anterior, los números que forman dichas sumas, estos ordenados de manera ascendente.

## *Manual de uso:*

Para poder utilizar el programa es necesario compilar los archivos de código que se encuentran en la carpeta src, para realizar esto se puede hacer uso del makefile que se encuentra en la carpeta principal del programa, al utilizarlo solo basta con escribir el comando "make release", lo cual generara el ejecutable del programa.

Una vez generado el ejecutable del programa solo se necesita ejecutar dicho archivo, el cual se ubica en la carpeta bin/ creada durante la compilación.

El programa puede ser corrido de dos maneras, la primera es de manera interactiva al ejecutar el programa de manera manual, y la segunda es con un lote de datos guardados en un archivo.

### 1.  *Interacción directa*

    Al ejecutar el archivo pedirá directamente los números hasta encontrar un final de archivo, cada número irá separado por un salto de línea (Enter), en que no desee ingresar más archivos se deberá presionar CTRL + D para insertar el final del archivo.

    Ejemplo:

    Al ingresar los siguientes números:

        100
        -21

    Se obtuvo la siguiente salida:

        Total: 2 numbers 11 sums

        100: 6 sums
        -21: 5 sums: 2 + 2 + 17, 3 + 5 + 13, 3 + 7 + 11, 5 + 5 + 11, 7 + 7 + 7

### 2. *Lote de datos*

    Esto puede ser llevado a cabo de dos maneras, la primera es mediante el de la función del Makefile proveído para realizar, o mediante el siguiente comando "./bin/nombre_ejecutable < ubicacion/nombre_datos.txt ".

    El programa también puede ser corrido utilizando datos de prueba, para ello se deben colocar los archivos en la carpeta tests, para posteriormente utilizar el comando "make test" y obtener una comparación de datos entre los esperados y los obtenidos.

    En el primer caso se obtendría un resultado como la salida de la forma anterior, pero en segundo seria de la siguiente forma.

    Ejemplo:

        # make test
        icdiff --no-headers tests/output002.txt <(bin/goldbach_serial < tests/input002.txt) ||:
        Total 21 numbers 16 sums                                                                 Total: 21 numbers 14 sums                                                               

        0:NA                                    0:NA
        1:NA                                    1:NA
        2:NA                                    2:NA
        3:NA                                    3:NA
        4:NA                                    4:NA
        5:NA                                    5:NA
        6: 1 sums                               6: 1 sums
        ...
        -6: 1 sums: 3 + 3                       -6: 1 sums: 3 + 3
        -7: 1 sums: 2 + 2 + 3                   -7: 1 sums: 2 + 2 + 3
        -8: 1 sums: 3 + 5                       -8: 1 sums: 3 + 5
        -9: 2 sums: 2 + 2 + 5, 3 + 3 + 3        -9: 2 sums: 2 + 2 + 5, 3 + 3 + 3 

## *Creditos:*

* Oscar Mario Fernandez Jimenez (oscar.fernandezjimenez@ucr.ac.cr)

* Fernando Jose Arce Castillo (fernando.arcecastillo@ucr.ac.cr)

* Alexander Sanchez Zamora (alexander.sanchezzamora@ucr.ac.cr)

Fecha de realización: 21-01-2023.
