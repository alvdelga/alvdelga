#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

void print_current_time() {
    struct timeval tv;
    struct timezone tz;

    // Obtener la hora actual con gettimeofday
    if (gettimeofday(&tv, &tz) == -1) {
        perror("gettimeofday failed");
        exit(1);
    }

    // Mostrar la hora actual en segundos y microsegundos
    printf("Tiempo actual (segundos): %ld\n", tv.tv_sec);
    printf("Microsegundos: %ld\n", tv.tv_usec);
}

int main() {
    printf("Imprimiendo la hora actual:\n");
    print_current_time();

    // Esperar 2 segundos
    printf("Esperando 2 segundos...\n");
    sleep(2);

    // Mostrar la hora después de la espera
    printf("Tiempo después de esperar 2 segundos:\n");
    print_current_time();

    return 0;
}
