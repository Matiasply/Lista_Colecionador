#include <stdio.h>
#include "colecao.h"

int main(){

    int escolha;
    Colecao dados;

    printf("Bem-vindo!");
    printf("\nO que deseja fazer?");
    printf("\n1. Cadastrar item");
    scanf("%d", &escolha);

    if(escolha == 1){
        dados = cadastrar_item();
        gerar_arquivo(dados);
    }
}