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

// Lê o arquivo e salva os elementos em uma lista de char
void lerArquivo(char *v) {
  char aux[100];
  FILE *fr = fopen("movimentacoes.txt", "r");
  int i = 0;

  while (fscanf(fr, "%s", aux) != EOF) {
    i++;
  }

  fclose(fr);
}

// Cadastra uma nova receita/gasto
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

// Gera o relatorio das movimentacoes por categoria
void gerarRelatorioCat() {
  struct Movimentacao mov;

  FILE *fr = fopen("movimentacoes.txt", "r");
  FILE *html = fopen("relatorio_cat.html", "w");

  fprintf(html, "<html lang=\"br\">\n");
  fprintf(html, "<head>\n<meta charset=\"UTF-8\">\n");
  fprintf(html, "<title>Relatório por categoria</title>\n");
  fprintf(html, "</head>\n<body>\n");
  fprintf(html, "<table border=\"1\">\n");
  fprintf(html, "<tr><th>Descricao</th><th>Valor R$</th><th>Data (dd/mm/aa)</th><th>Categoria</th></tr>\n");

  while (fscanf(fr, "%lf", &mov.valor) != EOF) {
      fscanf(fr, " %[^\n]s", mov.descricao);
      fscanf(fr,  "%s %s", mov.data, mov.categoria);
      fprintf(html, "<tr><td>%s</th><td>%.2lf</td><td>%s</td><td>%s</td></tr>\n", mov.descricao, mov.valor, mov.data, mov.categoria);
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
      fprintf(html, "<tr><td>%s</th><td>%.2lf</td><td>%s</td><td>%s</td></tr>\n", mov.descricao, mov.valor, mov.data, mov.categoria);
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
      gerarRelatorioCat();
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