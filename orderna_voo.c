#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int duracao, delay;
} Dados;

// QUICKSORT
int separa(Dados v[], int p, int r) {
    int c = v[r].duracao;
    int t, t2, j = p;
    for (int k = p; k < r; ++k) {
        if (v[k].duracao <= c) {
            t = v[j].duracao;
            t2 = v[j].delay;
            v[j].duracao = v[k].duracao;
            v[j].delay = v[k].delay;
            v[k].duracao = t;
            v[k].delay = t2;
            ++j;
        }
    }
    t = v[j].duracao;
    t2 = v[j].delay;
    v[j].duracao = v[r].duracao;
    v[j].delay = v[r].delay;
    v[r].duracao = t;
    v[r].delay = t2;
    return j;
}

void quickSort(Dados v[], int p, int r) {
    while (p < r) {
        int j = separa(v, p, r);
        if (j-p < r-j) {
            quickSort(v, p, j-1);
            p = j+1;
        } else {
            quickSort(v, j+1, r);
            r = j-1;
        }
    }
}

int main () {
    FILE *arq, *arqNovo;
    int i = 0, j = 0;
    int tvoos_ate3hrs = 0, tvoos_ate6hrs = 0, tvoos_ate9hrs = 0, tvoos_acima9hrs = 0;
    int dvoos_ate3hrs = 0, dvoos_ate6hrs = 0, dvoos_ate9hrs = 0, dvoos_acima9hrs = 0;
    Dados d, *voos;

    voos = malloc(sizeof(Dados) * 539383); // ALOCANDO VETOR A SER UTILIZADO PARA ORDENAÇÃO

    arq = fopen("Airlines.csv", "r");  // ABERTURA DO ARQUIVO DE ENTRADA
    if (!arq) {
        printf("Erro na abertura do arquivo...");
        return 0;
    }

    while (fscanf(arq, "%d,%d\n", &d.duracao, &d.delay) != EOF) {  // LOOP PARA LER O ARQUIVO DE ENTRADA
        voos[i] = d;

        if (d.duracao <= 180) {
            tvoos_ate3hrs++;
            if (d.delay == 1) {
                dvoos_ate3hrs++;
            }
        } else if (d.duracao <= 360) {
            tvoos_ate6hrs++;
            if (d.delay == 1) {
                dvoos_ate6hrs++;
            }
        } else if (d.duracao <= 540) {
            tvoos_ate9hrs++;
            if (d.delay == 1) {
                dvoos_ate9hrs++;
            }
        } else {
            tvoos_acima9hrs++;
            if (d.delay == 1) {
                dvoos_acima9hrs++;
            }
        }

        i++;
    }
    fclose(arq);

    printf("Copia concluida!\n"); // CONFIRMAÇÃO DA CÓPIA DO ARQUIVO ORIGINAL PARA O VETOR
    
    clock_t start_time = clock(); // INÍCIO DO TIMER
    double elapsed_time;
    quickSort(voos, 0, 539382);
    elapsed_time = (double)(clock() - start_time)/CLOCKS_PER_SEC;
    printf("\nTempo gasto (Quick Sort): %fs\n", elapsed_time);  // FIM DO TIMER

    arqNovo = fopen("Airlines-saida.txt", "w");  // ABERTURA DO ARQUIVO DE SAÍDA
    if (!arqNovo) {
        printf("Erro na abertura do arquivo...");
        return 0;
    }

    do { // LOOP PARA SALVAR O VETOR NO ARQUIVO DE SAÍDA
        fprintf(arqNovo, "%d %d\n", voos[j].duracao, voos[j].delay);
        j++;
    } while (j < 539383);

    printf("\nPorcentagem de atraso em voos de até 3hrs de duração: %.2f%%\n", ((float) dvoos_ate3hrs / tvoos_ate3hrs)*100);
    printf("Porcentagem de atraso em voos de até 6hrs de duração: %.2f%%\n", ((float) dvoos_ate6hrs / tvoos_ate6hrs)*100);
    printf("Porcentagem de atraso em voos de até 9hrs de duração: %.2f%%\n", ((float) dvoos_ate9hrs / tvoos_ate9hrs)*100);
    printf("Porcentagem de atraso em voos com mais de 9hrs de duração: %.2f%%\n", ((float) dvoos_acima9hrs / tvoos_acima9hrs)*100);

    fclose(arqNovo);
    free(voos);  // DESALOCANDO VETOR

    return 0;
}
