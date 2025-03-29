#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 4  

typedef struct {
    double dados[MAX];
    int topo;
} Pilha;

Pilha* criar_pilha() {
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    p->topo = -1;
    return p;
}

int vazia(Pilha* p) {
    return p->topo == -1;
}

int cheia(Pilha* p) {
    return p->topo == MAX - 1;
}

void push(Pilha* p, double dado) {
    if (cheia(p)) {
       
        for (int i = 0; i < MAX - 1; i++) {
            p->dados[i] = p->dados[i + 1];
        }
        p->dados[MAX - 1] = dado;
    } else {
        p->dados[++p->topo] = dado;
    }
}

double pop(Pilha* p) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia! Expressão inválida.\n");
        exit(EXIT_FAILURE);
    }
    return p->dados[p->topo--];
}

double top(Pilha* p) {
    if (vazia(p)) {
        printf("Erro: Pilha vazia!\n");
        exit(EXIT_FAILURE);
    }
    return p->dados[p->topo];
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
    char* token = strtok(expressao, " ");
    char temp[200] = "";

    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            push(p, atof(token));
            strcat(temp, token);
            strcat(temp, " ");
        } else {
            if (p->topo < 1) {
                printf("Erro: Expressão RPN inválida!\n");
                free(p);
                exit(EXIT_FAILURE);
            }
            double b = pop(p);
            double a = pop(p);
            double resultado;
            char operador[2] = {token[0], '\0'};
            char tempFormula[100];

            switch (token[0]) {
                case '+': resultado = a + b; break;
                case '-': resultado = a - b; break;
                case '*': resultado = a * b; break;
                case '/': 
                    if (b == 0) {
                        printf("Erro: Divisão por zero!\n");
                        free(p);
                        exit(EXIT_FAILURE);
                    }
                    resultado = a / b; 
                    break;
                default: 
                    printf("Erro: Operador inválido!\n");
                    free(p);
                    exit(EXIT_FAILURE);
            }
            sprintf(tempFormula, "(%g %s %g)", a, operador, b);
            push(p, resultado);
            strcat(temp, tempFormula);
            strcat(temp, " ");
        }
        token = strtok(NULL, " ");
    }

    if (p->topo != 0) {
        printf("Erro: Expressão RPN mal formada!\n");
        free(p);
        exit(EXIT_FAILURE);
    }

    double resultadoFinal = pop(p);
    strcpy(formula, temp);
    free(p);
    return resultadoFinal;
}

int main() {
    char expressao[100];
    char expressao_copia[100];
    char formula[200];

    printf("Digite a expressão RPN: ");
    fgets(expressao, 100, stdin);
    expressao[strcspn(expressao, "\n")] = 0;

    strcpy(expressao_copia, expressao);

    if (!validar_RPN(expressao_copia)) {
        printf("Erro: Expressão RPN inválida!\n");
        return EXIT_FAILURE;
    }

    double resultado = calcular_RPN(expressao, formula);
    printf("Expressão algébrica: %s\n", formula);
    printf("Resultado: %.2f\n", resultado);
    
    return 0;
}
