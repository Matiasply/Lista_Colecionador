#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "colecao.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Lê todos os caracteres até encontrar \n ou EOF
}

Colecao cadastrar_item(int *quantidade_itens){
    Colecao item;
    int aux = 0;

    printf("Digite o identificador do item: ");
    scanf("%d", &item.identificador);
    
    printf("\nDigite a descricao: ");
    limpar_buffer(); // Limpa o buffer antes de ler a string
    fgets(item.descricao, 50, stdin);
    // Remover o '\n' caso ele tenha sido lido
    item.descricao[strcspn(item.descricao, "\n")] = '\0';
    
    printf("\nDigite a quantidade: ");
    scanf("%d", &item.quantidade);
    
    aux++; // Conta quantos itens são cadastrados
    *quantidade_itens += aux;
    
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

void consultar_item(char *nome_arquivo, int identificador) {
    Colecao item; // Alterado para uma variável local, em vez de um ponteiro
    char *token, linha[60];
    int encontrado = 0; // Flag para verificar se o item foi encontrado

    FILE *dados = fopen(nome_arquivo, "r");

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

void listar_acervo(char *nome_arquivo) {

    Colecao item; 
    char *token, linha[60];
    

    FILE *dados = fopen(nome_arquivo, "r");

    if (dados == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (fgets(linha, sizeof(linha), dados)) {
        token = strtok(linha, ";");
        while (token != NULL) { 
                item.identificador = atoi(token);
                token = strtok(NULL, ";");
                strncpy(item.descricao, token, sizeof(item.descricao) - 1);
                item.descricao[sizeof(item.descricao) - 1] = '\0'; // Garantir terminação da string
                token = strtok(NULL, ";");
                item.quantidade = atoi(token);
                break; // Sair do loop interno
        }
        printf("Identificador: %d\n", item.identificador);
        printf("Descricao: %s\n", item.descricao);
        printf("Quantidade: %d\n", item.quantidade);
        printf("\n\n");
    }

    fclose(dados); // Fechar o arquivo após a leitura
    
}

void remover_item(char *nome_arquivo, int identificador, int *quantidade_itens) {
    Colecao itens[*quantidade_itens];
    char *token, linha[60];
    int j = 0, i;
    int encontrado = 0; // Flag para verificar se o item foi encontrado

    FILE *dados = fopen(nome_arquivo, "r");
    if (dados == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Lê o arquivo e armazena os itens que não serão removidos
    while (fgets(linha, sizeof(linha), dados)) {
        token = strtok(linha, ";");
        if (token != NULL && atoi(token) == identificador) {
            encontrado = 1; // Item encontrado para remoção
            // Ignora o item a ser removido
            continue;
        }

        // Preenche os dados do item no array
        itens[j].identificador = atoi(token);
        token = strtok(NULL, ";");
        strncpy(itens[j].descricao, token, sizeof(itens[j].descricao) - 1);
        itens[j].descricao[sizeof(itens[j].descricao) - 1] = '\0'; // Garantir terminação da string
        token = strtok(NULL, ";");
        itens[j].quantidade = atoi(token);
        j++; // Incrementa o índice do array
    }

    fclose(dados); // Fecha o arquivo original

    // Atualiza a quantidade de itens
    *quantidade_itens = j;

    // Reescreve o arquivo com os itens restantes
    FILE *novo_arquivo = fopen(nome_arquivo, "w");
    if (novo_arquivo == NULL) {
        printf("Erro ao criar o arquivo.\n");
        return;
    }

    for (i = 0; i < j; i++) {
        fprintf(novo_arquivo, "%d;%s;%d\n", itens[i].identificador, itens[i].descricao, itens[i].quantidade);
    }

    fclose(novo_arquivo); // Fecha o arquivo atualizado
    if (!encontrado) {
        printf("Item inexistente!\n");
        return;
    } else {
        printf("Item removido com sucesso!\n");
    }
}

