typedef struct{
    char descricao[50];
    int identificador;
    int quantidade;
} Colecao;

Colecao cadastrar_item();
void limpar_buffer();
void gerar_arquivo(Colecao dados);
void consultar_item(char *nome_arquivo, int identificador);
Colecao remover_item(char *nome_arquivo, int identificador);
void listar_acervo(char *nome_arquivo);

