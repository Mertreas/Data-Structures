#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define TAM 6

typedef struct{
  char cod[4];
  char name[31];
  char sex;
  char idade[3];
  char especialidade[31];
  char telefone[15];
}Professor;

//------------------------------Verifica Arquivo--------------------------------
void VerificaAbertura(FILE *arq1, FILE *arq2, FILE *arq3){
  if(arq1==NULL || arq2==NULL || arq3==NULL){
    printf("Erro abertura dos arquivos\n");
    exit(1);
  }//if
}//VerificaAbertura

void FinalizaArquivo(FILE *arq1, FILE *arq2, FILE *arq3){
  fclose(arq1);
  fclose(arq2);
  fclose(arq3);
}//FinalizaArquivo

//-------------------------------InscriçãoeLeitura------------------------------
void escreverRegistrosTamanhoFixo(FILE *arq2,Professor p[]){

    int tamanho=0,cont_cod=3,cod_name=30,cont_especialidade=30,cont_telefone=14;
    int j=0,i;

    while(j!=6){
      tamanho=strlen(p[j].cod);
      fprintf(arq2,"%s",p[j].cod);
      for(i=0;i<cont_cod-tamanho;i++) {
      fprintf(arq2," ");
      }//for
      fprintf(arq2,"|");

      tamanho=strlen(p[j].name);
      fprintf(arq2,"%s",p[j].name);
      for(i=0;i<cod_name-tamanho;i++){
      fprintf(arq2," ");
      }//for
      fprintf(arq2,"|");

      fprintf(arq2,"%c",p[j].sex);
      fprintf(arq2,"|");

      tamanho=strlen(p[j].idade);
      fprintf(arq2,"%s",p[j].idade);
      fprintf(arq2,"|");

      tamanho=strlen(p[j].especialidade);
      fprintf(arq2,"%s",p[j].especialidade);
      for(i=0;i<cont_especialidade-tamanho;i++) {
      fprintf(arq2," ");
      }//for
      fprintf(arq2,"|");

      tamanho=strlen(p[j].telefone);
      fprintf(arq2,"%s",p[j].telefone);
      for(i=0;i<cont_telefone-tamanho;i++){
      fprintf(arq2," ");
      }//for
      fprintf(arq2,"|\n");
      j++;
  }//while
}//escreverRegistrosTamanhoFixo

void escreverRegistrosIndicadoresTamanho(FILE* arq2, Professor Registro[]){
  int contador=0;
    for(int i=0; i<TAM ;i++){
      contador=strlen(Registro[i].cod)+strlen(Registro[i].name)+1+strlen(Registro[i].idade)+strlen(Registro[i].especialidade)+strlen(Registro[i].telefone)+6;
      fprintf(arq2,"%d %s|%s|%c|%s|%s|%s|",contador,Registro[i].cod,Registro[i].name,Registro[i].sex,Registro[i].idade,Registro[i].especialidade,Registro[i].telefone);
    }//for
}//escreverRegistrosIndicadoresTamanho

void escreverRegistrosDelimitadores(FILE* arq2, Professor Registro[]){
  for(int i=0; i<TAM ;i++){
    fprintf(arq2,"%s|%s|%c|%s|%s|%s|#",Registro[i].cod,Registro[i].name,Registro[i].sex,Registro[i].idade,Registro[i].especialidade,Registro[i].telefone);
  }//for
}//escreverRegistrosDelimitadores

void lerRegistrosTamanhoFixo(FILE* arq3, Professor Registro[]){
    char caracter;
    int i=0;

    fseek(arq3,sizeof(int),SEEK_SET);
  //while rodando até o final do arquvio
  while(fgetc(arq3)=='|'){

    fscanf(arq3,"%3[^,]*c",&Registro[i].cod);
    //printf("%s ",Registro[i].cod );
    fscanf(arq3,"%c",&caracter);

    fscanf(arq3,"%30[^,]*c",&Registro[i].name);
    //printf("%s ",Registro[i].name );
    fscanf(arq3,"%c",&caracter);

    fscanf(arq3,"%c",&Registro[i].sex);
    //printf("%c ",Registro[i].sex);
    fscanf(arq3,"%c",&caracter);

    fscanf(arq3,"%3[^,]*c",&Registro[i].idade);
    //printf("%s ",Registro[i].idade);
    fscanf(arq3,"%c",&caracter);

    fscanf(arq3,"%30[^,]*c",&Registro[i].especialidade);
    //printf("%s ",Registro[i].especialidade);
    fscanf(arq3,"%c",&caracter);

    fscanf(arq3,"%14[^,]*c",&Registro[i].telefone);
    //printf("%s\n",Registro[i].telefone );
    fscanf(arq3,"%c",&caracter);
    fscanf(arq3,"%c",&caracter);
    i++;
  }//while

  for(int i=0;i<6;i++){
    printf("{%s,%s,%c,%s,%s,%s}\n",Registro[i].cod,Registro[i].name,Registro[i].sex,Registro[i].idade,Registro[i].especialidade,Registro[i].telefone);
  }//for
}//lerRegistrosTamanhoFixo

