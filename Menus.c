#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Variavel global do tamanho da Hash
int total;

//Menu do programa
void menu() {
  int op;
  char continua[5] = "sim";
  registro res;
  int cont = 0;

  printf("Bem vindo ao programa de Tabela Hash!\nAntes de começar, diga qual vai ser o tamanho da sua tabela (Recomendamos usar um número primo): ");
  scanf(" %d", &total);

  inicializar("arquivo.txt");

  while (strcmp(continua, "sim") == 0 || strcmp(continua, "Sim") == 0 || strcmp(continua, "SIM") == 0 ||  strcmp(continua, "s") == 0 || strcmp(continua, "S") == 0) {

    printf("\nEscolha uma das opções abaixo:\n"
           "1 -Inserir novo aluno\n"
           "2 - Imprimir informações de um determinado aluno, usando a matricula como referencia\n"
           "3 - Imprimir a tabela Hash\n"
           "4 - Sair");
    puts("");
    scanf(" %d", &op);

    switch (op) {
    case (1):
      if (cont >= total - 1) {
        printf("Você não pode adicionar mais elementos");
      } else {
        printf("\nDigite os dados do aluno que deseja adicionar: ");
        printf("\nNome: ");
        fflush(stdin);
        scanf(" %[^\n]s", res.nome);
        printf("Matricula: ");
        fflush(stdin);
        scanf(" %d", &res.matricula);
        printf("Curso: ");
        fflush(stdin);
        scanf(" %[^\n]s", res.curso);

        inserir("arquivo.txt", res.matricula, res.nome, res.curso);
        cont++;
        printf("\nElemento foi adicionado ");
      }
      break;

    case (2):

      printf("\nImprimindo elemento desejado");
      printf("\nDigite a matrícula do aluno que deseja imprimir: ");
      scanf("%d", &res.matricula);
      imprimirumaluno("arquivo.txt", res.matricula);
      break;

    case (3):
        printf("\nImprimindo todos os elementos da Heap:\n");
        imprimirTabela("arquivo.txt");
      break;

    case (4):
      printf("\n\nObrigado por utilizar nosso programa!");
      strcpy(continua, "nao");
      break;

    default:
      printf("\nOpção inválida\n");
    }

    if (op != 4) {
      printf("\nDeseja continuar? ");
      scanf("%s", continua);
      puts("");
    }
  }
}
