#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <math.h>

void finalizaarq(FILE *arq1,FILE *arq2){

  //finaliza e libera os arquivos
  fclose(arq1);
  fclose(arq2);
  free(arq1);
  free(arq2);

}//finalizaarq

//------------------------------ BUBBLESORT ------------------------------------

//função de Ordenação Bubblesort
int BubbleSort(int *vetor, int n){

  int i, continua, aux, fim = n;//variável continua para manter a iteração até o final
  int comparacao = 0; //vai medir a quantidade de comparações

  // fazer do/while até terminar o vetor
  do{
    continua = 0; //usado para zerar o "continua" para sair no laço caso o vetor esteje ordenado

    //O for serve para arrastar o maior elemento até o fim do vetor
    for(i = 0; i < fim - 1; i++){

      //Se o valor anterior for maior que o próximo, eles trocando de lugar
      if(vetor[i] > vetor[i+1]){
        aux = vetor[i];
        vetor[i] = vetor[i+1];
        vetor[i+1] = aux;
        continua = i;
        comparacao++;
      }//if

      comparacao++;

    }//for

    fim--; //Decremeta o fim pois o maior número já foi adicionado ao final do vetor
  }while (continua != 0);

  return comparacao;
}//Bubblesort

//------------------------------ SELECTIONSORT ---------------------------------

//função de ordenação SelectionSort
int SelectionSort(int *vetor, int n){

  int i, j, menor, aux;//variáveis para auxiliar
  int comparacao = 0; //vai medir a quantidade de comparações

  //for para percorrer todo o vetor
  for(i = 0; i < n-1; i++){
    menor = i;//iguala o menor ao valor de "i" de cada iteração'

    //compara os números dentro do vetor verificando qual o menor
    for(j = i+1; j < n; j++){

      if(vetor[j] < vetor[menor]){
        menor = j;
        comparacao++;

      }//if
      comparacao++;
    }//for

    if(i != menor){
      aux = vetor[i];
      vetor[i] = vetor[menor];
      vetor[menor] = aux;
    }//if
  }//for

  return comparacao;
}//SelectionSort

//------------------------------ INSERTIONSORT ---------------------------------

//função de ordenação InsertionSort
int InsertionSort(int *vetor, int n){

  int i, j, aux;
  int comparacao = 0; //vai medir a quantidade de comparações

  //percorre todos o vetor
  for(i = 1; i < n; i++){
    //salvando o valor do número para depois colocar ele no lugar correto
    aux = vetor[i];
    //percorrendo o vetor comparando os valores de são menores
    for(j = i; (j > 0) && (aux < vetor[j - 1]); j--){
        vetor[j] = vetor[j - 1];
        comparacao++;
    }//for

    vetor[j] = aux;
    comparacao++;
  }//for

  return comparacao;
}//InsertionSort

//------------------------------ MERGESORT -----------------------------------

//função que ordena o vetor principal do MergeSort
int Merge(int *vetor, int inicio, int meio, int fim){

  //variavéis
  int *temp, v1, v2, tamanho, i, j, k;
  int fim1 = 0, fim2 = 0;
  tamanho = fim - inicio + 1;
  v1 = inicio;
  v2 = meio+1;
  temp = (int *) malloc(tamanho*sizeof(int));//alocando o vetor dinamicamente
  int comparacao = 0; //vai medir a quantidade de comparações

  //se for diferente de nulo
  if(temp != NULL){
      for(i = 0; i < tamanho; i++){
        if(!fim1 && !fim2){
            if(vetor[v1] < vetor[v2]){ //Atribuindo o menor elemento entre os vetores
              temp[i] = vetor[v1++];
              comparacao++;
            }else{
              temp[i] = vetor[v2++];
              comparacao++;

              //condições para saber se chegou ao fim do vetor
              if(v1 > meio){
                fim1 = 1;
                comparacao++;
              }if(v2 > fim){
                fim2 = 1;
                comparacao++;
              }//if
            }//else

            comparacao++;
        }else{ //caso chege ao fim, copia o resto do vetor para o vetor principal
            if(!fim1){
              temp[i] = vetor[v1++];
              comparacao++;
            }else{
              temp[i] = vetor[v2++];
              comparacao++;
            }//else
        }//else
        comparacao++;
      }//for

      //Copia os valores do auxiliar para original
      for(j = 0, k = inicio; j < tamanho; j++, k++){
        vetor[k] = temp[j];
      }//for

      comparacao++;
  }//if

   free(temp);
  return comparacao;
}//Merge

