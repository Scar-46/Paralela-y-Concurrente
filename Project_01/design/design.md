# Diagramas del programa

En esta sección se pueden ver los distintos diagramas que explican el
funcionamiento del programa, estos se dividen en las siguientes secciones:

## **Diagrama de servidor**

En este primer diagrama se pueden apreciar las distintas relaciones que poseen
los componentes que forman el servidor por completo, todo esto junto a una serie
de datos que avanzan por los distintos componentes, esto con el objetivo de
mostrar de manera más clara como se ven afectados los datos al avanzar por las
estructuras que componen el programa.

![Diagram](./Server_Diagram.svg)

Podemos observar el circuito recorrido que debe realizarse para poder utilizar
el servidor: primero los clientes solicitan una conexión al servidor, el cual
acepta estas conexiones y las encola (en forma de sockets) para ser atendidas.
Aquí los HttpConnectionHandlers se encargan de desencolar estos Sockets para
encontrar la WebApp que atenderá sus solicitudes y procede a encolarlas en su
respectiva aplicación. Acto seguido, la WebApp solicitada se encargará de
introducir en otra cola cada una de las operaciones enviadas por el cliente
individualmente, para que las calculadoras (que serán tantas como procesadores
existan en el servidor) realicen los cálculos necesarios según sea el caso por
medio de los algoritmos implementados. Hecho esto, se encolan los datos
calculados en la cola que recibe el empaquetador con el fin de que este se
cerciore y compacte todas las solicitudes de un cliente en una sola respuesta,
la cual es recibida por un despachador que se encarga de enviarla de vuelta al
usuario.

En el siguiente diagrama podemos ver más a detalle las funciones utilizadas
en cada clase para realizar este recorrido:

![Diagram](./Server_UML_Diagram.svg)

> * Nota: Los espacios azules indican funciones propias de la clase, los
>       espacios morados indican herencia y los rojos indican otro diagrama.

### WebApp

La aplicación web consiste en el siguiente conjunto de clases:

* **GoldbachWebApp:** Se encarga de recibir las solicitudes HTTP que emite el
cliente, extrae los números del cuerpo de la solicitud y los pasa a
`GCalculator`.

* **GCalculator:** Desencola las solicitudes enviadas por el usuario y llama a
`GoldbachSolver` para que los procese. Seguidamente, encola las respuestas en
una cola compartida con el `Packer`.

* **GoldbachSolver:** Configura los datos para ser analizados por
`GoldbachSerial`

* **Goldbach_serial:** Se encarga de encontrar la suma de Goldbach de
números representados en aritmética de precisión fija. Esta clase recibe
un de número y retorna colecciones de números separados en sus sumas
de Goldbach.

Una vez analizados los datos se utilizan otras dos clases encargadas de la
manipulación de estos datos y su envío al cliente, respectivamente:

* **Packer:** Se asegura de que todas las operaciones enviadas por el cliente se
encuentren en un sólo vector, el cual transmite a `ResponseProducer` mediante
una cola.

* **ResponseProducer:** Ordena los datos recibidos de `Packer` y los envía al
cliente.

Para la implementación de este modelo ha sido necesaria la utilización de
diversas estructuras de datos para la manipulación de datos (como mapas y
vectores), así como la transmisión de los mismo a través de la cadena de
producción (como la cola). A continuación se puede apreciar un diagrama UML
sobre las relaciones existentes entre estas clases.

![WebApp](./Model_UML.svg)

> * Notas:
>     Los espacios azules indican funciones propias de la clase.

## **Diagrama UML**

Del mismo modo puede observarse el diagrama UML completo de todas las partes
previas del servidor unidas:

![Diagram](./Complete_UML.svg)

> * Notas:
>     Los espacios azules indican funciones propias de la clase,
>     mientras que los espacios morados indican herencia.

## **Diagrama de ejecución**

Este diagrama se presenta como funciona el programa al ingresar 3 datos que
desencadenan diferentes comportamientos en el código.
  
    1. El primer dato es positivo y par lo cual provocara que el programa deba
    guardar en memoria la cantidad de sumas de dos digitos primos unicamente.

    2. El segundo dato es impar y negativo, por lo cual será necesario guardar
    tres números por suma, así como la cantidad de sumas.

    3. El tercer dato es positivo y par lo cual provocara que el programa deba
    guardar en memoria la cantidad de sumas de dos digitos primos unicamente.

En la siguiente imagen se puede apreciar en comportamiento del programa al
recibir números con dichas características.

![Execution](./Execution_Diagram.svg)

> * Notas:
>     Las flechas verdes indican entradas.
>     Las flechas rojas son salidas.
>     Los espacios azules indican funciones propias de la clase
>     y los espacios morados indican herencia de dicho componente.
