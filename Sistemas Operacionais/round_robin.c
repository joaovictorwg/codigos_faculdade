#include <stdio.h>
#include <stdlib.h>

// Estrutura para representar um processo
typedef struct {
    int id;
    int tempo_burst;          // Tempo original de execução (CPU burst)
    int tempo_chegada;        // Tempo de chegada (vamos assumir 0 para este exemplo)
    int tempo_restante;       // Tempo restante de execução
    int tempo_conclusao;
    int tempo_retorno;        // Turnaround Time (Conclusão - Chegada)
    int tempo_espera;         // Waiting Time (Retorno - Burst)
} Processo;

// Função para executar o algoritmo Round Robin e coletar dados
void roundRobin(Processo processos[], int n, int quantum, int detalhar_execucao) {
    // Inicializa o tempo restante para cada processo
    for (int i = 0; i < n; i++) {
        processos[i].tempo_restante = processos[i].tempo_burst;
        processos[i].tempo_conclusao = 0; // Inicializa
        processos[i].tempo_retorno = 0;
        processos[i].tempo_espera = 0;
        processos[i].tempo_chegada = 0;
    }

    int tempo_corrente = 0;
    int concluidos = 0;
    int processos_na_rodada_atual = n; 

    if (detalhar_execucao) {
        printf("\n--- Linha do Tempo da Execucao (Round Robin) ---\n");
    }

    while (concluidos < n) {
    
        for (int i = 0; i < n; i++) {
            if (processos[i].tempo_restante > 0) {

                int tempo_executar_agora = 0;

                if (processos[i].tempo_restante > quantum) {
                    tempo_executar_agora = quantum;
                    tempo_corrente += quantum;
                    processos[i].tempo_restante -= quantum;
                    if (detalhar_execucao) {
                        printf("Tempo %d: Processo %d executou por %d unidades. Restante: %d\n",
                               tempo_corrente - quantum, processos[i].id, quantum, processos[i].tempo_restante);
                    }
                } else {
                    tempo_executar_agora = processos[i].tempo_restante;
                    tempo_corrente += processos[i].tempo_restante;
                    processos[i].tempo_restante = 0;
                    concluidos++;
                    
                    processos[i].tempo_conclusao = tempo_corrente;
                    processos[i].tempo_retorno = processos[i].tempo_conclusao - processos[i].tempo_chegada;
                    processos[i].tempo_espera = processos[i].tempo_retorno - processos[i].tempo_burst;
                    if (detalhar_execucao) {
                        printf("Tempo %d: Processo %d executou por %d unidades. CONCLUIDO.\n",
                               tempo_corrente - tempo_executar_agora, processos[i].id, tempo_executar_agora);
                    }
                }
            }
        }
    }
    if (detalhar_execucao) {
        printf("--- Fim da Execucao Detalhada ---\n\n");
    }
}

// Função para imprimir os resultados em formato de tabela
void imprimir_tabela_resultados(Processo processos[], int n) {
    float tempo_medio_espera = 0;
    float tempo_medio_retorno = 0;

    printf("\n--- Resultados do Escalonamento Round Robin ---\n");
    printf("-------------------------------------------------------------------------------------\n");
    printf("ID\tBurst (Exec.)\tChegada\tConclusao\tRetorno (Turnaround)\tEspera\n");
    printf("-------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t%d\t\t%d\t\t\t%d\n",
               processos[i].id,
               processos[i].tempo_burst,
               processos[i].tempo_chegada, // Será 0 neste exemplo
               processos[i].tempo_conclusao,
               processos[i].tempo_retorno,
               processos[i].tempo_espera);
        tempo_medio_espera += processos[i].tempo_espera;
        tempo_medio_retorno += processos[i].tempo_retorno;
    }
    printf("-------------------------------------------------------------------------------------\n");
    if (n > 0) {
        printf("Tempo Medio de Espera: %.2f\n", tempo_medio_espera / n);
        printf("Tempo Medio de Retorno: %.2f\n", tempo_medio_retorno / n);
    }
    printf("-------------------------------------------------------------------------------------\n\n");
}

int main() {
    int n, quantum;
    int detalhar_execucao_flag;

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
        // No código original era 'tempo', mudei para 'tempo_burst' para clareza
        printf("  Digite o tempo de burst (execucao) do Processo %d: ", processos[i].id);
        scanf("%d", &processos[i].tempo_burst);
        // Assumindo que todos chegam no tempo 0, conforme o código original
        processos[i].tempo_chegada = 0;
    }

    // Solicita ao usuário o tempo de quantum
    printf("\nDigite o quantum de tempo: ");
    scanf("%d", &quantum);

    if (quantum <= 0) {
        printf("Quantum invalido.\n");
        free(processos);
        return 1;
    }

    printf("\nDeseja ver a linha do tempo detalhada da execucao? (1 para Sim, 0 para Nao): ");
    scanf("%d", &detalhar_execucao_flag);

    // Executa o algoritmo Round Robin
    roundRobin(processos, n, quantum, detalhar_execucao_flag);

    // Imprime a tabela de resultados
    imprimir_tabela_resultados(processos, n);

    // Libera a memória alocada
    free(processos);

    return 0;
}