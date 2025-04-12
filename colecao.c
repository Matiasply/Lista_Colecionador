#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "colecao.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Lê todos os caracteres até encontrar \n ou EOF
}

Colecao cadastrar_item(){
    Colecao item;

    printf("Digite o identificador do item: ");
    scanf("%d", &item.identificador);

    printf("\nDigite a descricao: ");
    limpar_buffer(); // Limpa o buffer antes de ler a string
    fgets(item.descricao, 50, stdin);
    // Remover o '\n' caso ele tenha sido lido
    item.descricao[strcspn(item.descricao, "\n")] = '\0';

    printf("\nDigite a quantidade: ");
    scanf("%d", &item.quantidade);

    return item;
}

void gerar_arquivo(Colecao dados){
    FILE *arquivo = fopen("colecao.txt", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    
    fprintf(arquivo, "%d;%s;%d\n", dados.identificador, dados.descricao, dados.quantidade);
    
    fclose(arquivo);
}

void consultar_item(char *str, int identificador) {
    Colecao item; // Alterado para uma variável local, em vez de um ponteiro
    char *token, linha[60];
    int encontrado = 0; // Flag para verificar se o item foi encontrado

    FILE *dados = fopen(str, "r");

    if (dados == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), dados)) {
        token = strtok(linha, ";");
        while (token != NULL) {
            if (atoi(token) == identificador) {
                item.identificador = atoi(token);
                token = strtok(NULL, ";");
                strncpy(item.descricao, token, sizeof(item.descricao) - 1);
                item.descricao[sizeof(item.descricao) - 1] = '\0'; // Garantir terminação da string
                token = strtok(NULL, ";");
                item.quantidade = atoi(token);
                encontrado = 1; // Item encontrado
                break; // Sair do loop interno
            }
            token = strtok(NULL, ";");
        }
        if (encontrado) break; // Sair do loop externo
    }

    fclose(dados); // Fechar o arquivo após a leitura

    if (!encontrado) {
        printf("Item inexistente!\n");
    } else {
        printf("Identificador: %d\n", item.identificador);
        printf("Descricao: %s\n", item.descricao);
        printf("Quantidade: %d\n", item.quantidade);
    }
}