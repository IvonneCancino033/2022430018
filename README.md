Actividad 2
este programa en c++ simula un puerto seco que guarda mercaderia en contenedores, utilizando estructuras tipo pila (LIFO) con restricciones de altura (n) 
y cantidad maxima de pilas (m). La carga y descarga de los contenedores se realiza manualmente y permite liberar un contenedor especifico moviendo
temporalmente los que esten encima.
Se permite ingresar contenedores que el usuario elija en cada una de las m pilas disponibles (el maximo de pilas es 16), cada pila tiene una altura 
maxima de n contenedores.
Los contenedores tienen un identificador numerico unico al ingresar y se puede eliminar un contenedor especificando su numero, si hay contenedores
encima del que se quiere eliminar, estos se mueven a otras pilas que tenga espacio disponible para eliminar un contenedor que este abajo, mostrando
los movimientos en pantalla y si no hay espacio lateral para mover, se cancela la operacion.

manera de uso:
1) el programa pedira al usuario que ingrese a que pila (se muestra como PILA1, PILA2, PILA3, etc) desea ingresar el contendor actual.
2) puedes seguir agregando contenedores hasta que la pila este llena.
3) puedes ingresar el numero del contenedor que deseas eliminar.
4) se busca el contenedor y se movera los que esten encima a otras pilas con espacio desponible.
5) se mostrara el estado final de todas las pilas. 
