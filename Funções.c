#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Variavel global do tamanho da Hash
int total;

//Função para realizar o Hash
int hash(int key){
    return (key % total);
}

//inicializa a tabela
void inicializar(char *nomeArq){
    FILE *arq = fopen(nomeArq, "wb");
    registro a;
    a.disponibilidade = 1;
    for(int i = 0; i < total; i++){
        fwrite(&a, sizeof(registro), 1, arq);
    }
    fclose(arq);
}

//Função para achar posição na tabela
int acharPosicao(char *nomeArq, int x){
    int pos = hash(x);
    registro a;
    FILE *arq = fopen(nomeArq, "rb");
    fseek(arq, pos * sizeof(registro), SEEK_SET);
    fread(&a, sizeof(registro), 1, arq);
    while(a.disponibilidade == 0){
        pos = (pos + 1) % total;
        fseek(arq, pos * sizeof(registro), SEEK_SET);
        fread(&a, sizeof(registro), 1, arq);
    }
    fclose(arq);
    return pos;
}

//Função para inserir dados na tabela
void inserir(char* nomeArq, int matricula, char* nome, char* curso){
    int pos = acharPosicao(nomeArq, matricula);
    FILE *arq = fopen(nomeArq, "r+b");
    registro a;
    strcpy(a.nome, nome);
    strcpy(a.curso, curso);
    a.matricula = matricula;
    a.disponibilidade = 0;
    fseek(arq, pos * sizeof(registro), SEEK_SET);
    fwrite(&a, sizeof(registro), 1, arq);
    fclose(arq);
}

//Função para imprimir a tabela inteira
void imprimirTabela(char *nomeArq){
    FILE *arq = fopen(nomeArq, "r+b");
    registro a;
    for(int i = 0; i < total; i++){
        fseek(arq, i * sizeof(registro), SEEK_SET);
        fread(&a, sizeof(registro), 1, arq);
        if(a.disponibilidade == 0){
           printf("Posicao %d: Matrícula: %d, Nome: %s, Curso: %s\n", i, a.matricula, a.nome, a.curso);
        }else{
            printf("Posicao %d: Vazio\n", i);
        }
    }
    fclose(arq);
}

//Função para achar a posição de um aluno matriculado
int posicao(char *nomeArq, int mat){
    int pos = hash(mat);
    FILE *arq = fopen(nomeArq, "r+b");
    registro a;
    while(1){
        fseek(arq, pos * sizeof(registro), SEEK_SET);
        fread(&a, sizeof(registro), 1, arq);
        if(a.matricula == mat){
            fclose(arq);
            return pos;
        } if(a.disponibilidade==1){
            fclose(arq);
            return -1;
          }else{
            pos = (pos + 1) % total;
        }
    }
}

//Imprime os dados de um aluno se estiver matriculado
void imprimirumaluno(char *NomeArq, int matricula){
  FILE *arq = fopen(NomeArq, "r+b");
  registro a;
 int pos = posicao(NomeArq, matricula);
  if(pos>=0){
  fseek(arq, pos * sizeof(registro), SEEK_SET);
  fread(&a, sizeof(registro), 1, arq);
  printf("\nMatricula: %d\nNome: %s\nCurso: %s\nPosição na tabela: %d\n", a.matricula, a.nome, a.curso, pos);
  }else{
    printf("\nNão foi encontrado aluno com essa matricula");
  }
  fclose(arq);
}