void lerRegistrosIndicadoresTamanho(FILE* arq3, Professor Registro[]){
    char caracter;
    int i=0;

    fseek(arq3,2*sizeof(int),SEEK_SET);
    //while rodando até o final do arquvio
    while(fgetc(arq3)=='{'){

    fscanf(arq3,"%3[^,]*c",&Registro[i].cod);
    //printf("%s ",Registro[i].cod );
    fscanf(arq3,"%c",&caracter);

    fscanf(arq3,"%30[^,]*c",&Registro[i].name);
    //printf("%s ",Registro[i].name );
    fscanf(arq3,"%c",&caracter);

    fscanf(arq3,"%c",&Registro[i].sex);
    //printf("%c ",Registro[i].sex);
    fscanf(arq3,"%c",&caracter);

    fscanf(arq3,"%3[^,]*c",&Registro[i].idade);
    //printf("%s ",Registro[i].idade);
    fscanf(arq3,"%c",&caracter);

    fscanf(arq3,"%30[^,]*c",&Registro[i].especialidade);
    //printf("%s ",Registro[i].especialidade);
    fscanf(arq3,"%c",&caracter);

    fscanf(arq3,"%14[^,]*c",&Registro[i].telefone);
    //printf("%s\n",Registro[i].telefone );
    fscanf(arq3,"%c",&caracter);
    fscanf(arq3,"%c",&caracter);
    i++;
    }//while

    for(int i=0;i<6;i++){
    printf("{%s,%s,%c,%s,%s,%s}\n",Registro[i].cod,Registro[i].name,Registro[i].sex,Registro[i].idade,Registro[i].especialidade,Registro[i].telefone);
    }//for
}//lerRegistrosIndicadoresTamanho

void lerRegistrosDelimitadores(FILE* arq3, Professor Registro[]){
    char caracter;
    int i=0;

    fseek(arq3,sizeof(int),SEEK_SET);
    //while rodando até o final do arquvio
    while(fgetc(arq3)=='|'){

    fscanf(arq3,"%3[^,]*c",&Registro[i].cod);
    //printf("%s ",Registro[i].cod );
    fscanf(arq3,"%c",&caracter);

    fscanf(arq3,"%30[^,]*c",&Registro[i].name);
    //printf("%s ",Registro[i].name );
    fscanf(arq3,"%c",&caracter);

    fscanf(arq3,"%c",&Registro[i].sex);
    //printf("%c ",Registro[i].sex);
    fscanf(arq3,"%c",&caracter);

    fscanf(arq3,"%3[^,]*c",&Registro[i].idade);
    //printf("%s ",Registro[i].idade);
    fscanf(arq3,"%c",&caracter);

    fscanf(arq3,"%30[^,]*c",&Registro[i].especialidade);
    //printf("%s ",Registro[i].especialidade);
    fscanf(arq3,"%c",&caracter);

    fscanf(arq3,"%14[^,]*c",&Registro[i].telefone);
    //printf("%s\n",Registro[i].telefone );
    fscanf(arq3,"%c",&caracter);
    fscanf(arq3,"%c",&caracter);
    i++;
}//while

    for(int i=0;i<6;i++){
    printf("{%s,%s,%c,%s,%s,%s}\n",Registro[i].cod,Registro[i].name,Registro[i].sex,Registro[i].idade,Registro[i].especialidade,Registro[i].telefone);
    }//for
}//lerRegistrosDelimitadores

//-------------------------------Função Principal-------------------------------
int main(int argc, const char * argv[]){

  Professor Registro[TAM];
  int i=0;
  char caracter;
  char opcao;

  if(argc!= 3) {
    printf("Quantidade de parametros invalida\n");
    return 0;
  }//if para conferir se tem a quantidade de paramentos

  for(int i = 0; i < argc; i++) {
    printf("argv[%d] = %s\n", i, argv[i]);
  }//for exibe os argv - "os arquivos a serem abertos"

  //abrir arquivos
  FILE* arq1=fopen(argv[1], "r");
  FILE* arq2=fopen(argv[2], "w");
  FILE *arq3=fopen(argv[3],"r");

  VerificaAbertura(arq1,arq2,arq3);

  //while rodando até o final do arquvio
  while(fgetc(arq1)=='{'){

    fscanf(arq1,"%3[^,]*c",&Registro[i].cod);
    fscanf(arq1,"%c",&caracter);

    fscanf(arq1,"%30[^,]*c",&Registro[i].name);
    fscanf(arq1,"%c",&caracter);

    fscanf(arq1,"%c",&Registro[i].sex);
    fscanf(arq1,"%c",&caracter);

    fscanf(arq1,"%3[^,]*c",&Registro[i].idade);
    fscanf(arq1,"%c",&caracter);

    fscanf(arq1,"%30[^,]*c",&Registro[i].especialidade);
    fscanf(arq1,"%c",&caracter);

    fscanf(arq1,"%14[^,]*c",&Registro[i].telefone);
    fscanf(arq1,"%c",&caracter);
    fscanf(arq1,"%c",&caracter);

    i++;
  }//while

  rewind(arq1);
  fseek(arq1,-2,SEEK_END);
  fscanf(arq1,"%c",&opcao);

  switch(opcao){
    case '1':
      escreverRegistrosTamanhoFixo(arq2, Registro);
      lerRegistrosTamanhoFixo(arq2, Registro);
    break;

    case'2':
      escreverRegistrosIndicadoresTamanho(arq2, Registro);
      lerRegistrosDelimitadores(arq2, Registro);
    break;

    case'3':
      escreverRegistrosDelimitadores(arq2, Registro);
      lerRegistrosDelimitadores(arq2, Registro);
    break;

    default:
      printf("\nErro na opção do arquivo\n\n");
  }//switch

    FinalizaArquivo(arq1,arq2,arq3);
  return 0;
}//main
