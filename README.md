Arbol binario de numeros enteros

Este programa permite: 
-Crear un arbol
-Insertar un numero nuevo (nuevo nodo) en el arbol (ya creado)
-Modificar un numero (ya ingresado), 
-Eliminar un numero 
-Generar la imagen para visualizar el arbol utilizando Graphviz.

Requisito para compilar y ejecutar correctamente este programa:
- Un compilador de C++
- Graphviz: (http://www.graphviz.org/)(para generar la imagen del árbol)

Instalación de Graphviz en Linux: sudo apt install graphviz (bash)

Funciones principales:
-numeroRepetido(Nodo*, int): Verifica si un valor ya existe en el árbol.
-Crea_arbol(Nodo*&, Nodo*): Permite al usuario crear el arbol de forma manual preguntando por cada nodo 
-insertar(Nodo*&, int): Agrega un nuevo nodo como hijo izquierdo o derecho de un nodo existente
-eliminar(Nodo*&, int): Elimina un nodo por su numero, no se reestructura el arbol
-modificar(Nodo*, int, int): Modifica el valor de un nodo, verificando que el nuevo valor no exista
-preorden(Nodo*): Muestra el recorrido del arbol: raiz -> izquierda -> derecha
-inorden(Nodo*): Muestra el recorrido del arbol: izquierda -> raiz -> derecha
-posorden(Nodo*): Muestra el recorrido del arbol: izquierda -> derecha -> raiz
-generarDot(Nodo*, string, string): Genera un archivo .dot para visualizar el arbol (en una imagen en .png) con Graphviz
-La función liberarArbol(Nodo*&) libera toda la memoria usada por el árbol al salir del programa.

Visualizacion del arbol: el programa genera una imagen del arbol binario (grafo.png) y la abrira automaticamente (con system()),esto funciona si se tiene instalado Graphviz correctamente.

Flujo del uso del codigo:
- -El programa inicia con un arbol vacio y se despliega un menu
- -Opcion 1: Si el arbol esta vacio se comienza con la creacion de los nodos (con los numero ingresado), se consulta por el numero del nodo raiz (el primer numero que se ingresa),
- y luego se consulta si ese nodo tiene un hijo izquierdo o derecho al que tambien le tiene que dar un valor el usuario si es que existen,
- ademas se evitan tener numeros repetidos en el arbol.
- -Opcion 2: El usuario debe ingresar el numero del nodo que desea eliminar, el progama busca el valor y si lo encuentra lo elimina sin reestructurar el arbol
- -Opcion 3: El usuario debe ingresar el numero del nodo que quiere modificar, se le pide el nuevo numero que tendra el nodo,
- se verifica que el numero no este en el arbol y se modifica el nodo
- -Opcion 4: Se muestran los valores del arbol en recorrido preorden
- -Opcion 5: Se muestran los valores del arbol en recorrido inoorden
- -Opcion 6: Se muestran los valores del arbol en recorrido posorden
- -Opcion 7: Se crea un archivo.dot con la estructura del arbol y se usa Graphviz para generar una imagen en formato .png y se abre automaticamente
- -Opcion 8: Permite que el usuario inserte un nuevo numero con el arbol ya creado, el usuario debe indicar en que nodo existente quiere agregar un nuevo nodo e
- indicando en que direccion (izquierda-derecha) y se realiza la insercion si es que ese lugar esta libre
- Opcion 0: Se libera toda la memoria utilizada en el programa y se termina la ejecucion
  
