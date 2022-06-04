#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
ED2021-2-AT02-Clinica-LeonardoBueno.c
*/

//[2] - Criar uma struct para armazenar o que vamos retirar do arquivo.
typedef struct{
  int codigo;
  char info[100];
}Armazena;

//[3] - Monto a estruturas (struct) do tipo da lista.
typedef struct Nolista *PtrNoLista;

//tipo Nolista
typedef struct Nolista{
  Armazena chave; //chave
  PtrNoLista proximo; //Ptr próximo No
  PtrNoLista anterior; //Ptr anterior No
}Nolista;

//tipo Lista
typedef struct{
  PtrNoLista primeiro; //Ptr primeiro No
  int qtdeElementos; //contador
}ListaOrdenada;

//[4.1] - Inicializar a lista ordenada.
void iniciaListaOrdenada(ListaOrdenada *lista){
  lista->primeiro = NULL; //primeiro = NULL
  lista->qtdeElementos = 0; //contador = 0;
}//iniciaListaOrdenada

//[6] - Fazer função para verificar se a lista ordenada esta cheia.
bool estaVaziaListaOrdenada(ListaOrdenada *lista){
  return(lista->primeiro == NULL); //ou return (lista->contador == 0);
}//estaVaziaListaOrdenada

//[7] - Codificar a lista ordenada para inserir sem retorno.
bool inserirListaOrdenada(ListaOrdenada *lista, Armazena *info){
  PtrNoLista novo; //Criar um PtrNoLista
  novo = (PtrNoLista) malloc(sizeof(Nolista)); //alocar memoria e copiar info no novo no

  novo->chave.codigo = info->codigo;//recebe o numero de implementação
  strcpy(novo->chave.info, info->info);//colocando informações do arquivo na fila

  //Verificando se alocou o nó.
  if(!novo){
    printf("Não foi alocado um no de lista\n");
    return false;
  }//if

  novo->chave.codigo = info->codigo;

  //[8] - Codificar a lista ordenada para primeira insercao ou menor do que o primeiro elemento da lista.
  if((estaVaziaListaOrdenada(lista))){
    novo->anterior = NULL;
    novo->proximo = NULL;
    lista->primeiro = novo;
  }//if

  //[9] - Percorrer e encontrar o ponto de inserção.
  else if(info->codigo < lista->primeiro->chave.codigo){
    novo->anterior = NULL;
    lista->primeiro->anterior = novo;
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;

  }else{

    PtrNoLista aux;
    aux = lista->primeiro;

    while(aux->proximo != NULL && info->codigo > aux->proximo->chave.codigo){
      aux = aux->proximo;
    }//while

    novo->proximo = aux->proximo;

    if(aux->proximo != NULL){
      aux->proximo->anterior = novo;
    }//if

    novo->anterior = aux;
    aux->proximo = novo;
  }//else

  lista->qtdeElementos++;
  return true;

}//inserirListaOrdenada

//[10] - Procurar na lista ordenada.
void procurarListaOrdenada(ListaOrdenada *lista, int pesquisa, FILE *arqsai){
  PtrNoLista percorre = lista->primeiro;

  //Dislocar até a posição do número na lista
  while(percorre != NULL && pesquisa > percorre->chave.codigo){
    percorre = percorre->proximo;
  }//while

  //Verificação para saber se o número pesquisado existe
  if(percorre == NULL || percorre->chave.codigo > pesquisa){
    fprintf(arqsai, "O elemento não foi encontrado!\n");
  }else{
    //Número encontrado e gravando informação do número
    fputc('{', arqsai);
    fprintf(arqsai, "%d", percorre->chave.codigo);
    fputs(percorre->chave.info, arqsai);
  }//else
}//procurarListaOrdenada

//[11] - Imprimir a lista ordenada.
void GravaListaArquivo(ListaOrdenada *lista, FILE *arqsai){
  PtrNoLista percorre;
  for(percorre = lista->primeiro; percorre!= NULL; percorre = percorre->proximo){
    fputc('{', arqsai);
    fprintf(arqsai, "%d", percorre->chave.codigo);
    fputs(percorre->chave.info, arqsai);
  }//for
}//GravaListaArquivo

