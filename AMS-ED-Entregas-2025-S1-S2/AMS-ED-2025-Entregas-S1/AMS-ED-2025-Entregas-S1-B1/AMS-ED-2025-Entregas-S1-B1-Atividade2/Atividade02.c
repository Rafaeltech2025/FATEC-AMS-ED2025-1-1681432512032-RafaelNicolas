/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-2                                 */
/*             Objetivo: <<  Manipulacao de Array com ponteiro  >>                  */
/*                                                                                  */
/*                                  Autor: Rafael Nicolas Campos                    */
/*                                                                   Data:06/03/2024*/
/*----------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATOS 50
#define MAX_NOTAS_PE 4
#define MAX_NOTAS_AC 5
#define MAX_NOTAS_PP 10
#define MAX_NOTAS_EB 3

typedef struct Candidato {
    char* nome;
    float* pe;
    float* ac;
    float* pp;
    float* eb;
    float nf;
    struct Candidato* proximo;
} Candidato;

float calcularMedia(float* notas, int tamanho) {
    float soma = 0, maior = notas[0], menor = notas[0];

    for (int i = 0; i < tamanho; i++) {
        if (notas[i] > maior) maior = notas[i];
        if (notas[i] < menor) menor = notas[i];
        soma += notas[i];
    }
    soma -= (maior + menor);
    return soma / (tamanho - 2);
}

void calcularNotaFinal(Candidato* candidato) {
    float media_pe = calcularMedia(candidato->pe, MAX_NOTAS_PE);
    float media_ac = calcularMedia(candidato->ac, MAX_NOTAS_AC);
    float media_pp = calcularMedia(candidato->pp, MAX_NOTAS_PP);
    float media_eb = calcularMedia(candidato->eb, MAX_NOTAS_EB);

    candidato->nf = (media_pe * 0.3f) + (media_ac * 0.1f) + (media_pp * 0.4f) + (media_eb * 0.2f);
}

void incluirCandidato(Candidato** comeco, char* nome, float* pe, float* ac, float* pp, float* eb) {
    Candidato* novoCandidato = (Candidato*)malloc(sizeof(Candidato));
    if (novoCandidato == NULL) {
        printf("Erro ao alocar memória para o candidato.\n");
        return;
    }

    novoCandidato->nome = (char*)malloc(strlen(nome) + 1);
    if (novoCandidato->nome == NULL) {
        printf("Erro ao alocar memória para o nome.\n");
        free(novoCandidato);
        return;
    }
    strcpy(novoCandidato->nome, nome);

    novoCandidato->pe = (float*)malloc(MAX_NOTAS_PE * sizeof(float));
    novoCandidato->ac = (float*)malloc(MAX_NOTAS_AC * sizeof(float));
    novoCandidato->pp = (float*)malloc(MAX_NOTAS_PP * sizeof(float));
    novoCandidato->eb = (float*)malloc(MAX_NOTAS_EB * sizeof(float));

    if (novoCandidato->pe == NULL || novoCandidato->ac == NULL || novoCandidato->pp == NULL || novoCandidato->eb == NULL) {
        printf("Erro ao alocar memória para as notas.\n");
        free(novoCandidato->nome);
        free(novoCandidato);
        return;
    }

    memcpy(novoCandidato->pe, pe, MAX_NOTAS_PE * sizeof(float));
    memcpy(novoCandidato->ac, ac, MAX_NOTAS_AC * sizeof(float));
    memcpy(novoCandidato->pp, pp, MAX_NOTAS_PP * sizeof(float));
    memcpy(novoCandidato->eb, eb, MAX_NOTAS_EB * sizeof(float));

    calcularNotaFinal(novoCandidato);

    novoCandidato->proximo = *comeco;
    *comeco = novoCandidato;
}

void classificarCandidatos(Candidato** comeco) {
    Candidato *i, *j;
    float tempNF;
    char* tempNome = (char*)malloc(100 * sizeof(char));

    for (i = *comeco; i != NULL; i = i->proximo) {
        for (j = i->proximo; j != NULL; j = j->proximo) {
            if (i->nf < j->nf) {
                tempNF = i->nf;
                i->nf = j->nf;
                j->nf = tempNF;

                strcpy(tempNome, i->nome);
                strcpy(i->nome, j->nome);
                strcpy(j->nome, tempNome);
            }
        }
    }

    free(tempNome);
}

void imprimirClassificacao(Candidato* comeco) {
    Candidato* ptr = comeco;
    printf("Classificação dos 5 melhores candidatos: \n");

    for (int i = 0; i < 5 && ptr != NULL; i++) {
        printf("%d- %s: Nota Final: %.2f \n", i + 1, ptr->nome, ptr->nf);
        ptr = ptr->proximo;
    }
}

void liberarMemoria(Candidato* comeco) {
    Candidato* ptr = comeco;
    while (ptr != NULL) {
        Candidato* temp = ptr;
        ptr = ptr->proximo;
        free(temp->nome);
        free(temp->pe);
        free(temp->ac);
        free(temp->pp);
        free(temp->eb);
        free(temp);
    }
}

int lerNota(char tipo[], int indice) {
    float nota;
    while (1) {
        printf("%s %d: ", tipo, indice + 1);
        if (scanf("%f", &nota) != 1 || nota < 0 || nota > 10) {
            printf("Nota inválida. Digite um número entre 0 e 10.\n");
            while(getchar() != '\n');
        } else {
            return nota;
        }
    }
}

int main(void) {
    Candidato* comeco = NULL;
    int numero_candidatos = 0;
    char prosseguir = 'S';

    while (prosseguir == 'S' || prosseguir == 's') {
        char nome[100];
        float pe[MAX_NOTAS_PE], ac[MAX_NOTAS_AC], pp[MAX_NOTAS_PP], eb[MAX_NOTAS_EB];

        printf("Candidatos cadastrados: %d\n", numero_candidatos);
        printf("Digite o nome do candidato: ");
        scanf(" %[^\n]", nome);

        printf("Digite as %d notas da Prova Escrita (PE):\n", MAX_NOTAS_PE);
        for (int i = 0; i < MAX_NOTAS_PE; i++) {
            pe[i] = lerNota("Nota PE", i);
        }

        printf("Digite as %d notas da Análise Curricular (AC):\n", MAX_NOTAS_AC);
        for (int i = 0; i < MAX_NOTAS_AC; i++) {
            ac[i] = lerNota("Nota AC", i);
        }

        printf("Digite as %d notas da Prova Prática (PP):\n", MAX_NOTAS_PP);
        for (int i = 0; i < MAX_NOTAS_PP; i++) {
            pp[i] = lerNota("Nota PP", i);
        }

        printf("Digite as %d notas da Entrevista em Banca (EB):\n", MAX_NOTAS_EB);
        for (int i = 0; i < MAX_NOTAS_EB; i++) {
            eb[i] = lerNota("Nota EB", i);
        }

        incluirCandidato(&comeco, nome, pe, ac, pp, eb);
        numero_candidatos++;

        if (numero_candidatos >= MAX_CANDIDATOS) {
            printf("Você atingiu o limite máximo de candidatos (50).\n");
            break;
        }

        printf("\nGostaria de cadastrar outro candidato? (S para SIM, N para NÃO): ");
        scanf(" %c", &prosseguir);
    }

    classificarCandidatos(&comeco);
    imprimirClassificacao(comeco);

    liberarMemoria(comeco);

    return 0;
}
