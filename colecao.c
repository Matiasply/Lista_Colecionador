#include <stdio.h>
#include "colecao.h"

Colecao cadastrar_item(){
    Colecao item;

    printf("Digite o identificador do item: ");
    scanf("%d", &item.identificador);

    printf("\nDigite a descricao: ");
    fgets(item.descricao, 50, stdin);

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

