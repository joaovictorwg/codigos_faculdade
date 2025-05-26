#include <stdio.h>

#define MAX_PROCESSES 10

// Estrutura para representar um processo
typedef struct {
    int id;             // ID do processo
    int tempo_execucao; // Tempo de execucao
    int tempo_conclusao;// Tempo de conclusao 
    int tempo_retorno;  // Tempo de retorno 
    int tempo_espera;   // Tempo de espera 
} Process;

// Funcao para calcular os tempos
void calcular_tempos_fifo(Process processos[], int n) {
    if (n == 0) {
        return;
    }

    // Lógica para calcular o tempo de espera:
    // O primeiro processo nao espera (relativo ao início do processamento da fila).
    processos[0].tempo_espera = 0;
    for (int i = 1; i < n; i++) {
        processos[i].tempo_espera = processos[i-1].tempo_espera + processos[i-1].tempo_execucao;
    }


    // Lógica para calcular o tempo de retorno:
    for (int i = 0; i < n; i++) {
        processos[i].tempo_retorno = processos[i].tempo_espera + processos[i].tempo_execucao;
        processos[i].tempo_conclusao = processos[i].tempo_retorno;
    }
}

// Funcao para imprimir os resultados no formato especificado
void imprimir_resultados(Process processos[], int n_processos) {
    float tempo_medio_espera = 0;
    float tempo_medio_retorno = 0;


    printf("----------------------------------------------------------------------\n"); 
    printf("ID\tExecucao\tConclusao\tRetorno (Turnaround)\tEspera\n");
    printf("----------------------------------------------------------------------\n"); 

    for (int i = 0; i < n_processos; i++) {
 
        printf("%d\t%d\t\t%d\t\t%d\t\t\t%d\n",
               processos[i].id,
               processos[i].tempo_execucao,
               processos[i].tempo_conclusao,
               processos[i].tempo_retorno,
               processos[i].tempo_espera);
        tempo_medio_espera += processos[i].tempo_espera;
        tempo_medio_retorno += processos[i].tempo_retorno;
    }
    printf("----------------------------------------------------------------------\n"); 
    if (n_processos > 0) {
        printf("Tempo Medio de Espera: %.2f\n", tempo_medio_espera / n_processos);
        printf("Tempo Medio de Retorno: %.2f\n", tempo_medio_retorno / n_processos);
    } else {
        printf("Tempo Medio de Espera: 0.00\n");
        printf("Tempo Medio de Retorno: 0.00\n");
    }
}

int main() {
    int n;

    printf("Digite o numero de processos: ");
    scanf("%d", &n);

    if (n > MAX_PROCESSES || n <= 0) {
        printf("Numero invalido de processos! O numero maximo e %d.\n", MAX_PROCESSES);
        if (n <= 0) {
             printf("Nenhum processo para executar.\n");
        }
        return 1;
    }

    Process processes[n]; 

    // Entrada dos processos 
    printf("\n--- Entrada dos Processos ---\n");
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("\nProcesso P%d:\n", processes[i].id);
        
        printf("  Tempo de Execucao (Burst): ");
        scanf("%d", &processes[i].tempo_execucao);
    }
    
    printf("\nEscalonando os processos utilizando FIFO...\n");

    // Calcula os tempos de espera, retorno e conclusao 
    calcular_tempos_fifo(processes, n);

    // Imprime os resultados no novo formato 
    imprimir_resultados(processes, n);

    return 0;
}