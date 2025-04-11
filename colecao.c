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

