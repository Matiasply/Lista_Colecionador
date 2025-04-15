typedef struct{
    char descricao[50];
    int identificador;
    int quantidade;
} Colecao;

Colecao cadastrar_item(int *quantidade_itens);
void limpar_buffer();
void gerar_arquivo(Colecao dados);
void consultar_item(char *nome_arquivo, int identificador);
void remover_item(char *nome_arquivo, int identificador, int *quantidade_itens);
void listar_acervo(char *nome_arquivo);

