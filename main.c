#include <stdio.h>
#include <string.h>
#include <time.h>

// Estrutura de uma movimentacao
struct Movimentacao {
  double valor;
  char descricao[100];
  char data[100];
  char categoria[100];
};

// Retorna uma data para segundos
int converteData(int dia, int mes, int ano) {
  struct tm tm = {};
  tm.tm_mday = dia;
  tm.tm_mon  = mes - 1;
  tm.tm_year = ano - 1900;
  time_t tempo = mktime(&tm);
  return tempo;
}

// Retorna a data atual em segundos
int verifDataAtual() {
  struct tm *atual;
  time_t segundos;
  time(&segundos); 
  atual = localtime(&segundos);
  return segundos;
}

// Grava a nova movimentacao em um arquivo txt
void gravarArquivo(struct Movimentacao m) {
  FILE *fr = fopen("movimentacoes.txt", "a");
  fprintf(fr, "%.2lf\n", m.valor);
  fprintf(fr, "%s\n", m.descricao);
  fprintf(fr, "%s\n", m.data);
  fprintf(fr, "%s\n", m.categoria);
  fclose(fr);
}

// Limpa o lixo de memoria para nao errar comparacoes
void limparVetor(char *v, int n) {
  for (int i = 0; i < n; i++) {
    v[i] = '\0';
  }
}

// Le a categoria necessaria no cadastro e no relatorio por cat.
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
void gerarRelatorioCat(char *cat, int dataAtual) {
  struct Movimentacao mov;
  int igual = 1; // Recebe 1 se as categorias sao iguais e 0, senao.
  int dia=0, mes=0, ano=0, data=0;

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
    fscanf(fr, "%d/%d/%d", &dia, &mes, &ano);
    fscanf(fr,  "%s", mov.categoria);
    data = converteData(dia, mes, ano);
    for (int i = 0; i < 100; i++) {
      if (mov.categoria[i] != cat[i]) {
        igual = 0;
      }
    }
    if (igual && ((dataAtual-2592000 <= data) && (data <= dataAtual))) {
      fprintf(html, "<tr><td>%s</td><td>%.2lf</td><td>%2d/%2d/%4d</td><td>%s</td></tr>\n", mov.descricao, mov.valor, dia, mes, ano, mov.categoria);
    }
  }

  fprintf(html, "</table>\n</body>\n</html>\n");
  fclose(fr);
  fclose(html);
  printf("\nRelatorio por categoria criado com sucesso!\n");
}

// Gera o relatorio das movimentacoes dos ultimos 12 meses
void gerarRelatorio12(int dataAtual) {
  struct Movimentacao mov;
  int dia=0, mes=0, ano=0, data=0;

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
    fscanf(fr, "%d/%d/%d", &dia, &mes, &ano);
    fscanf(fr,  "%s", mov.categoria);
    data = converteData(dia, mes, ano);
    if ((dataAtual-31104000 <= data) && (data <= dataAtual)) {
      fprintf(html, "<tr><td>%s</td><td>%.2lf</td><td>%d/%d/%d</td><td>%s</td></tr>\n", mov.descricao, mov.valor, dia, mes, ano, mov.categoria);
    }
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
  int i = -1, op = -1, dataAtual = verifDataAtual();
  while (i == -1) {
    printf("\nGerenciador financeiro:\n");
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
      cadastrar();
    } else if (op == 2) {
      i = 0;
      char cat[100];
      limparVetor(cat, 100);
      printf("Escolha uma categoria para gerar o relatorio:\n");
      lerCat(cat);
      gerarRelatorioCat(cat, dataAtual);
    } else if (op == 3) {
      i = 0;
      gerarRelatorio12(dataAtual);
    }
  }
}

// Funcao principal
int main(void) {
  menu();
  return 0;
  // 2592000 -> segundos em um mês
  // 31104000 -> segundos em um ano
}