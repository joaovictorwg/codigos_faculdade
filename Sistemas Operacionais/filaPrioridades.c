#include <stdio.h>
#include <stdlib.h> 
#include <limits.h> 

// Estrutura para representar um processo
typedef struct {
    int id;                 // Identificador do processo
    int prioridade;         // Prioridade do processo (menor valor = maior prioridade)
    int tempo_chegada;      // Tempo em que o processo chega ao sistema
    int tempo_execucao;     // Tempo total de CPU necessário para o processo
    int tempo_restante;     // Tempo de CPU restante para o processo
    int tempo_conclusao;    // Tempo em que o processo termina a execução
    int tempo_espera;       // Tempo que o processo passou esperando na fila
    int tempo_retorno;      // Tempo total desde a chegada até a conclusão (turnaround time)
    int executado_pelo_menos_uma_vez; // Flag para controlar a primeira execução
} Processo;

// Função para encontrar o processo com maior prioridade que já chegou e ainda não concluiu
int encontrar_prox_processo(Processo processos[], int n_processos, int tempo_atual) {
    int idx_maior_prioridade = -1;
    int maior_prioridade = INT_MAX; // Inicializa com a menor prioridade possível (maior valor)

    for (int i = 0; i < n_processos; i++) {
        // Verifica se o processo já chegou, ainda precisa executar e tem prioridade maior (menor valor)
        if (processos[i].tempo_chegada <= tempo_atual && processos[i].tempo_restante > 0) {
            if (processos[i].prioridade < maior_prioridade) {
                maior_prioridade = processos[i].prioridade;
                idx_maior_prioridade = i;
            }
            // Critério de desempate: se a prioridade for igual, escolhe o que chegou primeiro
            else if (processos[i].prioridade == maior_prioridade) {
                if (idx_maior_prioridade == -1 || processos[i].tempo_chegada < processos[idx_maior_prioridade].tempo_chegada) {
                    idx_maior_prioridade = i;
                }
            }
        }
    }
    return idx_maior_prioridade;
}

// Função principal do escalonador
void escalonador_prioridade_preemptivo(Processo processos[], int n_processos) {
    int tempo_atual = 0;
    int processos_concluidos = 0;
    int ultimo_processo_executado = -1; // Para rastrear mudanças de contexto

    printf("\n--- Linha do Tempo da Execucao ---\n");

    while (processos_concluidos < n_processos) {
        int idx_processo_atual = encontrar_prox_processo(processos, n_processos, tempo_atual);

        if (idx_processo_atual == -1) {
            // Nenhum processo pronto para executar, avança o tempo
            if (ultimo_processo_executado != -2) { // Evita imprimir "Ocioso" repetidamente
                 printf("Tempo %d: CPU Ociosa\n", tempo_atual);
                 ultimo_processo_executado = -2; // -2 indica ocioso
            }
            tempo_atual++;
            continue;
        }

        Processo *p_atual = &processos[idx_processo_atual];

        if (ultimo_processo_executado != p_atual->id) {
            if (p_atual->tempo_restante == p_atual->tempo_execucao) { // Primeira vez executando
                 printf("Tempo %d: Processo %d (Prioridade %d) iniciou.\n", tempo_atual, p_atual->id, p_atual->prioridade);
            } else { // Retomando após preempção
                 printf("Tempo %d: Processo %d (Prioridade %d) retomou (preemptivo).\n", tempo_atual, p_atual->id, p_atual->prioridade);
            }
            ultimo_processo_executado = p_atual->id;
        }


        // Simula a execução por uma unidade de tempo
        p_atual->tempo_restante--;
        tempo_atual++;

        // Verifica se o processo atual concluiu
        if (p_atual->tempo_restante == 0) {
            p_atual->tempo_conclusao = tempo_atual;
            p_atual->tempo_retorno = p_atual->tempo_conclusao - p_atual->tempo_chegada;
            p_atual->tempo_espera = p_atual->tempo_retorno - p_atual->tempo_execucao;
            processos_concluidos++;
            printf("Tempo %d: Processo %d (Prioridade %d) concluiu.\n", tempo_atual, p_atual->id, p_atual->prioridade);
            ultimo_processo_executado = -1; // Reseta para indicar que o processo terminou
        }
    }
    printf("--- Fim da Execucao ---\n\n");
}

// Função para imprimir os resultados
void imprimir_resultados(Processo processos[], int n_processos) {
    float tempo_medio_espera = 0;
    float tempo_medio_retorno = 0;

    printf("---------------------------------------------------------------------------------------------------\n");
    printf("ID\tPrioridade\tChegada\tExecucao\tConclusao\tRetorno (Turnaround)\tEspera\n");
    printf("---------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < n_processos; i++) {
        printf("%d\t%d\t\t%d\t%d\t\t%d\t\t%d\t\t\t%d\n",
               processos[i].id,
               processos[i].prioridade,
               processos[i].tempo_chegada,
               processos[i].tempo_execucao,
               processos[i].tempo_conclusao,
               processos[i].tempo_retorno,
               processos[i].tempo_espera);
        tempo_medio_espera += processos[i].tempo_espera;
        tempo_medio_retorno += processos[i].tempo_retorno;
    }
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("Tempo Medio de Espera: %.2f\n", tempo_medio_espera / n_processos);
    printf("Tempo Medio de Retorno: %.2f\n", tempo_medio_retorno / n_processos);
}

int main() {
    int n_processos;

    printf("Digite o numero de processos: ");
    scanf("%d", &n_processos);

    if (n_processos <= 0) {
        printf("Numero de processos invalido.\n");
        return 1;
    }

    Processo *processos = (Processo *)malloc(n_processos * sizeof(Processo));
    if (processos == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    printf("\nDigite os detalhes de cada processo:\n");
    for (int i = 0; i < n_processos; i++) {
        printf("\nProcesso %d:\n", i + 1);
        processos[i].id = i + 1;
        printf("  Tempo de Chegada: ");
        scanf("%d", &processos[i].tempo_chegada);
        printf("  Tempo de Execucao: ");
        scanf("%d", &processos[i].tempo_execucao);
        printf("  Prioridade (menor valor = maior prioridade): ");
        scanf("%d", &processos[i].prioridade);
        processos[i].tempo_restante = processos[i].tempo_execucao;
        processos[i].tempo_conclusao = 0;
        processos[i].tempo_espera = 0;
        processos[i].tempo_retorno = 0;
        processos[i].executado_pelo_menos_uma_vez = 0;
    }

    escalonador_prioridade_preemptivo(processos, n_processos);
    imprimir_resultados(processos, n_processos);

    free(processos); // Libera a memória alocada
    return 0;
}