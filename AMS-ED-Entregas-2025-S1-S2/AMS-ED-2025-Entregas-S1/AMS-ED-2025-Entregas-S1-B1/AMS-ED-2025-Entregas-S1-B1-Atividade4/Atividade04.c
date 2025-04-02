
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    /
/                         Id da Atividade: S1-B1-4                                 /
/             Objetivo: <<  Manipulação de Pilha - Implementado HP12c  >>          /
/                                                                                  /
/                                  Autor: Rafael Nicolas Campos                    /
/                                                                   Data:01/04/2025/
/----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 4  

typedef struct {
    double dados[MAX];
    int topo;
} Pilha;

typedef struct {
    char dados[MAX][100]; 
    int topo;
} PilhaStr;

Pilha* criar_pilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = -1;
    return p;
}

PilhaStr* criar_pilha_str() {
    PilhaStr* p = (PilhaStr*)malloc(sizeof(PilhaStr));
    p->topo = -1;
    return p;
}

int vazia(Pilha* p) {
    return p->topo == -1;
}

void push(Pilha* p, double dado) {
    p->dados[++p->topo] = dado;
}

double pop(Pilha* p) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia! Expressão inválida.\n");
        exit(EXIT_FAILURE);
    }
    return p->dados[p->topo--];
}

void push_str(PilhaStr* p, char* dado) {
    strcpy(p->dados[++p->topo], dado);
}

char* pop_str(PilhaStr* p) {
    if (vazia((Pilha*)p)) {
        printf("Erro: Pilha de strings vazia!\n");
        exit(EXIT_FAILURE);
    }
    return p->dados[p->topo--];
}

int validar_RPN(char* expressao) {
    int operandos = 0, operadores = 0;
    char* token = strtok(expressao, " ");
    
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            operandos++;
        } else if (strchr("+-*/", token[0]) && strlen(token) == 1) {
            operadores++;
        } else {
            return 0;
        }
        token = strtok(NULL, " ");
    }
    return operandos == operadores + 1;
}

double calcular_RPN(char* expressao, char* formula) {
    Pilha* p = criar_pilha();
    PilhaStr* ps = criar_pilha_str();
    char* token = strtok(expressao, " ");

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(p, atof(token));
            push_str(ps, token);
        } else {
            if (p->topo < 1) {
                printf("Erro: Expressão RPN inválida!\n");
                free(p);
                free(ps);
                exit(EXIT_FAILURE);
            }
            
            double b = pop(p);
            double a = pop(p);
            double resultado;
            char operador[2] = {token[0], '\0'};
            char expr[100];

            char* str_b = pop_str(ps);
            char* str_a = pop_str(ps);

            switch (token[0]) {
                case '+': resultado = a + b; break;
                case '-': resultado = a - b; break;
                case '*': resultado = a * b; break;
                case '/': 
                    if (b == 0) {
                        printf("Erro: Divisão por zero!\n");
                        free(p);
                        free(ps);
                        exit(EXIT_FAILURE);
                    }
                    resultado = a / b; 
                    break;
                default: 
                    printf("Erro: Operador inválido!\n");
                    free(p);
                    free(ps);
                    exit(EXIT_FAILURE);
            }

            sprintf(expr, "(%s %s %s)", str_a, operador, str_b);
            push(p, resultado);
            push_str(ps, expr);
        }
        token = strtok(NULL, " ");
    }

    if (p->topo != 0) {
        printf("Erro: Expressão RPN mal formada!\n");
        free(p);
        free(ps);
        exit(EXIT_FAILURE);
    }

    double resultadoFinal = pop(p);
    strcpy(formula, pop_str(ps));

    free(p);
    free(ps);
    return resultadoFinal;
}

int main() {
    char expressao[100];
    char expressao_copia[100];
    char formula[200];

    while (1) {  
        printf("\nDigite a expressão RPN (ou 'sair' para encerrar): ");
        fgets(expressao, 100, stdin);
        expressao[strcspn(expressao, "\n")] = 0;

        if (strcmp(expressao, "sair") == 0) {
            printf("Encerrando o programa...\n");
            break;  
        }

        strcpy(expressao_copia, expressao);

        if (!validar_RPN(expressao_copia)) {
            printf("Erro: Expressão RPN inválida! Tente novamente.\n");
            continue;
        }

        double resultado = calcular_RPN(expressao, formula);
        printf("Expressão algébrica: %s\n", formula);
        printf("Resultado: %.2f\n", resultado);
    }

    return 0;
}
