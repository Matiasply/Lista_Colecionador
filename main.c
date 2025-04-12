#include <stdio.h>
#include "colecao.h"

int main(){

    int escolha, identif;
    Colecao dados;

    do{
    printf("Bem-vindo!");
    printf("\n1. Cadastrar item.");
    printf("\n2. Consultar item.");
    printf("\n0. Sair.");
    printf("\nO que deseja fazer? ");
    scanf("%d", &escolha);

    if(escolha == 1){
        dados = cadastrar_item();
        gerar_arquivo(dados);
    }
    if (escolha == 2){
        printf("Digite o identificador do item: ");
        scanf("%d", &identif);

        consultar_item("colecao.txt", identif);
    }
}while(escolha != 0);
    
}