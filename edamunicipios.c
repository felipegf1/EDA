#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int ibge;
    char municipio[30];
    char UF[3];
    char regiao[30];
    int populacao;
    char porte[30];
}MUNICIPIOS;

typedef struct{
    int ibge;
    int pop;
}MSORT;

int buscaBinaria(int *V, int n, int chave){
 int inicio, final, meio;
 inicio = 0;
 final = n - 1;
 while(inicio <= final){
 meio = (inicio + final)/2;
 if (chave == V[meio])
 return meio;
 if (chave < V[meio])
 final = meio - 1;//busca nos valores menores
 else
 inicio = meio + 1;//busca nos valores maiores
 }
 return -1; //chave nao encontrada
}

int buscaSequencialDesordenada(int *V, int n, int chave){
 int p, posic = -1;
 for(p=0;p<n;p++){
    if(chave == V[p]){
    posic = p;
    }
 }
 return posic;
}

void bubbleSort(int vet[], int tam){
 int i,j, temp;
 for(i=tam-1; i>0; i--){
 for(j=0; j < i; j++) //Faz trocas até posição i
 if( vet[j] > vet[j+1] ){
 temp = vet[j];
 vet[j] = vet[j+1];
 vet[j+1] = temp;
        }
    }
}

void limpar_tela() {      // funcao para limpar a tela
    #ifdef _WIN32
        system("cls");
    #elif __linux__ 
        system("clear");
    #endif         
}


int main(){
int i = 0;
FILE* arquivo;
MUNICIPIOS dados;
MUNICIPIOS ibge[5570];
int idibge[5570];
int n; // variavel para usar no switch
int b; // variavel que vai receber o resultado da funcao
int numero; // numero para ser comparado com o ibge

do{
    limpar_tela();
    printf("Escolha uma opcao: \n");
    printf("1 - Carregar o vetor com as informacoes do arquivo\n");
    printf("2 - Procurar por municipio no arquivo\n");
    printf("3 - Encerrar Programa\n");
    scanf("%d", &n);
    fflush(stdin);
    switch(n){
       
        case 1:
            limpar_tela();
            arquivo = fopen("Lista-Municipios.csv", "rb");
            if(!arquivo){
                printf("erro");
            }

            while(fscanf(arquivo,"%[^,],%[^,],%[^,],%[^,],%d,%d\n", dados.UF, dados.municipio, dados.regiao, dados.porte, &dados.ibge, &dados.populacao) != EOF){
                idibge[i] = dados.ibge;
                ibge[i] = dados;
                printf("%n",&i);
                i++;
            }
            fclose(arquivo);
        
        break;

        case 2:
            limpar_tela();
            printf("Informe o IBGE a ser procurado: ");
            scanf("%d", &numero);
            b = buscaBinaria(idibge, 5570, numero);
            printf("%d", b);

            printf("Municipio: %s\n", ibge[b].municipio);
            printf("UF: %s\n", ibge[b].UF);
            printf("Regiao: %s\n", ibge[b].regiao);
            printf("Populacao em 2010: %d\n", ibge[b].populacao);
            printf("Porte: %s\n", ibge[b].porte);
            printf("\nPressione qualquer tecla para voltar ao menu \n");
            fflush(stdin);
            getchar();
            fflush(stdin);
        break;    

        case 3:
        fflush(stdin);
        printf("%d\n", ibge[b].populacao);
        getchar();
        break;
    }


}while(n != 4);




return 0;
}