#  Laboratorio 10 — Conteo Automatizado de Residuos en Proteínas (Archivos PDB)

## 👩‍💻 Autor

**Nombre:** Ivonne Cancino  
**Asignatura:** Algoritmos y Estructura de Datos  
**Carrera:** Ingeniería Civil en Bioinformática  
**Universidad:** Universidad de Talca - Facultad de Ingeniería  

---

##  Descripción

Este laboratorio automatiza el conteo de residuos espedìficos de aminoàcidos cargados (LYS,ARG,HIS,GLU,ASP) en tres archivos PDB correspondiente a las proteìnas **HEM_A, GFP_A, ACE2_A** .

El script residues_count.sh:

- Filtra las líneas que contienen los residuos y el átomo alfa (CA).  
- Cuenta las ocurrencias de cada residuo en cada proteína.  
- Genera archivos CSV con los resultados para cada proteína de forma clara y ordenada.  
- Facilita la comparación y análisis de los residuos presentes. 

---

##  Estructura del proyecto

```
📂 obtencion_aminoacido
 ┣ 📜 residues_count.sh   # Script Bash automatizado para conteo
 ┣ 📜 HEM_A-Residues-Count.csv  # CSV con conteo para proteína HEM_A
 ┣ 📜 GFP_A-Residues-Count.csv  # CSV con conteo para proteína GFP_A
 ┣ 📜 ACE2_A-Residues-Count.csv # CSV con conteo para proteína ACE2_A
 ┣ 📜 HEM_A.pdb   # Archivos PDB originales
 ┣ 📜 GFP_A.pdb   # Archivos PDB originales
 ┗ 📜 ACE2_A.pdb  # Archivos PDB originales          
```

---

##  Requisitos del sistema


```
- Sistema operativo Linux
- Bash shell disponible.
- Comandos bàsicos: grep, wc , echo (disponibles por defecto en Linux)
```

---

### Ejecución del Script:
```
1. Dar permisos de ejcuciòn (solo una vez)
     chmod +x residues_count.sh
2. Ejecutar el Script:
     ./residues_count.sh

```

---

## ¿Que hace el script?

Para cada proteìna HEM_A, GFP_A, ACE"_A y para cada residuo LYS, ARG, HIS, GLU, ASP:

```
- Busca las lìneas del archivo PDB correspondiente al residuo.
- Filtra solo las lìneas que contienen el àtomo "CA" (carbonno alfa).
- Cuenta cuàntas ocurrencias hay (cada una representa un residuo).
- Guarda los resultados en un archivo CSV con formato:
aas;HEM_A
LYS;11
ARG;3
HIS;10
GLU;4
ASP;8

- Informa por terminal cuando cada archivo CSV es creado.

Ejemplo salida en terminal:
Archivo HEM_A-Residues-Count.csv creado con éxito.
Archivo GFP_A-Residues-Count.csv creado con éxito.
Archivo ACE2_A-Residues-Count.csv creado con éxito.

Ejemplo contenido archivo CSV (HEM_A-Residues-Count.csv):
aas;HEM_A
LYS;11
ARG;3
HIS;10
GLU;4
ASP;8

Cada archivo CSV tendrá esta estructura, pero con los datos correspondientes a cada proteína.
```

## Limpieza 
---


Si deseas eliminar los archivos generados: rm *_Residues-Count.csv *_LYS-CA.pdb


---

##  Conclusión

El script  **residues_count.sh** permite automatizar el conteo de residuos específicos en múltiples archivos **PDB**, agilizando el análisis bioinformático de las proteínas estudiadas y facilitando la exportación de datos para posteriores análisis o visualización.

---
