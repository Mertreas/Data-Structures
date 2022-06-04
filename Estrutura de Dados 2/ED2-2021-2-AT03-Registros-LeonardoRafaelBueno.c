#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int idade;
    int codigo;
    char sexo[2];
    char telefone[15];
    char nome[31];
    char especialidade[31];
}Professor;

void Finaliza(FILE *entrada, FILE *temp, FILE *open, FILE *saida){
  fclose(entrada);
  fclose(saida);
  fclose(temp);
  fclose(open);
}//Finaliza

void LerArquivo(FILE *entrada, FILE *temp, FILE *open, FILE *saida, Professor iden[], char* aux){
  //variáveis
  char letra;
  int tamanho, top, linhas = 0, i = 0;
  char palavra[100];

  //Verificando se o arquivo de entrada está vazio
  letra = getc(entrada);
    if(letra == EOF){
        fprintf(saida,"Arquivo de leitura vazio\n");
        Finaliza(entrada, temp, open, saida);
        exit(1);
    }//if

  //Volta para o começo do arquivo
  fseek(entrada, 0, SEEK_SET);

  //Salva a quantidade de linhas existente no arquivo
  if(letra == 's'){
      do{
          letra = fgetc(entrada);
          if(letra == '\n'){
              linhas++;
          }//if
      }while(letra != EOF);
  }//if

  iden = (Professor*) malloc (sizeof(Professor)*linhas-1);
  //Volta para o começo do arquivo
  fseek(entrada, 0, SEEK_SET);
  //Escreve o tamanho e o top do arquivo
  fscanf(entrada, "tamanho '%d' top '%d'", &tamanho, &top);

  //Percorre o arquivo inteiro
  do{
    fscanf(entrada,"%[^|\n]s\n", palavra);

    aux= strtok(palavra, "|");

    iden[i].codigo = atoi(aux);
    aux= strtok(NULL, "|");
    printf("%d\n", iden[i].codigo);

    strcpy(iden[i].nome, aux);
    aux= strtok(NULL, "|");

    strcpy(iden[i].sexo, aux);
    aux= strtok(NULL, "|");

    iden[i].idade = atoi(aux);
    aux= strtok(NULL, "|");

    strcpy(iden[i].especialidade, aux);
    aux= strtok(NULL, "|");

    strcpy(iden[i].telefone, aux);
    aux= strtok(NULL, "|");

    i++;
  }while(letra != EOF);
  printf("Entrou!\n");
  for(int j = 0; j < linhas; j++){
    printf("%d || %s || %s || %d || %s || %s", iden[j].codigo, iden[j].nome, iden[j].sexo, iden[j].idade,
    iden[j].especialidade, iden[j].telefone);
  }//for
}//LerArquivo

/*void VerificaParametros(int argc, int argv){
  if(argc != 5){
    printf("Parametros invalidos\n");
    exit(1);
  }//if

  for(int i = 0; i < argc; i++) {
    printf("argv[%d] = %s\n", i, argv[i]);
  }//for
}//VerificaAbertura
*/
void LiberaMemoria(Professor iden[], char* aux){
  free(iden);
  free(aux);
}//LiberaMemoria

void VerificaAbertura(FILE *entrada, FILE *temp, FILE *open, FILE *saida){
  if(entrada == NULL || saida == NULL || temp == NULL || open == NULL){
      printf("Erro na abertura do arquivo!\n");
      Finaliza(entrada, temp, open, saida);
      exit(1);
  }//if
}//VerificaAbertura

int main(int argc, const char * argv[]) {

    //Variáveis
    Professor *iden;
    char *aux;

    //VerificaParametros(argc,argv);
    /*
    //abrir arquivos
    FILE* entrada = fopen(argv[1], "r");
    FILE* open = fopen(argv[2], "r");
    FILE* temp = fopen(argv[3], "w");
    FILE* saida = fopen(argv[4], "w");
    */
    FILE* entrada = fopen("input1.txt", "r");
    FILE* open = fopen("operations1.txt", "r");
    FILE* temp = fopen("temp1.txt", "w");
    FILE* saida = fopen("output1.txt", "w");

    VerificaAbertura(entrada, temp, open, saida);
    LerArquivo(entrada, temp, open, saida, iden, aux);
    Finaliza(entrada, temp, open, saida);
    LiberaMemoria(iden, aux);

    return 0;
}//main
