#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
ED2021-1-AT03-IndiceRemissivo-LeonardoBueno.c
*/

//<TIPOS DE ESTRUTURAS>

//Estrutura da Lista
typedef struct Nolista *PtrNoLista;//Renomeará o ponteiro

typedef struct Nolista{
  int pagina;
  PtrNoLista prox;
}NoLista;

typedef struct{
  PtrNoLista comeco;
  int qtdeElementos;
}ListaOrdenada;
//----------------------------------------------------------------

//Estrutura da struct auxiliar
typedef struct Auxiliar{
  char info[40];
  ListaOrdenada paginas;
}Auxiliar;
//-----------------------------------------------------------------

//----------------------------------------------------------------
//Estrutura da Arvore
//NoArvore* PtrNoArvore -> PtrNoArvore* (**NoArvore)
typedef struct NoArvore* PtrNoArvore;

//NoArvore (struct)
typedef struct NoArvore{
  Auxiliar x;
  PtrNoArvore esquerda;
  PtrNoArvore direita;
}NoArvore;
//----------------------------------------------------------------

//<FUNÇÕES>

//----------------------------------------------------------------
//LISTA
void InicialistaOrdenada(ListaOrdenada *lista){
    lista->comeco = NULL;
    lista->qtdeElementos = 0;
}//InicialistaOrdenada

bool estaVaziaListaOrdenada(ListaOrdenada *lista){
    return(lista->qtdeElementos == 0);
}//estaVaziaLista

void InsereListaOrdenada(ListaOrdenada *lista, int x){

    PtrNoLista auxiliar; //ponteiro auxiliar
    PtrNoLista novo; //ponteiro novo

    //Alocando memória para o ponteiro
    novo = (PtrNoLista)malloc(sizeof(NoLista));
    novo->pagina = x;

    //Verificando se está vazia e se o elemento é menor
    if(estaVaziaListaOrdenada(lista) || x < lista->comeco->pagina){
      novo->prox = lista->comeco;
      lista->comeco = novo;

    }else{
    //Verificando o ponto de adição do elemento
      auxiliar = lista->comeco;
      while(auxiliar->prox != NULL && x > auxiliar->prox->pagina){
        auxiliar = auxiliar->prox;
      }//while


      novo->prox = auxiliar->prox;
      auxiliar->prox = novo;

    }//else

    lista->qtdeElementos++;
}//InsereListaOrdenada

bool PesquisaListaOrdenada(ListaOrdenada *lista, int x){
    //Verificando se está vazia
    if(estaVaziaListaOrdenada(lista)){
      return false;
    }//if

    //Criando ponteiro para percorrer o caminho
    PtrNoLista percorrer;

    for(percorrer = lista->comeco; percorrer != NULL; percorrer = percorrer->prox){
      if(percorrer->pagina == x){
        return true;
      }//if
    }//for

    //Caso não encontre o elemento
    return false;
}//PesquisaListaOrdenada

//-----------------------------------------------------------------
//ARVORE
//Inicia arvore
void iniciaArvore(PtrNoArvore *node){
  (*node) = NULL;
}//iniciaArvore

//Está vazia
bool estaVaziaArvore(PtrNoArvore *node){
  return ((*node) == NULL);
}//estaVaziaArvore

//EmOrdem
void percursoEmOrdem(PtrNoArvore *node, FILE *arq2){
  //Ponteiro para percorrer
  PtrNoLista percorrer;

  if(*node == NULL){
    return;
  }//if

  percursoEmOrdem(&(*node)->esquerda, arq2);
  fprintf(arq2, "%s", (*node)->x.info);

  for(percorrer = (*node)->x.paginas.comeco; percorrer != NULL; percorrer = percorrer->prox){
    fprintf(arq2, ",%d", percorrer->pagina);
  }//for

  fprintf(arq2,"\n");

  percursoEmOrdem(&(*node)->direita, arq2);
}//percursoEmOrdem

bool InsereArvore(PtrNoArvore *node, char *x){
    if(*node == NULL){
      (*node) = malloc(sizeof(NoArvore));
      (*node)->direita = NULL;
      (*node)->esquerda = NULL;

      strcpy ((*node)->x.info,x);
      InicialistaOrdenada(&(*node)->x.paginas);

      return true;
    }//if

    if(strcmp((*node)->x.info, x) > 0){
      return(InsereArvore(&(*node)->esquerda, x));
    }else{
      return(InsereArvore(&(*node)->direita, x));
    }//else
  }//InsereArvore

bool ProcuraArvore(PtrNoArvore *node, char *p, int pagina){
    if(*node == NULL){
      return false;
    }//if

    if(strcmp((*node)->x.info, p) == 0 && !PesquisaListaOrdenada(&(*node)->x.paginas, pagina)){
      InsereListaOrdenada(&(*node)->x.paginas, pagina);
      return(true);
    }//if

    if(strcmp((*node)->x.info, p) > 0){
      return(ProcuraArvore(&(*node)->esquerda, p, pagina));
    }else{
      return(ProcuraArvore(&(*node)->direita, p, pagina));
    }//else

}//ProcuraArvore


int main(int argc, const char *argv[]){

  PtrNoArvore node;
  char *pesq;
  char primeiralinha[100], text[400];
  int p = 0;

  //Fazer verificação da quantidade de argc passados, se for != 3, o código nem roda.
      if(argc!=3){
        printf("Quantidade de parametros invalidos\n");
        return 1;
      }//if

    iniciaArvore(&node);
  //Abre os arquivos e valida se os mesmos foram abertos
      FILE *arq = fopen(argv[1],"r");
      FILE *arq2 = fopen(argv[2], "w");
      if(arq == NULL || arq2 == NULL){
        printf("Erro na abertura do arquivo.\n");
        return 1;
      }//if

      if(fscanf(arq, "%s[^\n]",&primeiralinha) == -1){
        printf("O arquivo está vazio!\n");
        fprintf(arq2,"O arquivo está vazio!\n");
        exit(1);
      }//if

      strlwr(primeiralinha);
      pesq = strtok(primeiralinha," .()<:,>:\n)");

      if(strcmp(pesq, "termos") !=0 && strcmp(pesq, "termo") != 0){
          printf("Formato errado!\n");
          fprintf(arq2, "Formato errado!\n");
          exit(1);
      }else{
          pesq = strtok(NULL," .()<:,>:\n)");

          while(pesq != NULL){
            InsereArvore(&node, pesq);
            pesq = strtok(NULL," .()<:,>:\n)");
          }//while
      }//else

      while(fgets(text,399,arq) != NULL){
        strlwr(text);
        pesq = strtok(NULL," .()<:,>:\n)");

        while (pesq != NULL){

          if(strcmp(pesq,"page") == 0){
            p++;
          }else{
            ProcuraArvore(&node, pesq, p);
          }//else

          pesq = strtok(NULL," .()<:,>:\n)");

        }//while
      }//while

      percursoEmOrdem(&node, arq2);
      printf("Sucesso!\n");

    fclose(arq);
    fclose(arq2);

  return 0;
}//main