//[11.1] - Imprimir a lista ordenada inversa
void imprimirInversa(ListaOrdenada *lista,  FILE *arqsai){
  PtrNoLista percorre = lista->primeiro;
  PtrNoLista aux = lista->primeiro;

  //while para chegar ao fim da lista
  while(percorre->proximo != NULL){
    percorre = percorre->proximo;
  }//while

  //gravando no arquivo de trás pra frente
  while(percorre != NULL){
    fputc('{', arqsai);
    fprintf(arqsai, "%d", percorre->chave.codigo);
    fputs(percorre->chave.info, arqsai);
    percorre = percorre->anterior;//voltando do ultimo pro primeiro pois o primeiro não tem anterior
  }//while
}//imprimirInversa

int main(int argc, const char *argv[]){

//variáveis
  int opcao, pesquisa;
  ListaOrdenada lista;
  Armazena info;
  iniciaListaOrdenada(&lista);

//[0] - Fazer verificação da quantidade de argc passados, se for != 3, o código nem roda.
  if(argc!=3){
    printf("Quantidade de paramentros invalidos!\n");
    return 1;
  }//if

//[1] - Abre os arquivos e valida se os mesmos foram abertos.
  FILE *arqen = fopen(argv[1],"r");
  FILE *arqsai = fopen(argv[2],"w");

  if(arqen == NULL || arqsai == NULL){
    printf("Erro na abertura do arquivo.\n");
    return 1;
  }//if

//[4] - Inicia a lista ordenada.
  iniciaListaOrdenada(&lista);

//[5] - Capturando as informações do arquivo.
  while(fgetc(arqen)=='{'){
    fscanf(arqen,"%d",&info.codigo);
    fgets(info.info, 100, arqen);

    inserirListaOrdenada(&lista, &info);

    fscanf(arqen,"%d",&opcao);
  }//while

  //Menu para as opções do programa
  switch(opcao){

    //imprimir em orde crescente
    case 1:
    printf("A opcao escolhida foi imnprimir em ordem crescente!\n");
    GravaListaArquivo(&lista, arqsai);
    break;

    //imprimir em ordem decrescente
    case 2:
    printf("A opcao escolhida foi imnprimir em ordem decrescente!\n");
    imprimirInversa(&lista, arqsai);
    break;

    //imprimir pesquisar
    case 3:
    fscanf(arqen, "%d", &pesquisa);
    printf("A opcao escolhida foi pesquisar o cadastro %d!\n", pesquisa);
    procurarListaOrdenada(&lista, pesquisa, arqsai);
    break;

    //Não existe a opção
    default:
    printf("A opcao escolhida nao existe!\n");
    break;

  }//switch

  //Fechando os arquivos
  fclose(arqen);
  fclose(arqsai);
}//main

//Pseudocódigo

//argc - é a qtd de parametros que roda. [ 3 parametros, sendo 0 main, 1 entrada.txt , 2 saida.txt]
//[0] - Fazer verificação da quantidade de argc passados, se for != 3, o código nem roda. -------------  [ok]
//[1] - Abre os arquivos e valida se os mesmos foram abertos.-------------  [ok]
//[2] - Criar uma struct para armazenar o que vamos retirar do arquivo (codigo, nome, sexo, peso e altura). -------------  [ok]
//[2.1] - Utilizo o fgetc para pegar o caracter do arquivo e ver qual lista será utilizada. ----------------
//[3] - Monto a estruturas (struct) do tipo da lista ao foi pega. -------------  [ok]
//[4] - Inicializar a lista ordenada. -------------  [ok]
//[5] - Capturando as informações do arquivo. -------------  [ok]
//[6] - Fazer função para verificar se a lista ordenada esta cheia. -------------  [ok]
//[7] - Codificar a lista ordenada para inserir sem retorno.-------------  [ok]
//[8] - Codificar a lista ordenada para primeira insercao ou menor do que o 1 elemento da lista.-------------  [ok]
//[9] - Percorrer e encontrar o ponto de inserção. -------------  [ok]
//[10] - Procurar na lista ordenada. -------------  [ok]
//[11] - Imprimir a lista ordenada. -------------  [ok]
