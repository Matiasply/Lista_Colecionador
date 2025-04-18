#include <stdio.h>
#include <stdlib.h>
#include "colecao.h"

int main(){

    int escolha, identif,cont = 0, *quantidade = &cont;
    Colecao dados;

    printf("Bem-vindo!");
    printf("\n\nEsse programa tem como objetivo cadastrar e consultar itens de uma colecao.\n\n");
    printf("A seguir, ");
    do{
    printf("Escolha uma das opcoes:\n\n");
    printf("\n1. Cadastrar item.");
    printf("\n2. Consultar item.");
    printf("\n3. Remover item.");
    printf("\n4. Alterar item.");
    printf("\n5. Listar Acervo.");
    printf("\n0. Sair.");
    printf("\nO que deseja fazer? ");
    scanf("%d", &escolha);

    switch(escolha){
        case 1:
            system("cls||clear");
            dados = cadastrar_item(quantidade);
            gerar_arquivo(dados);
            break;
        case 2:
            system("cls||clear");
            printf("Digite o identificador do item: ");
            scanf("%d", &identif);
            consultar_item("colecao.txt", identif);
            printf("\n\n");
            break;
        case 3:
            system("cls||clear");
            printf("Digite o identificador do item: ");
            scanf("%d", &identif);
            remover_item("colecao.txt", identif, quantidade);
            break;
        case 4:
            system("cls||clear");
            printf("Digite o identificador do item: ");
            scanf("%d", &identif);
            alterar_item("colecao.txt", identif);
            break;
        case 5:
            system("cls||clear");
            listar_acervo("colecao.txt");
            break;
        default:
            printf("\nOpcao invalida! Tente novamente.\n\n");
    }
    }while(escolha != 0);
   
}