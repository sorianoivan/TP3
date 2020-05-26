Nombre: Ivan Soriano

Padrón: 102342

URL: 



# <u>Trabajo Práctico 3</u>

 

### <u>Server</u>

Luego de que el *bind_skt* empiece a escuchar conexiones el servidor lanzara un hilo que sera el encargado de esperar por la entrada estándar el carácter 'q' que indica que el servidor no debe escuchar mas conexiones y finalizar el programa. Luego de lanzar dicho hilo, comienza a aceptar clientes. Mientras el *bind_skt* este abierto, este se quedara esperando una conexión. Cuando se establezca una conexión con *peer_skt* se creara una nueva instancia de la clase Messenger que recibirá (por movimiento) el socket creado, el numero secreto que el cliente deberá adivinar y una referencia a la cantidad de ganadores del juego. Este "Mensajero" se agregara al vector de clientes y luego se lanzara un hilo comenzando su ejecución. Como se puede observar en el programa, para lanzar el hilo se hace:

```
clients[total_clients - clients_removed]->start();
```

Esto es ya que después de aceptar a un cliente debo recorrer el vector y eliminar a aquellos que ya hayan terminado. Esto causa que los indices de los clientes dentro del vector cambien, por lo que debe ser compensado. A continuación se da un ejemplo para clarificar:

Acepto un cliente y lo ubico en clients[0], pero antes de que otro cliente se conecte, este termina su ejecución. Luego, acepto un segundo cliente y lo ubico en clients[1], pero después al recorrer el vector se eliminara al primer cliente y el segundo pasara a ubicarse en clients[0]. Luego, cuando acepte otro cliente, este debe ser ubicado en clients[1], no en clients[2] como pasaría si solo usara *total_clients* como indice.

Este ciclo se repite hasta que el servidor reciba por entrada estándar el carácter 'q', entonces se cerrara el *bind_skt*, se esperara a que todos los clientes terminen su ejecución, se liberaran sus recursos y se mostraran los resultados.

Diagrama de clases del Server:

![ServerClassDiagram](/img/ServerClassDiagram.png)

Diagrama de secuencia de aceptación de clientes:

![ServerSequenceDiagram](/img/ServerSequenceDiagram.png)

### <u>Messenger</u>

El Messenger es el encargado de comunicarse con el cliente. Primero recibe un comando del cliente que puede ser 'h' (Ayuda), 's' (Rendirse) o 'n' (Numero). Si recibe 'h' le enviara al cliente un mensaje con los comandos validos. Si recibe 's', le enviara un mensaje que diga "Perdiste" y terminara la ejecución. Si recibe 'n', luego espera el numero de 2 bytes q enviara el cliente. Habiendo recibido el numero, se lo manda a la clase Verifier que le dirá si cumple con los requisitos de ser de 3 cifras y que ninguna este repetida. Si esto no se cumple se le envía un mensaje al cliente diciendo que el numero no cumple los requisitos. Si el numero es valido, se lo compara con el numero secreto. Si el numero es correcto, se le envía el mensaje "Ganaste" al cliente, se incrementa la cantidad de ganadores (a pesar de que puede haber varios threads que quieran cambiar esta variable no habrá race conditions ya que la variable es atómica), y se termina la ejecución. Si el numero es incorrecto se le envía la cantidad de cifras que están bien, regular o mal. Si el cliente no adivino el numero en 10 intentos se le envía el mensaje "Perdiste" y se termina la ejecución.

Diagrama de clases de Messenger:

![MessengerClassDiagram](/img/MessengerClassDiagram.png)

Diagrama de secuencia de Messenger:

![MessengerSequenceDiagram](/img/MessengerSequenceDiagram.png)



### <u>Cliente</u>

El cliente comienza recibiendo un comando por la entrada estándar. Si el comando es "AYUDA" o "RENDIRSE" le envía el carácter correspondiente al Messenger con el que se comunica y espera la respuesta que luego imprimirá por la salida estándar. Si el comando no es ninguna de esas dos cosas, el comando debería ser un numero. Para verificar esto, la clase Verifier le aplica la función *stoi* que lanzara una excepción si es algo distinto a un numero o si es un numero que no entra en una variable de tipo int. Como el enunciado me pide que el numero debe poder ser representado con 2 bytes, debo verificar también que el numero sea menor a 65535. Si el numero cumple con estas condiciones es enviado al Messenger que me enviara una respuesta. Con respecto a la respuesta debo aclarar que para recibirla e imprimirla se usa un char* en lugar de un std::vector<char> debido a que el método recv() de sockets utiliza void* y no soporta std::vector.

![ClientClassDiagram](/img/ClientClassDiagram.png)



Diagrama de secuencia de Cliente:

![ClientSequenceDiagram](/img/ClientSequenceDiagram.png)