Este programa implementa un arbol AVL para almacenar y gestionar terminos GO (Gene Ontology) leidos desde un archivo CSV
El arbol se mantiene balanceado en cada insercion o eliminacion

El programa permite:
-Cargar un arbol desde un archivo CSV (crea el arbol), con la ruta del archivo ejemplo: /home/ivonne/Documentos/algoritmo/laboratorio5/GeneOntology(GO).csv
-Insertar nuevos terminos GO manualmente 
-Buscar un termino por su score
-Eliminar un termino por score (manteniendo el balance)
-Generar una visualizacion del arbol en formato PNG usando graphviz
-Liberar la memoria usada antes de salir
El arbol se ordena y balancea por el Score

Flujo del programa:
-Se inicia el programa y esperar los argumentos para poder desplegar el menu (uso de argv y argc)
-Crear arbol: se entrega la ruta del archivo CSV y es procesado
-Generar grafo: visualizar el archivo CSV y comprobar que fue leido correctamente
-Insertar (se le piden los 3 tipos de informacion funcion, codigo y score)
-Eliminacion (se elimina por el score), si fue exitoso se mostrara un mensaje 
-Buscar nodo (se busca por el score) y si es encontrado se muestra la informnacion del nodo
-Liberar memoria 
por cada accion realizada se recomienda ir generando el grafo para corroborar que se estan realizando las acciones correctamente

Requisitos:
-Graphviz
-Archivo CSV
-Lenguaje c++

Laboratorio 5 - Algoritmos y Estructuras de Datos
Ivonne Cancino
