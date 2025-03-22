#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pedido {
    int numero_pedido;
    char nome_cliente[100];
    char descricao_prato[100];
    int quantidade;
    char status[20];
    struct Pedido *proximo;
} Pedido;

Pedido* inicializar_lista() {
    return NULL;
}

Pedido* buscar_pedido(Pedido* lista, int numero_pedido) {
    Pedido* atual = lista;
    while (atual != NULL) {
        if (atual->numero_pedido == numero_pedido) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void inserir_pedido(Pedido** lista, int numero_pedido, const char* nome_cliente, const char* descricao_prato, int quantidade, const char* status) {
    if (buscar_pedido(*lista, numero_pedido)) {
        printf("Erro: Pedido %d já existe na lista.\n", numero_pedido);
        return;
    }
    
    Pedido* novo_pedido = (Pedido*)malloc(sizeof(Pedido));
    if (novo_pedido == NULL) {
        printf("Erro de alocação de memória.\n");
        exit(1);
    }
    novo_pedido->numero_pedido = numero_pedido;
    strncpy(novo_pedido->nome_cliente, nome_cliente, 99);
    strncpy(novo_pedido->descricao_prato, descricao_prato, 99);
    novo_pedido->quantidade = quantidade;
    strncpy(novo_pedido->status, status, 19);
    novo_pedido->proximo = *lista;
    *lista = novo_pedido;
    printf("Pedido %d inserido com sucesso!\n", numero_pedido);
}

void atualizar_status(Pedido* lista, int numero_pedido, const char* novo_status) {
    Pedido* pedido = buscar_pedido(lista, numero_pedido);
    if (pedido) {
        strncpy(pedido->status, novo_status, 19);
        printf("Status do pedido %d atualizado para '%s'.\n", numero_pedido, novo_status);
    } else {
        printf("Pedido não encontrado.\n");
    }
}

void deletar_pedido(Pedido** lista, int numero_pedido) {
    Pedido* atual = *lista;
    Pedido* anterior = NULL;
    
    while (atual != NULL && atual->numero_pedido != numero_pedido) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Pedido não encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        *lista = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    
    free(atual);
    printf("Pedido %d deletado com sucesso.\n", numero_pedido);
}

void liberar_lista(Pedido** lista) {
    Pedido* atual = *lista;
    while (atual != NULL) {
        Pedido* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    *lista = NULL;
    printf("Memória liberada.\n");
}

void exibir_pedidos(Pedido* lista) {
    if (!lista) {
        printf("Nenhum pedido registrado.\n");
        return;
    }
    Pedido* atual = lista;
    while (atual != NULL) {
        printf("Pedido %d:\n", atual->numero_pedido);
        printf("Cliente: %s\n", atual->nome_cliente);
        printf("Prato: %s\n", atual->descricao_prato);
        printf("Quantidade: %d\n", atual->quantidade);
        printf("Status: %s\n\n", atual->status);
        atual = atual->proximo;
    }
}

int main() {
    Pedido* lista = inicializar_lista();
    int opcao, numero_pedido, quantidade;
    char nome_cliente[100], descricao_prato[100], status[20];
    
    do {
        printf("\nSistema de Gerenciamento de Pedidos\n");
        printf("1. Inserir Pedido\n");
        printf("2. Exibir Pedidos\n");
        printf("3. Buscar Pedido\n");
        printf("4. Atualizar Status\n");
        printf("5. Deletar Pedido\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();
        
        switch(opcao) {
            case 1:
                printf("Número do pedido: ");
                scanf("%d", &numero_pedido);
                getchar();
                printf("Nome do cliente: ");
                fgets(nome_cliente, 100, stdin);
                nome_cliente[strcspn(nome_cliente, "\n")] = '\0';
                printf("Descrição do prato: ");
                fgets(descricao_prato, 100, stdin);
                descricao_prato[strcspn(descricao_prato, "\n")] = '\0';
                printf("Quantidade: ");
                scanf("%d", &quantidade);
                getchar();
                printf("Status do pedido: ");
                fgets(status, 20, stdin);
                status[strcspn(status, "\n")] = '\0';
                inserir_pedido(&lista, numero_pedido, nome_cliente, descricao_prato, quantidade, status);
                break;
            case 2:
                exibir_pedidos(lista);
                break;
            case 3:
                printf("Número do pedido para buscar: ");
                scanf("%d", &numero_pedido);
                Pedido* pedido_encontrado = buscar_pedido(lista, numero_pedido);
                if (pedido_encontrado) {
                    printf("Pedido encontrado: %d\n", pedido_encontrado->numero_pedido);
                } else {
                    printf("Pedido não encontrado.\n");
                }
                break;
            case 4:
                printf("Número do pedido para atualizar status: ");
                scanf("%d", &numero_pedido);
                getchar();
                printf("Novo status: ");
                fgets(status, 20, stdin);
                status[strcspn(status, "\n")] = '\0';
                atualizar_status(lista, numero_pedido, status);
                break;
            case 5:
                printf("Número do pedido para deletar: ");
                scanf("%d", &numero_pedido);
                deletar_pedido(&lista, numero_pedido);
                break;
            case 6:
                liberar_lista(&lista);
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 6);
    
    return 0;
}