typedef struct{
    char descricao[50];
    int identificador;
    int quantidade;
} Colecao;

Colecao cadastrar_item();
void gerar_arquivo(Colecao dados);

