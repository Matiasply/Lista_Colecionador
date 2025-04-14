#include <stdio.h>
#include <stdlib.h>
#include "colecao.h"

int main(){

    int escolha, identif;
    Colecao dados;

    printf("Bem-vindo!");
    printf("\n\nEsse programa tem como objetivo cadastrar e consultar itens de uma colecao.\n\n");
    printf("A seguir, ");
    do{
    printf("Escolha uma das opcoes:\n\n");
    printf("\n1. Cadastrar item.");
    printf("\n2. Consultar item.");
    printf("\n5. Listar Acervo.");
    printf("\n0. Sair.");
    printf("\nO que deseja fazer? ");
    scanf("%d", &escolha);

    if(escolha == 1){
        system("cls||clear");
        dados = cadastrar_item();
        gerar_arquivo(dados);
    }
    if (escolha == 2){
        system("cls||clear");
        printf("Digite o identificador do item: ");
        scanf("%d", &identif);

        consultar_item("colecao.txt", identif);
    }
    if (escolha == 5){
        system("cls||clear");
        listar_acervo("colecao.txt");
    }
}while(escolha != 0);
    
}