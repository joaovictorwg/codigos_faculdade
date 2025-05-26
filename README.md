# Relatório: Algoritmos de Escalonamento de Processos em Sistemas Operacionais

## Introdução

O gerenciamento de processos é uma das funções mais importantes de um sistema operacional. Para garantir o uso eficiente do processador e proporcionar uma experiência justa e responsiva aos usuários, o sistema operacional utiliza algoritmos de escalonamento para decidir qual processo será executado em cada momento. Este relatório apresenta uma análise dos principais algoritmos de escalonamento estudados na disciplina de Sistemas Operacionais: FIFO (First-In, First-Out), SJF (Shortest Job First) não-preemptivo, Round Robin e Prioridades Preemptivo. Cada algoritmo será explicado de forma simples, destacando suas principais características, funcionamento e diferenças.

---

## Desenvolvimento

### 1. FIFO (First-In, First-Out)

O algoritmo FIFO, também conhecido como FCFS (First Come, First Served), é o mais simples entre os algoritmos de escalonamento. Nele, os processos são atendidos na ordem em que chegam na fila, sem qualquer tipo de preempção ou prioridade. Cada processo espera até que todos os anteriores terminem sua execução.

**Características:**
- Simplicidade de implementação.
- Não há preempção: um processo só sai da CPU quando termina.
- Pode causar longos tempos de espera para processos curtos que chegam depois de processos longos (efeito "convoy").

**Exemplo de uso no código:**  
O programa solicita ao usuário o número de processos e seus tempos de execução. Em seguida, calcula e exibe os tempos de espera, retorno e conclusão de cada processo, além das médias.

---

### 2. SJF (Shortest Job First) Não-Preemptivo

O SJF é um algoritmo que seleciona, entre os processos prontos, aquele que possui o menor tempo de execução (burst time). No modo não-preemptivo, uma vez que um processo começa a executar, ele só sai da CPU quando termina.

**Características:**
- Reduz o tempo médio de espera em relação ao FIFO.
- Pode causar inanição (starvation) de processos longos se processos curtos continuarem chegando.
- Não há preempção.

**Exemplo de uso no código:**  
O programa recebe os tempos de execução dos processos, ordena-os pelo menor burst time e calcula os tempos de espera e retorno, exibindo os resultados em tabela.

---

### 3. Round Robin

O Round Robin é um algoritmo preemptivo que utiliza um quantum de tempo fixo. Cada processo recebe uma fatia de tempo (quantum) para executar. Se não terminar nesse tempo, volta para o final da fila, permitindo que outros processos também sejam atendidos.

**Características:**
- Justo para sistemas interativos e multitarefa.
- Previne inanição, pois todos os processos recebem tempo de CPU regularmente.
- O desempenho depende do tamanho do quantum: quantums muito pequenos aumentam o overhead de troca de contexto; quantums muito grandes se aproximam do FIFO.

**Exemplo de uso no código:**  
O usuário informa o número de processos, seus tempos de execução e o quantum. O programa simula a execução dos processos em rodadas, mostrando a linha do tempo e os resultados finais.

---

### 4. Prioridades Preemptivo

Neste algoritmo, cada processo recebe uma prioridade. O escalonador sempre escolhe para execução o processo pronto com maior prioridade (menor valor numérico). Se um novo processo de prioridade maior chega, ele pode interromper o processo em execução (preempção).

**Características:**
- Permite diferenciar processos críticos de menos importantes.
- Pode causar inanição de processos de baixa prioridade.
- É preemptivo: processos podem ser interrompidos por outros de maior prioridade.

**Exemplo de uso no código:**  
O usuário informa os dados dos processos, incluindo prioridade. O programa simula a execução, mostrando quando processos são interrompidos e retomados, além de calcular os tempos de espera e retorno.

---

## Conclusão

Os algoritmos de escalonamento de processos são fundamentais para o funcionamento eficiente de sistemas operacionais. Cada algoritmo possui vantagens e desvantagens, sendo mais adequado para determinados cenários:

- **FIFO** é simples, mas pode ser injusto com processos curtos.
- **SJF** minimiza o tempo médio de espera, mas pode causar inanição.
- **Round Robin** é ideal para sistemas interativos, garantindo justiça entre processos.
- **Prioridades Preemptivo** permite tratar processos críticos com mais urgência, mas pode deixar processos de baixa prioridade esperando indefinidamente.

A escolha do algoritmo depende dos objetivos do sistema e do perfil das aplicações executadas. Compreender o funcionamento de cada um é essencial para projetar sistemas operacionais eficientes e justos.

---




introudução - 
desenvolvimento - 
conclusão
