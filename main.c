#include <stdio.h>
#include <string.h>

struct Movimentacao {
  double valor;
  char descricao[100];
  char data[100];
  char categoria[100];
};

void gravarArquivo(struct Movimentacao m) {
  FILE *fr = fopen("movimentacoes.txt", "a");
  fprintf(fr, "%.2lf\n", m.valor);
  fprintf(fr, "%s\n", m.descricao);
  fprintf(fr, "%s\n", m.data);
  fprintf(fr, "%s\n", m.categoria);
  fclose(fr);
}

void cadastrar() {
  int aux = 0;
  struct Movimentacao nova;
  printf("\nCadastrar receita/gasto (adicionar sinal -)\n");
  printf("Valor: R$ ");
  scanf("%lf", &nova.valor);
  printf("Descricao: ");
  scanf(" %[^\n]s", nova.descricao);
  printf("Data (dd/mm/aa): ");
  scanf("%s", nova.data);
  printf("Categoria (0 - Moradia, 1 - Estudos, 2 - Transporte, 3 - Alimentacao, 4 - Trabalho): ");
  scanf("%d", &aux);
  
  if (aux == 0) {
    strcpy(nova.categoria, "Moradia");
  } else if (aux == 1) {
    strcpy(nova.categoria, "Estudos");
  } else if (aux == 2) {
    strcpy(nova.categoria, "Transporte");
  } else if (aux == 3) {
    strcpy(nova.categoria, "Alimentacao");
  } else if (aux == 4) {
    strcpy(nova.categoria, "Trabalho");
  }

  gravarArquivo(nova);
  printf("\nMovimentacao cadastrada com sucesso!\n");
}

void gerarRelatorioCat() {
  FILE *fr = fopen("relatorio_cat.html", "w");
  fprintf(fr, "<html lang=\"br\">\n<head>\n<meta charset=\"UTF-8\">\n<title>Relatório - Categorias</title>\n</head>\n<body>\n<h1>Relatório</h1>\n</body>\n</html>");
  fclose(fr);
  printf("\nRelatorio das movimentacoes por categoria criado com sucesso!\n");
}

void gerarRelatorio12() {
  FILE *fr = fopen("relatorio.html", "w");
  fprintf(fr, "<html lang=\"br\">\n<head>\n<meta charset=\"UTF-8\">\n<title>Relatório - Últimos 12 meses</title>\n</head>\n<body>\n<h1>Relatório</h1>\n</body>\n</html>");
  fclose(fr);
  printf("\nRelatorio dos ultimos 12 meses criado com sucesso!\n");
}

void sair() {
  printf("\nObrigado por usar o programa. Ate logo!\n");
}

void menu() {
  int i = -1, op = -1;
  while (i == -1) {
    printf("Gerenciador financeiro:\n");
    printf("1 - Cadastrar receita/gasto\n");
    printf("2 - Movimentacoes por categoria\n");
    printf("3 - Movimentacoes nos ultimos 12 meses\n");
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
      gerarRelatorioCat();
    } else if (op == 3) {
      i = 0;
      gerarRelatorio12();
    }
  }
}

int main(void) {
  menu();
  return 0;
}