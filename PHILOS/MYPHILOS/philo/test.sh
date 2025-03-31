#!/bin/bash

# Parámetros de entrada
N_PHILOS=500oo
TIME_TO_DIE=800
TIME_TO_EAT=200
TIME_TO_SLEEP=200

# Ejecutamos el programa y capturamos la salida
./philo $N_PHILOS $TIME_TO_DIE $TIME_TO_EAT $TIME_TO_SLEEP > out.txt

# Obtenemos el timestamp del mensaje "died"
death_line=$(grep "died" out.txt)
timestamp=$(echo $death_line | awk '{print $1}')

echo "Philosopher died at: $timestamp ms (expected around $TIME_TO_DIE ms)"

# Comprobamos si se excede el margen de 10ms
if (( timestamp > TIME_TO_DIE + 10 )); then
    echo "❌ Tiempo excedido: $((timestamp - TIME_TO_DIE))ms de retraso"
else
    echo "✅ Dentro del límite: $((timestamp - TIME_TO_DIE))ms"
fi