//função de ordenação MergeSort
int MergeSort(int *vetor, int inicio, int fim){

  int meio;
  int comparacao; //vai medir a quantidade de comparações

  //Se o início for menor que o fim
  if(inicio < fim){
    meio = floor((inicio+fim)/2);//dividindo o vetor em duas partes
    MergeSort(vetor, inicio, meio);//chamando a primeira parte do vetor
    MergeSort(vetor, meio+1, fim);//chamando a segunda parte do vetor
    comparacao = Merge(vetor, inicio, meio, fim);//chamando a função que agrupa os vetores
  }//if

  return comparacao;
}//MergeSort

//---------------------------------- QUICKSORT ---------------------------------
//função que ordena o vetor principal do QuickSort
int Particiona(int *vetor, int inicio, int final){

  int Esquerda = inicio-1;
  int Direita = final;
  int Pivo = vetor[inicio];
  int aux;

  while(Esquerda < Direita){

    while(vetor[Esquerda] <= Pivo){
      Esquerda++;
    }//while
    while(vetor[Direita] > Pivo){
      Direita--;
    }//while

    if(Esquerda < Direita){
      aux = vetor[Esquerda];
      vetor[Esquerda] = vetor[Direita];
      vetor[Direita] = aux;
    }//if
  }//while

  vetor[inicio] = vetor[Direita];
  vetor[Direita] = Pivo;

  return Direita;
}//Particiona

int Particiona2(int *vetor, int inicio, int final){

  int Esquerda = inicio;
  int Direita = final;
  int Pivo = vetor[inicio];
  int aux;
  int comparacao = 0; //vai medir a quantidade de comparações

  while(Esquerda < Direita){

    while(vetor[Esquerda] <= Pivo){
      Esquerda++;
      comparacao++;
    }//while
    while(vetor[Direita] > Pivo){
      Direita--;
      comparacao++;
    }//while

    comparacao++;

    if(Esquerda < Direita){
      aux = vetor[Esquerda];
      vetor[Esquerda] = vetor[Direita];
      vetor[Direita] = aux;
      comparacao++;
    }//if
  }//while

  vetor[inicio] = vetor[Direita];
  vetor[Direita] = Pivo;

  return comparacao;
}//Particiona

int QuickSort(int *vetor, int inicio, int final){

  int Pivo, Pivo2;

  if(final > inicio){

    Pivo = Particiona(vetor, inicio, final);
    Pivo2 = Particiona2(vetor, inicio, final);
    QuickSort(vetor, inicio, Pivo-1);
    QuickSort(vetor, Pivo+1, final);

  }//if

  return Pivo2;
}//Quicksort

//------------------------------------------------------------------------------

char identifica(FILE *arq1,FILE *arq2, int *quant){

  //declaracao de variaveis
  char caracter,iden;

  //while rodando até o final do arquvio
  while (!feof(arq1)) {

  fscanf(arq1,"%i",quant);
  fscanf(arq1,"%c",&caracter);
  fscanf(arq1,"%c",&caracter);
  if (caracter == 'c' || caracter == 'd' || caracter == 'r'){
    if(caracter =='c'){
      iden ='c';
      break;
    }//if para salvar o idenficador de pilha como c
    if(caracter =='d'){
      iden ='d';
      break;
    }//if para salvar o idenficador de pilha como d
    if(caracter =='r'){
      iden ='r';
      break;
    }//if para salvar o idenficador de pilha como r
  }//if para quando o identificador de pilha for c ou d ou r

  if (caracter != 'c' || caracter != 'd' || caracter != 'r'){
      fprintf(arq2, "Arquivo inválido!");
      printf("-= Erro / O identificador do tipo de pilhas e diferente de 'c' ou de 'd' e de 'r '=-\n");
      finalizaarq(arq1,arq2);
      return 0;
  }//if para quando o identificador de pilha nao for 'e' nem 'd'
  }//while

  //retornando para o inicio do arquivo
  rewind(arq1);

  //retornando o valor de pessoas
  return iden;
}//identifica

