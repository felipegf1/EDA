#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int ID, idade, salario, comprou, linha;
    char genero[10];
} Dados;

typedef struct {
    Dados d, *info;
    struct TABP *Esquerda;
    struct TABP *Direita;
} TABP;

TABP* adicionarNo(TABP *A, int valor, int linha) {
    if (A == NULL) {
        TABP *aux = malloc(sizeof(TABP));
        aux->d.ID = valor;
        aux->d.linha = linha;
        aux->Esquerda = NULL;
        aux->Direita = NULL;
        return aux;
    } else {
        if (valor < A->d.ID) {
            A->Esquerda = adicionarNo(A->Esquerda, valor, linha);
        } else {
            A->Direita = adicionarNo(A->Direita, valor, linha);
        }
        return A;
    }
}

void printArvore(TABP *A, Dados info[]) {
    if (A) {
        printArvore(A->Esquerda, info);
        printf("ID: %04d, Age: %02d, Purchased: %d, AnnualSalary: %06d, Gender: %s\n", info[A->d.linha].ID, info[A->d.linha].idade,
                info[A->d.linha].comprou, info[A->d.linha].salario, info[A->d.linha].genero);
        printArvore(A->Direita, info);
    }
}

void menu() {
    printf("-------------------------------------------\n");
    printf("                ABP - GRUPO D              \n");
    printf("-------------------------------------------\n");
    printf("OPÇÕES:\n");
    printf("1) Carregar arquivo de dados\n");
    printf("2) Emitir relatório\n");
    printf("3) Sair do programa\n");
    printf("-------------------------------------------\n");
}

void limpar_tela() {
    #ifdef _WIN32
        system("cls");
    #elif __linux__ 
        system("clear");
    #endif         
}

int main () {
    FILE *arq;
    char nome_arquivo[50];
    Dados d, dados[1000];
    int N, i, id[1000];
    TABP *arvore = NULL;
    i = 0;

    do {
        limpar_tela();
        menu();
        scanf("%d", &N);
        fflush(stdin);

        switch (N) {
            case 1:
                limpar_tela();
                printf("Digite o nome do arquivo (SEM O .csv):\n");
                scanf("%s", nome_arquivo);
                fflush(stdin);

                arq = fopen(strcat(nome_arquivo, ".csv"), "r");

                if (!arq) {
                    printf("Erro na abertura...");
                    return 0;
                }

                while (fscanf(arq, "%[^,],%d,%d,%d,%d\n", d.genero, &d.ID, &d.idade, &d.salario, &d.comprou) != EOF) {
                    dados[i] = d;
                    id[i] = d.ID;
                    i++;
                }
                fclose(arq);
                printf("Arquivo copiado!\n");

                for (int j = 0; j < i; j++) {
                    arvore = adicionarNo(arvore, id[j], j);        
                }
                getchar();
                fflush(stdin);
    
                break;
            case 2:
                if (arvore == NULL) {
                    printf("Arquivo vazio!!!\n");
                    getchar();
                    fflush(stdin);
                } else {
                    printArvore(arvore, dados);
                    getchar();
                    fflush(stdin);
                }
                break;
            case 3:
                break;        
        }

    } while (N != 3);
}