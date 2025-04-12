typedef struct{
    char descricao[50];
    int identificador;
    int quantidade;
} Colecao;

Colecao cadastrar_item();
void limpar_buffer();
void gerar_arquivo(Colecao dados);
void consultar_item(char *str, int identificador);

