#include <stdio.h>
/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B2-2                                */
/*             Objetivo: << Bublle Sort >>                                          */
/*                                                                                  */
/*                                  Autor: Rafael Nicolas Campos                    */
/*                                                                  Data:06/05/2025 */
/*----------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    float *vetor;
    int i = 0, j;
    float entrada, temp;
    char buffer[100];
    char extra;
    char resposta;

    vetor = (float*) malloc(5 * sizeof(float));  // Aloca espaço para até 5 números
    if (vetor == NULL) {
        printf("Erro na alocação de memória!\n");
        return 1;
    }

    do {
        printf("Digite o número %d: ", i + 1);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Erro ao ler entrada.\n");
            continue;
        }

  
        if (sscanf(buffer, "%f %c", &entrada, &extra) != 1) {
            printf("Entrada inválida! Por favor, digite um número válido.\n");
            continue;
        }

        vetor[i] = entrada;
        i++;

        if (i >= 5) {
            printf("Limite de 5 números atingido.\n");
            break;
        }

        printf("Deseja digitar outro número? (s/n): ");
        resposta = getchar();

        // Limpa o buffer depois de pegar a resposta
        while (getchar() != '\n');

    } while (resposta == 's' || resposta == 'S');

 
    for (int x = 0; x < i - 1; x++) {
        for (j = 0; j < i - 1 - x; j++) {
            if (vetor[j] > vetor[j + 1]) {
                temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }

    printf("Array ordenado em ordem ascendente:\n");
    for (j = 0; j < i; j++) {
        printf("%.2f ", vetor[j]);
    }
    printf("\n");

    free(vetor);
    return 0;
}