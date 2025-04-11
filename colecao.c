#include <stdio.h>
#include <string.h>
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
    
    fprintf(arquivo, "Identificador: %d\nDescricao: %s\nQuantidade: %d,", dados.identificador, dados.descricao, dados.quantidade);
    
    fclose(arquivo);
}

