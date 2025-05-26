#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um processo
typedef struct {
    int id;              // ID do processo
    int tempo_burst;     // Tempo de execução do processo (Burst Time)
    int tempo_espera;    // Tempo de espera (Waiting Time)
    int tempo_retorno;   // Tempo de retorno (Turnaround Time)
} Processo;

// Função para ordenar os processos pelo tempo de execução (burst time) de forma crescente
int compare(const void *a, const void *b) {
    return ((Processo *)a)->tempo_burst - ((Processo *)b)->tempo_burst;
}

// Função para calcular o tempo de espera e o tempo de retorno de cada processo (SJF não-preemptivo)
void calcularTemposSJF(Processo processos[], int n) {
    int total_tempo_espera = 0;
    int total_tempo_retorno = 0;

    // O primeiro processo no SJF (após a ordenação) não tem tempo de espera inicial
    processos[0].tempo_espera = 0;

    // Calcular o tempo de espera para os processos subsequentes
    for (int i = 1; i < n; i++) {
        processos[i].tempo_espera = processos[i - 1].tempo_espera + processos[i - 1].tempo_burst;
        total_tempo_espera += processos[i].tempo_espera;
    }

    // Calcular o tempo de retorno para todos os processos
    for (int i = 0; i < n; i++) {
        processos[i].tempo_retorno = processos[i].tempo_espera + processos[i].tempo_burst;
        total_tempo_retorno += processos[i].tempo_retorno;
    }

    // Impressão da tabela de resultados
    printf("\n--- Resultados do Escalonamento SJF (Nao-Preemptivo) ---\n");
    printf("-----------------------------------------------------------------------\n");
    printf("ID\tBurst (Exec.)\tEspera\t\tRetorno (Turnaround)\n");
    printf("-----------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n",
               processos[i].id,
               processos[i].tempo_burst,
               processos[i].tempo_espera,
               processos[i].tempo_retorno);
    }
    printf("-----------------------------------------------------------------------\n");

    if (n > 0) {
        printf("Tempo Medio de Espera: %.2f\n", (float)total_tempo_espera / n);
        printf("Tempo Medio de Retorno: %.2f\n", (float)total_tempo_retorno / n);
    }
    printf("-----------------------------------------------------------------------\n\n");
}

int main() {
    int n;

    // Solicita ao usuário o número de processos
    printf("Digite o numero de processos: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Numero de processos invalido.\n");
        return 1;
    }

    // Aloca memória para os processos
    Processo *processos = (Processo *)malloc(n * sizeof(Processo));
    if (processos == NULL) {
        printf("Erro ao alocar memoria para processos.\n");
        return 1;
    }

    // Solicita ao usuário o tempo de execução de cada processo
    printf("\nDigite os detalhes de cada processo:\n");
    for (int i = 0; i < n; i++) {
        processos[i].id = i + 1;
        printf("  Digite o tempo de burst (execucao) do Processo %d: ", processos[i].id);
        scanf("%d", &processos[i].tempo_burst);
    }

    // Ordena os processos pelo burst time (SJF não-preemptivo)
    qsort(processos, n, sizeof(Processo), compare);

    // Calcula e exibe os tempos
    calcularTemposSJF(processos, n);

    // Libera a memória alocada
    free(processos);

    return 0;
}