#!/bin/bash

# Lista de proteínas
proteins=("HEM_A" "GFP_A" "ACE2_A")

# Lista de residuos cargados
residues=("LYS" "ARG" "HIS" "GLU" "ASP")

# Carpeta de trabajo: PDBs ya deben estar aquí
workdir="$(pwd)"

for protein in "${proteins[@]}"; do
    # Archivo de salida CSV
    csv_file="${protein}_Residues-Count.csv"
    
    # Crear cabecera
    echo "aas;${protein}" > "${csv_file}"
    
    for res in "${residues[@]}"; do
        # Contar CA de cada residuo
        count=$(grep "${res}" "${protein}.pdb" | grep "CA" | wc -l)
        echo "${res};${count}" >> "${csv_file}"
    done

    echo "Archivo ${csv_file} creado con éxito."
done
