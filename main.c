#include <stdio.h>
#include <string.h>

// Estrutura de uma movimentacao
struct Movimentacao {
  double valor;
  char descricao[100];
  char data[100];
  char categoria[100];
};

// Grava a nova movimentacao em um arquivo txt
void gravarArquivo(struct Movimentacao m) {
  FILE *fr = fopen("movimentacoes.txt", "a");
  fprintf(fr, "%.2lf\n", m.valor);
  fprintf(fr, "%s\n", m.descricao);
  fprintf(fr, "%s\n", m.data);
  fprintf(fr, "%s\n", m.categoria);
  fclose(fr);
}

// Limpa o lixo de memória para não errar comparações
void limparVetor(char *v, int n) {
  for (int i = 0; i < n; i++) {
    v[i] = '\0';
  }
}

// Lê a categoria necessária no cadastro e no relatório por cat.
void lerCat(char *cat) {
  int aux = 0;
  printf("Categoria (0 - Moradia, 1 - Estudos, 2 - Transporte, 3 - Alimentacao, 4 - Trabalho): ");
  scanf("%d", &aux);
  if (aux == 0) {
    strcpy(cat, "Moradia");
  } else if (aux == 1) {
    strcpy(cat, "Estudos");
  } else if (aux == 2) {
    strcpy(cat, "Transporte");
  } else if (aux == 3) {
    strcpy(cat, "Alimentacao");
  } else if (aux == 4) {
    strcpy(cat, "Trabalho");
  }
}

// Cadastra uma nova receita/gasto
void cadastrar() {
  struct Movimentacao nova;
  printf("\nCadastrar receita/gasto (adicionar sinal -)\n");
  printf("Valor: R$ ");
  scanf("%lf", &nova.valor);
  printf("Descricao: ");
  scanf(" %[^\n]s", nova.descricao);
  printf("Data (dd/mm/aa): ");
  scanf("%s", nova.data);
  lerCat(nova.categoria);

  gravarArquivo(nova);
  printf("\nMovimentacao cadastrada com sucesso!\n");
}

// Gera o relatorio das movimentacoes por categoria
void gerarRelatorioCat(char *cat) {
  struct Movimentacao mov;
  int igual = 1; // Recebe 1 se as categorias são iguais e 0, senão.

  FILE *fr = fopen("movimentacoes.txt", "r");
  FILE *html = fopen("relatorio_cat.html", "w");

  fprintf(html, "<html lang=\"br\">\n");
  fprintf(html, "<head>\n<meta charset=\"UTF-8\">\n");
  fprintf(html, "<title>Relatório por categoria</title>\n");
  fprintf(html, "</head>\n<body>\n");
  fprintf(html, "<table border=\"1\">\n");
  fprintf(html, "<tr><th>Descricao</th><th>Valor R$</th><th>Data (dd/mm/aa)</th><th>Categoria</th></tr>\n");

  while (fscanf(fr, "%lf", &mov.valor) != EOF) {
    igual = 1;
    limparVetor(mov.categoria, 100);
    fscanf(fr, " %[^\n]s", mov.descricao);
    fscanf(fr,  "%s %s", mov.data, mov.categoria);
    for (int i = 0; i < 100; i++) {
      if (mov.categoria[i] != cat[i]) {
        igual = 0;
      }
    }
    if (igual) {
      fprintf(html, "<tr><td>%s</td><td>%.2lf</td><td>%s</td><td>%s</td></tr>\n", mov.descricao, mov.valor, mov.data, mov.categoria);
    }
  }

  fprintf(html, "</table>\n</body>\n</html>\n");
  fclose(fr);
  fclose(html);
  printf("\nRelatorio por categoria criado com sucesso!\n");
}

// Gera o relatorio das movimentacoes dos ultimos 12 meses
void gerarRelatorio12() {
  struct Movimentacao mov;

  FILE *fr = fopen("movimentacoes.txt", "r");
  FILE *html = fopen("relatorio.html", "w");

  fprintf(html, "<html lang=\"br\">\n");
  fprintf(html, "<head>\n<meta charset=\"UTF-8\">\n");
  fprintf(html, "<title>Relatório - últimos 12 meses</title>\n");
  fprintf(html, "</head>\n<body>\n");
  fprintf(html, "<table border=\"1\">\n");
  fprintf(html, "<tr><th>Descricao</th><th>Valor R$</th><th>Data (dd/mm/aa)</th><th>Categoria</th></tr>\n");

  while (fscanf(fr, "%lf", &mov.valor) != EOF) {
    fscanf(fr, " %[^\n]s", mov.descricao);
    fscanf(fr,  "%s %s", mov.data, mov.categoria);
    fprintf(html, "<tr><td>%s</td><td>%.2lf</td><td>%s</td><td>%s</td></tr>\n", mov.descricao, mov.valor, mov.data, mov.categoria);
  }

  fprintf(html, "</table>\n</body>\n</html>\n");
  fclose(fr);
  fclose(html);
  printf("\nRelatorio dos últimos 12 meses criado com sucesso!\n");
}

// Saida do programa
void sair() {
  printf("\nObrigado por usar o programa. Ate logo!\n");
}

// Menu principal
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
      char cat[100];
      limparVetor(cat, 100);
      printf("Escolha uma categoria para gerar o relatorio:\n");
      lerCat(cat);
      gerarRelatorioCat(cat);
    } else if (op == 3) {
      i = 0;
      gerarRelatorio12();
    }
  }
}

// Funcao principal
int main(void) {
  menu();
  return 0;
}