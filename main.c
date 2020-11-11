#include <stdio.h>

struct Movimentacao {
  double valor;
  char descricao[100];
  char data[100];
};

void gravarArquivo(struct Movimentacao m) {
  FILE *fr = fopen("movimentacoes.txt", "a");
  fprintf(fr, "%lf\n", m.valor);
  fprintf(fr, "%s\n", m.descricao);
  fprintf(fr, "%s\n", m.data);
  fclose(fr);
}

void cadastrar() {
  struct Movimentacao nova;
  printf("\nCadastrar receita/gasto\n");
  printf("Valor: R$ ");
  scanf("%lf", &nova.valor);
  printf("Descricao: ");
  scanf(" %[^\n]s", nova.descricao);
  printf("Data (dd/mm/aa): ");
  scanf("%s", nova.data);
  gravarArquivo(nova);
  printf("\nMovimentacao cadastrada com sucesso!\n");
}

void visualizarCategorias() {
  printf("\nVisualizar categorias\n");
}

void gerarRelatorio() {
  FILE *fr = fopen("relatorio.html", "w");
  fprintf(fr, "<html lang=\"br\">\n<head>\n<meta charset=\"UTF-8\">\n<title>Relatório de movimentações</title>\n</head>\n<body>\n<h1>Relatório</h1>\n</body>\n</html>");
  fclose(fr);
  printf("\nRelatorio criado com sucesso!\n");
}

void sair() {
  printf("\nObrigado por usar o programa. Ate logo!\n");
}

void menu() {
  int i = -1, op = -1;
  while (i == -1) {
    printf("Gerenciador financeiro:\n");
    printf("1 - Cadastrar receita/gasto\n");
    printf("2 - Visualizar categorias:\n");
    printf("3 - Gerar relatorio HTML\n");
    printf("0 - Sair do programa\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &op);

    if (op == 0) {
      i = 0;
      sair();
    } else if (op == 1) {
      i = 0;
      cadastrar();
    } else if (op == 2) {
      i = 0;
      visualizarCategorias();
    } else if (op == 3) {
      i = 0;
      gerarRelatorio();
    }
  }
}

int main(void) {
  menu();
  return 0;
}