//função que imprime o vetor e depois da ordenação
void Imprimir(int *vetor, int n, int inicio, int fim, char caracter, FILE *arq2){

  int comparacao = 0;
  int Vbuble[n], VSelect[n], Vinsert[n], Vmerge[n], Vquick[n];
  int start1,start2,start3,start4,start5;
  int time_taken_millis1,time_taken_millis2,time_taken_millis3,time_taken_millis4,time_taken_millis5;

  for(int i=0; i<n; i++){
    Vbuble[i]=vetor[i];
    VSelect[i]=vetor[i];
    Vinsert[i]=vetor[i];
    Vmerge[i]=vetor[i];
    Vquick[i]=vetor[i];
  }//for

  start1 = clock();
  comparacao = BubbleSort(Vbuble, n);
  printf("\n \n \n");
  printf("BubbleSort:    ");
  fprintf(arq2, "BubbleSort:    ");

  if(caracter == 'd'){

    for(int i = n - 1; i >= 0; i--){
      printf(" %i", Vbuble[i]);
      fprintf(arq2, " %i", Vbuble[i]);
    }//for

  }else{

    for(int i = 0; i < n; i++){
      printf(" %i", Vbuble[i]);
      fprintf(arq2, " %i", Vbuble[i]);
    }//for

  }//else
  //time_taken_millis1 = (int)((clock()-start1)*1E3/CLOCKS_PER_SEC);
  time_taken_millis1 = (int)((clock()-start1));
  printf(", %i comp", comparacao);
  fprintf(arq2, ", %i comp", comparacao);
  printf( " %i ms", time_taken_millis1);
  fprintf(arq2, " %i ms", time_taken_millis1);
  printf("\n");
  fprintf(arq2,"\n");

  start2 = clock();
  comparacao = SelectionSort(VSelect, n);
  printf("SelectionSort: ");
  fprintf(arq2, "SelectionSort: ");

  if(caracter == 'd'){

    for(int i = n - 1; i >= 0; i--){
      printf(" %i", VSelect[i]);
      fprintf(arq2, " %i", VSelect[i]);
    }//for

  }else{

    for(int i = 0; i < n; i++){
      printf(" %i", VSelect[i]);
      fprintf(arq2, " %i", VSelect[i]);
    }//for

  }//else
  //time_taken_millis2 = (int)((clock()-start2)*1E3/CLOCKS_PER_SEC);
  time_taken_millis2 = (int)((clock()-start2));
  printf(", %i comp", comparacao);
  fprintf(arq2, ", %i comp", comparacao);
  printf( " %i ms", time_taken_millis2);
  fprintf(arq2, " %i ms", time_taken_millis2);
  printf("\n");
  fprintf(arq2,"\n");

  start3 = clock();
  comparacao = InsertionSort(Vinsert, n);
  printf("InsertionSort: ");
  fprintf(arq2, "InsertionSort: ");

    if(caracter == 'd'){

    for(int i = n - 1; i >= 0; i--){
      printf(" %i", Vinsert[i]);
      fprintf(arq2, " %i", Vinsert[i]);
    }//for

  }else{

    for(int i = 0; i < n; i++){
      printf(" %i", Vinsert[i]);
      fprintf(arq2, " %i", Vinsert[i]);
    }//for

  }//else
  //time_taken_millis3 = (int)((clock()-start3)*1E3/CLOCKS_PER_SEC);
  time_taken_millis3 = (int)((clock()-start3));
  printf(", %i comp", comparacao);
  fprintf(arq2, ", %i comp", comparacao);
  printf( " %i ms", time_taken_millis3);
  fprintf(arq2, " %i ms", time_taken_millis3);
  printf("\n");
  fprintf(arq2,"\n");

  start4 = clock();
  comparacao = MergeSort(Vmerge, inicio, fim);
  printf("MergeSort:     ");
  fprintf(arq2, "MergeSort:     ");

  if(caracter == 'd'){

    for(int i = n - 1; i >= 0; i--){
      printf(" %i", Vmerge[i]);
      fprintf(arq2, " %i", Vmerge[i]);
    }//for

  }else{

    for(int i = 0; i < n; i++){
      printf(" %i", Vmerge[i]);
      fprintf(arq2, " %i", Vmerge[i]);
    }//for

  }//else
  //time_taken_millis4 = (int)((clock()-start4)*1E3/CLOCKS_PER_SEC);
  time_taken_millis4 = (int)((clock()-start4));
  printf(", %i comp", comparacao);
  fprintf(arq2, ", %i comp", comparacao);
  printf( " %i ms", time_taken_millis4);
  fprintf(arq2, " %i ms", time_taken_millis4);
  printf("\n");
  fprintf(arq2,"\n");

  start5 = clock();
  comparacao = QuickSort(Vquick, inicio, fim);
  printf("QuickSort:     ");
  fprintf(arq2, "QuickSort:     ");

  if(caracter == 'd'){

    for(int i = n-1; i >= 0; i--){
      printf(" %i", Vquick[i]);
      fprintf(arq2, " %i", Vquick[i]);
    }//for

  }else{

    for(int i = 0; i < n; i++){
      printf(" %i", Vquick[i]);
      fprintf(arq2, " %i", Vquick[i]);
    }//for

  }//else
  //time_taken_millis5 = (int)((clock()-start5)*1E3/CLOCKS_PER_SEC);
  time_taken_millis5 = (int)((clock()-start5));
  printf(", %i comp", comparacao);
  fprintf(arq2, ", %i comp", comparacao);
  printf( " %i ms", time_taken_millis5);
  fprintf(arq2, " %i ms", time_taken_millis5);
  printf("\n \n \n");
  fprintf(arq2,"\n");

}//Imprimir

