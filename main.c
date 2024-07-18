#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/wait.h>

#define BUFFER_SIZE 11

// Função para verificar se um número é primo
int is_prime(int number) {
    if (number <= 1) return 0;
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) return 0;
    }
    return 1;
}

// Função do produtor
void producer(int write_pipe, int count) {
    srand(time(NULL));
    int N = 1;

    for (int i = 0; i < count; i++) {
        int delta = rand() % 100 + 1;
        N += delta;

        char buffer[BUFFER_SIZE];
        snprintf(buffer, sizeof(buffer), "%d", N);
        write(write_pipe, buffer, BUFFER_SIZE);
    }

    // Enviar 0 para sinalizar o fim
    char buffer[BUFFER_SIZE];
    snprintf(buffer, sizeof(buffer), "%d", 0);
    write(write_pipe, buffer, BUFFER_SIZE);

    close(write_pipe);
}

// Função do consumidor
void consumer(int read_pipe) {
    char buffer[BUFFER_SIZE];

    while (1) {
        read(read_pipe, buffer, BUFFER_SIZE);
        int number = atoi(buffer);

        if (number == 0) break;

        if (is_prime(number)) {
            printf("Número primo recebido: %d\n", number);
        } else {
            printf("Número não primo recebido: %d\n", number);
        }
    }

    close(read_pipe);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <quantidade de números>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int count = atoi(argv[1]);
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Processo filho - Consumidor
        close(pipefd[1]); // Fechar extremidade de escrita
        consumer(pipefd[0]);
        exit(EXIT_SUCCESS);
    } else {
        // Processo pai - Produtor
        close(pipefd[0]); // Fechar extremidade de leitura
        producer(pipefd[1], count);
        wait(NULL); // Esperar pelo término do consumidor
        exit(EXIT_SUCCESS);
    }

    return 0;
}
