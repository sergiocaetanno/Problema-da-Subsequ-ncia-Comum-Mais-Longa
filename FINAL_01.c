/*
Universidade Federal de Goi�s - UFG
An�lise e Projeto em Algoritmo(APA)
Profa. M�rcia Cappelle

Alunos:
Luiz Carlos B. Vieira
S�rgio Caetano J�nior
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

const int maiorTamanhoDeSequencia = 1000;

//Fun��o auxiliar que determina o menor valor entre dois inteiros

int min (int a,int b){

    if(a<=b){
        return a;
    }
    else{
        return b;
    }
}

//Fun��o que cria uma matriz din�mica tridimensional de caracteres que ser� utilizada, posteriormente, pela fun��o LCS

char *** criaMatrizStrings(char* sequencia1, char* sequencia2, int tamanhoSequencia1, int tamanhoSequencia2){

    char *** matrizStrings;
    char stringTemporaria[2]= "0";

    matrizStrings = (char***)malloc((tamanhoSequencia1 + 2) * sizeof(char**));

    for(int i = 0; i < (tamanhoSequencia1 + 2); i++){

        matrizStrings[i] = (char**)malloc((tamanhoSequencia2 + 2) * sizeof(char*));
    }

    // TAMANHO DA SEQU�NCIA 1 - > QUANTIDADE DE LINHAS -> i
    // TAMANHO DA SEQUENCIA 2 - > QUANTIDADE DE COLUNAS -> j

        for (int i = 0; i < (tamanhoSequencia1 + 2); i++){
            for(int j = 0; j < (tamanhoSequencia2 + 2); j++){

                matrizStrings[i][j] = (char*)malloc(min(tamanhoSequencia1,tamanhoSequencia2) * sizeof(char));

                if(i==0 && j>=2){

                    stringTemporaria[0] = sequencia2[j-2];
                    strncpy(matrizStrings[i][j], stringTemporaria,2);
                }

                if(j==0 && i>=2){

                    stringTemporaria[0] = sequencia1[i-2];
                    strncpy(matrizStrings[i][j], stringTemporaria,2);
                }
            }
        }

    return matrizStrings;
}



//Fun��o respons�vel por encontrar a maior subsequencia comum entre duas outras sequ�ncias
/*Al�m de retornar a maior subsequ�ncia, a fun��o reorganiza a matriz de strings passada como par�metro
de forma a representar, pelas suas posi��es,as solu��es de todos os subproblemas*/

char* LCS (char*** matrizStrings, int tamanhoSequencia1, int tamanhoSequencia2) {

    for(int i = 1; i < tamanhoSequencia1 + 2; i++) {
        for(int j = 1; j < tamanhoSequencia2 + 2; j++) {
            if(i == 1 || j == 1) {

                strcpy(matrizStrings[i][j], "");
            }
            else if(strcmp(matrizStrings[i][0],matrizStrings[0][j]) == 0){

                strcpy(matrizStrings[i][j],matrizStrings[i-1][j-1]);
                strcat(matrizStrings[i][j],matrizStrings[i][0]);
            }
            else if(strcmp(matrizStrings[i][0],matrizStrings[0][j]) != 0){

                if(strlen(matrizStrings[i][j-1])>=strlen(matrizStrings[i-1][j])){

                    strcpy(matrizStrings[i][j],matrizStrings[i][j-1]);
                }
                else{

                    strcpy(matrizStrings[i][j],matrizStrings[i-1][j]);
                }
            }
        }
    }
    return(matrizStrings[tamanhoSequencia1+1][tamanhoSequencia2 + 1]);
}

void main(void){
    clock_t tempoInicial, tempoFinal;

    setlocale(LC_ALL, "Portuguese");

    //Parte de entrada de dados

    int tamanhoSequencia1, tamanhoSequencia2;
    char* StringDeEntrada;

    StringDeEntrada = malloc(maiorTamanhoDeSequencia * sizeof(char));

    printf("Digite a primeira sequ�ncia de letras: ");
    scanf("%s", StringDeEntrada);
    char sequencia1[strlen(StringDeEntrada) + 1];
    strcpy(sequencia1,StringDeEntrada);

    printf("\nDigite a segunda sequ�ncia de letras: ");

    scanf("%s",StringDeEntrada);

    char sequencia2[strlen(StringDeEntrada) + 1];
    strcpy(sequencia2,StringDeEntrada);

    free(StringDeEntrada);

    tamanhoSequencia1 = strlen(sequencia1);
    tamanhoSequencia2 = strlen(sequencia2);

    //Cria��o da matriz.
    char* maiorSubSeq;
    char*** matriz;

    tempoInicial = clock();

    matriz = criaMatrizStrings(sequencia1, sequencia2, tamanhoSequencia1, tamanhoSequencia2);

    //Aplica��o da LCS na matriz criada. A maior subsequ�ncia � representada pelo �ltimo item da matriz
    maiorSubSeq = LCS(matriz, tamanhoSequencia1, tamanhoSequencia2);

    tempoFinal = clock();

    double tempoDeExecucao = (tempoFinal - tempoInicial)*1000 / CLOCKS_PER_SEC;

    printf("\nMaior subsequ�ncia comum(LCS): %s\n\nTamanho da LCS: %i\n\nTempo de execu��o: %lf", maiorSubSeq, strlen(matriz[tamanhoSequencia1+1][tamanhoSequencia2+1]), tempoDeExecucao);
}