int *gerador(int tamanho){
  int *vetor;

  vetor=(int*)malloc(tamanho*sizeof(int));

  return(vetor);
}//gerador

char Preenche(int *vetor, int tamanho, char caracter){

  if (caracter == 'c' || caracter == 'd' || caracter == 'r'){
    if(caracter =='c'){
      for(int i=0; i<tamanho; i++){
        vetor[i]=i;
      }//for
    }//if para salvar o idenficador de pilha como c

    if(caracter =='d'){
      for(int i=tamanho; i>0; i--){
        vetor[i-1]=i;
      }//for
    }//if para salvar o idenficador de pilha como d
    
    if(caracter =='r'){
      for(int i=0; i<10; i++){
        vetor[i]=rand() % 32000;
      }//for
    }//if para salvar o idenficador de pilha como r
  }//if para quando o identificador de pilha for c ou d ou r

  return caracter;
}//Preenche

void VerificaParametros(int argc){
  if(argc != 3){
    printf("Parametros invalidos\n");
    exit(1);
  }//if
}//VerificaParametros

void VerificaAberturaArquivo(FILE *arq1, FILE *arq2){
  if(arq1 == NULL||arq2 == NULL){
    printf("Erro ao abrir arquivos\n");
    exit(1);
  }//if
}//VerificaAberturaArquivo

//Função Principal
int main(int argc, const char *argv[]) {

  char iden;
  int quant;
  int *vet;
  char caracter;

  srand(time(NULL));

  /*VerificaParametros(argc);

  FILE* arq1 = fopen(argv[1], "r");
  FILE* arq2 = fopen(argv[2], "w");
  */
  FILE* arq1 = fopen("input1.txt", "r");
  FILE* arq2 = fopen("output1.txt", "w");

  VerificaAberturaArquivo(arq1, arq2);

  iden = identifica(arq1, arq2, &quant);

  vet = gerador(quant);

  caracter = Preenche(vet, quant, iden);

  Imprimir(vet, quant, 0, quant, caracter, arq2);

  finalizaarq(arq1, arq2);
  return 0;
}//main
