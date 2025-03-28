#!/bin/bash

# Define an array of the different sets of arguments
args=(
    "5 800 200 200"
    "5 600 150 150"
    "4 410 200 200"
    "100 800 200 200"
    "105 800 200 200"
    "200 800 200 200"
)

# Variables para contar pruebas correctas e incorrectas
correct=0
incorrect=0
failed_tests=()  # Arreglo para guardar las pruebas fallidas

# Loop through the arguments and execute the program with each set
for arg_set in "${args[@]}"
do
    echo "Running with parameters: $arg_set"
    
    # Run the program in the background and capture its PID
    ./philo $arg_set &
    pid=$!
    
    # Wait for 5 seconds or until the program finishes
    sleep 11
    
    # Check if the program is still running
    if ps -p $pid > /dev/null; then
        # If it's still running after 5 seconds, print "done" and exit
        echo "Done: Execution of './philo $arg_set' ran for 5 seconds successfully."
        # Kill the process if it took too long and move to the next set of args
        kill $pid
        wait $pid 2>/dev/null # to clean up the background process
        correct=$((correct + 1)) # Increment the correct counter
    else
        # If the process finished before 5 seconds, print an error and stop the test
        echo "Error: Execution of './philo $arg_set' finished before 5 seconds."
        incorrect=$((incorrect + 1)) # Increment the incorrect counter
        failed_tests+=("$arg_set")  # Añadir el conjunto de parámetros fallido al arreglo
        break # Exit the loop, thus stopping further tests
    fi

    echo "-----------------------------"

    # Pausa de 2 segundos entre cada prueba
    sleep 2
done

# Mostrar resumen al final de la ejecución
echo "=============================="
echo "Test Results:"
echo "Correct Tests: $correct"
echo "Incorrect Tests: $incorrect"

# Mostrar qué pruebas fallaron
if [ $incorrect -gt 0 ]; then
    echo "The following tests failed:"
    for test in "${failed_tests[@]}"
    do
        echo "$test"
    done
fi
