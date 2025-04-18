#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "colecao.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Lê todos os caracteres até encontrar \n ou EOF
}

void recalcular_quantidade_itens(char *nome_arquivo, int *quantidade_itens) {
    FILE *dados = fopen(nome_arquivo, "r");
    if (dados == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        *quantidade_itens = 0; // Se o arquivo não puder ser aberto, não há itens
        return;
    }

    char linha[60];
    int contador = 0;

    // Conta o número de linhas no arquivo
    while (fgets(linha, sizeof(linha), dados)) {
        contador++;
    }

    fclose(dados);

    *quantidade_itens = contador; // Atualiza o valor de quantidade_itens
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

void remover_item(char *nome_arquivo, int identificador, int *quantidade_itens) {
    Colecao itens[*quantidade_itens - 1];
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

void alterar_item(char *nome_arquivo, int identificador, int *quantidade_itens) {
    Colecao itens[*quantidade_itens]; 
    int j = 0;
    char *token, linha[60];
    
    FILE *dados = fopen(nome_arquivo, "r");
    if (dados == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    
    Colecao item;
    int encontrado = 0;

    while (fgets(linha, sizeof(linha), dados)) {
        token = strtok(linha, ";");
        itens[j].identificador = atoi(token);
        token = strtok(NULL, ";");
        strncpy(itens[j].descricao, token, sizeof(itens[j].descricao) - 1);
        itens[j].descricao[sizeof(itens[j].descricao) - 1] = '\0';
        token = strtok(NULL, ";");
        itens[j].quantidade = atoi(token);

        if (itens[j].identificador == identificador) {
            encontrado = 1;
            item = itens[j];
        }
        j++;
    }
    fclose(dados);

    if (!encontrado) {
        printf("Item inexistente!\n");
        return;
    }

    // Modificar o item
    int escolha;
    printf("O que deseja modificar?\n(1) Descricao\n(2) Quantidade\nEscolha: ");
    scanf("%d", &escolha);
    switch (escolha) {
        case 1:
            printf("Digite a nova descricao: ");
            limpar_buffer();
            fgets(item.descricao, sizeof(item.descricao), stdin);
            item.descricao[strcspn(item.descricao, "\n")] = '\0'; // Finaliza a string
            break;
        case 2:
            printf("Digite a nova quantidade: ");
            scanf("%d", &item.quantidade);
            break;
        default:
            printf("Opcao invalida!\n");
            return;
    }

    // Atualizar o item na lista
    for (int i = 0; i < j; i++) {
        if (itens[i].identificador == identificador) {
            itens[i] = item;
            break;
        }
    }

    // Reescrever o arquivo
    dados = fopen(nome_arquivo, "w");
    if (dados == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < j; i++) {
        fprintf(dados, "%d;%s;%d\n", itens[i].identificador, itens[i].descricao, itens[i].quantidade);
    }
    fclose(dados);

    printf("Item alterado com sucesso!\n\n");
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