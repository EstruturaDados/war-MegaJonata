#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

//==================================================
// ESTRUTURA
//==================================================

typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

//==================================================
// VARIÁVEIS GLOBAIS PARA COMPARAÇÕES
//==================================================

long comparacoes = 0;

//==================================================
// FUNÇÃO PARA EXIBIR COMPONENTES
//==================================================

void mostrarComponentes(Componente vetor[], int tamanho) {

    printf("\n============================================\n");
    printf("COMPONENTES DA TORRE DE RESGATE\n");
    printf("============================================\n");

    for(int i = 0; i < tamanho; i++) {

        printf("\nComponente %d", i + 1);
        printf("\nNome: %s", vetor[i].nome);
        printf("\nTipo: %s", vetor[i].tipo);
        printf("\nPrioridade: %d\n", vetor[i].prioridade);
    }
}

//==================================================
// BUBBLE SORT POR NOME
//==================================================

void bubbleSortNome(Componente vetor[], int tamanho) {

    Componente aux;

    comparacoes = 0;

    for(int i = 0; i < tamanho - 1; i++) {

        for(int j = 0; j < tamanho - i - 1; j++) {

            comparacoes++;

            if(strcmp(vetor[j].nome, vetor[j + 1].nome) > 0) {

                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

//==================================================
// INSERTION SORT POR TIPO
//==================================================

void insertionSortTipo(Componente vetor[], int tamanho) {

    comparacoes = 0;

    for(int i = 1; i < tamanho; i++) {

        Componente chave = vetor[i];
        int j = i - 1;

        while(j >= 0) {

            comparacoes++;

            if(strcmp(vetor[j].tipo, chave.tipo) > 0) {

                vetor[j + 1] = vetor[j];
                j--;

            } else {
                break;
            }
        }

        vetor[j + 1] = chave;
    }
}

//==================================================
// SELECTION SORT POR PRIORIDADE
//==================================================

void selectionSortPrioridade(Componente vetor[], int tamanho) {

    comparacoes = 0;

    for(int i = 0; i < tamanho - 1; i++) {

        int menor = i;

        for(int j = i + 1; j < tamanho; j++) {

            comparacoes++;

            if(vetor[j].prioridade < vetor[menor].prioridade) {
                menor = j;
            }
        }

        if(menor != i) {

            Componente aux = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = aux;
        }
    }
}

//==================================================
// BUSCA BINÁRIA POR NOME
// (vetor deve estar ordenado por nome)
//==================================================

int buscaBinariaPorNome(Componente vetor[],
                        int tamanho,
                        char nome[]) {

    int inicio = 0;
    int fim = tamanho - 1;

    long comparacoesBusca = 0;

    while(inicio <= fim) {

        int meio = (inicio + fim) / 2;

        comparacoesBusca++;

        int resultado =
            strcmp(vetor[meio].nome, nome);

        if(resultado == 0) {

            printf("\nComparacoes da busca: %ld\n",
                   comparacoesBusca);

            return meio;
        }

        if(resultado < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    printf("\nComparacoes da busca: %ld\n",
           comparacoesBusca);

    return -1;
}

//==================================================
// MEDIÇÃO DE TEMPO
//==================================================

double medirTempo(void (*algoritmo)
                 (Componente[], int),
                 Componente vetor[],
                 int tamanho) {

    clock_t inicio, fim;

    inicio = clock();

    algoritmo(vetor, tamanho);

    fim = clock();

    return ((double)(fim - inicio))
           / CLOCKS_PER_SEC;
}

//==================================================
// FUNÇÃO PRINCIPAL
//==================================================

int main() {

    Componente componentes[MAX_COMPONENTES];

    int quantidade;
    int opcao;

    printf("=====================================\n");
    printf("TORRE DE RESGATE - SAFE ZONE FINAL\n");
    printf("=====================================\n");

    do {

        printf("\nQuantidade de componentes (1 a 20): ");
        scanf("%d", &quantidade);

    } while(quantidade < 1 ||
            quantidade > MAX_COMPONENTES);

    getchar();

    // Cadastro dos componentes
    for(int i = 0; i < quantidade; i++) {

        printf("\n--- COMPONENTE %d ---\n", i + 1);

        printf("Nome: ");
        fgets(componentes[i].nome,
              sizeof(componentes[i].nome),
              stdin);
        componentes[i].nome[
            strcspn(componentes[i].nome,"\n")] = '\0';

        printf("Tipo: ");
        fgets(componentes[i].tipo,
              sizeof(componentes[i].tipo),
              stdin);
        componentes[i].tipo[
            strcspn(componentes[i].tipo,"\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        scanf("%d", &componentes[i].prioridade);
        getchar();
    }

    do {

        printf("\n================================");
        printf("\nMENU DE ESTRATEGIAS");
        printf("\n================================");
        printf("\n1 - Bubble Sort por Nome");
        printf("\n2 - Insertion Sort por Tipo");
        printf("\n3 - Selection Sort por Prioridade");
        printf("\n4 - Busca Binaria por Nome");
        printf("\n5 - Mostrar Componentes");
        printf("\n0 - Sair");
        printf("\nOpcao: ");

        scanf("%d", &opcao);
        getchar();

        switch(opcao) {

            case 1: {

                double tempo =
                    medirTempo(
                        bubbleSortNome,
                        componentes,
                        quantidade);

                printf("\nOrdenacao por NOME concluida!");
                printf("\nComparacoes: %ld",
                       comparacoes);
                printf("\nTempo: %.6f segundos\n",
                       tempo);

                mostrarComponentes(
                    componentes,
                    quantidade);

                break;
            }

            case 2: {

                double tempo =
                    medirTempo(
                        insertionSortTipo,
                        componentes,
                        quantidade);

                printf("\nOrdenacao por TIPO concluida!");
                printf("\nComparacoes: %ld",
                       comparacoes);
                printf("\nTempo: %.6f segundos\n",
                       tempo);

                mostrarComponentes(
                    componentes,
                    quantidade);

                break;
            }

            case 3: {

                double tempo =
                    medirTempo(
                        selectionSortPrioridade,
                        componentes,
                        quantidade);

                printf("\nOrdenacao por PRIORIDADE concluida!");
                printf("\nComparacoes: %ld",
                       comparacoes);
                printf("\nTempo: %.6f segundos\n",
                       tempo);

                mostrarComponentes(
                    componentes,
                    quantidade);

                break;
            }

            case 4: {

                char chave[30];

                printf("\nIMPORTANTE:");
                printf("\nA busca binaria exige que o vetor esteja ordenado por nome.\n");

                printf("\nDigite o componente-chave: ");

                fgets(chave,
                      sizeof(chave),
                      stdin);

                chave[strcspn(chave,"\n")] = '\0';

                int posicao =
                    buscaBinariaPorNome(
                        componentes,
                        quantidade,
                        chave);

                if(posicao >= 0) {

                    printf("\nCOMPONENTE ENCONTRADO!\n");
                    printf("Nome: %s\n",
                           componentes[posicao].nome);

                    printf("Tipo: %s\n",
                           componentes[posicao].tipo);

                    printf("Prioridade: %d\n",
                           componentes[posicao].prioridade);

                    printf("\n>>> Torre de resgate pronta para ativacao! <<<\n");

                } else {

                    printf("\nComponente nao encontrado.\n");
                }

                break;
            }

            case 5:

                mostrarComponentes(
                    componentes,
                    quantidade);

                break;

            case 0:

                printf("\nEncerrando sistema...\n");
                break;

            default:

                printf("\nOpcao invalida!\n");
        }

    } while(opcao != 0);

    return 0;
}
