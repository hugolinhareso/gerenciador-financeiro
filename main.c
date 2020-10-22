#include <stdio.h>

void cadastrar() {
  printf("\nCadastrar receita/gasto\n");
}

void visualizarCategorias() {
  printf("\nVisualizar categorias\n");
}

void gerarRelatorio() {
  printf("\nGerar Relatorio HTML\n");
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