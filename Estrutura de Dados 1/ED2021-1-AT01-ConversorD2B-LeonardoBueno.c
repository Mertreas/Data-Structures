#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*
ED2021-1-AT01-ConversorD2B-LeonardoBueno.c
*/

//[2] - Criar uma struct para armazenar o que vamos retirar do arquivo ( caracter e números)
typedef struct{
    char tipo_pilha;
    float numero;
}Armazena;

//==============================================================================

//[3] - Monto a estruturas ( struct ) do tipo da pilha ao foi pega ( fazer uma pilha de cada vez para não se confundir)
//Pilha Estática

#define TAMANHO 100

typedef struct{
  //vetor de inteiros
  int array[TAMANHO];
  //controlar o topo
  int topo;
  //contador
  int qtdeElementos;
}PilhaEstatica;

//==============================================================================

//==============================================================================
//Pilha Dinâmica
typedef struct NoPilha *PonteiroNoPilha;

  typedef struct NoPilha{
    int chave;
    PonteiroNoPilha prox;
  }NoPilha;

  typedef struct{
    PonteiroNoPilha topo;
    //contador
    int qtdeElementos;
}PilhaDinamica;

//==============================================================================

//IniciaPilhaDinamica
void IniciaPilhaDinamica(PilhaDinamica *pd){
  pd->topo = NULL;
  pd->qtdeElementos = 0;
}

bool estavaziaPilhaDinamica(PilhaDinamica *pd){
  return(pd->qtdeElementos == 0);
}

//Empilha Pilha Dinâmica
void EmpilhaPilhaDinamica(PilhaDinamica *pd, int x){
  //passo 1
  PonteiroNoPilha Aux;
  //passo 2
  Aux = (PonteiroNoPilha)malloc(sizeof(NoPilha));
  //Colocando o valor do elemento no novo nó
  Aux->chave = x;
  //passo 4
  Aux->prox = pd->topo;
  //passo 5
  pd->topo = Aux;
  //passo 6
  pd->qtdeElementos++;
}

void imprimePilhaDinamica(PilhaDinamica *p){
  printf("{");
      //Ptr no de pilha para realizar o for de exibição da pilha
      PonteiroNoPilha ptr;
//ponteiro recebe o topo, roda enquanto não for NULL, aponta pro próximo até achar NULL e parar
        for(ptr=p->topo;ptr!=NULL;ptr=ptr->prox){
          printf("%d ",ptr->chave);
        }//for
  printf("}");
}//ImprimePilhaDinamica

int DesempilhaPd(PilhaDinamica *pd){

  int aux=-1;
    if(!estavaziaPilhaDinamica(pd)){
        PonteiroNoPilha Aux;

      Aux = pd->topo;

      aux = Aux->chave;

      pd->topo = pd->topo->prox;

      free(Aux);

      pd->qtdeElementos--;
    }else{
      printf("Warning: esta vazia\n");
    }
    return(aux);
}

//==============================================================================
//Funções para Pilha Estatica

//Inciaidno Pilha Estatica
void IniciaPilhaEstatica(PilhaEstatica *p){
  p->topo = 0;
  p->qtdeElementos = 0;
}//IniciaPilhaEstatica

//[7] - Fazer Funções para verificar se a pilha esta cheia ou vazia, pilhas Dinamicas nunca estarão cheias ( por causa do malloc)
bool estaVaziaPilhaEstatica(PilhaEstatica *p){
  return(p->topo == 0);
}

bool estaCheiaPilhaEstatica(PilhaEstatica * p){
  return(p->qtdeElementos == TAMANHO);
}

void EmpilhaPilhaEstatica(PilhaEstatica *p, int x){
  //Se não está cheia:
  if(!estaCheiaPilhaEstatica(p)){
    //inserir o elemento
    p->array[p->topo] = x;
    //incrementar o topo
    p->topo++;
    //incrementar quantidade de qtdeElementos
    p->qtdeElementos;
  }else{
    printf("O elemento nao foi inserido, pilha esta cheia\n");
  }//else
}

void imprimePilhaEstatica(PilhaEstatica *p){
  printf("Pilha Estatica = {");
      for(int i=0;i<p->array[p->topo-1];i++){
          printf("%d ",p->array[i]);
      }//for
  printf("}");
}//imprimePilhaEstatica

int DesempilhaPe(PilhaEstatica *p){
  int aux = - 1;

  if( !estaVaziaPilhaEstatica(p)){
    aux = p->array[p->topo-1];
    p->topo--;
    p->qtdeElementos--;
    }else{
      printf("Warning: nao removi, porque esta vazia\n");
      }//else

      return (aux);
  }
//==============================================================================

//==============================================================================
//Funções Gerais.

bool VerificaNumeroInteiro(float numero){
  int inteiro;
      inteiro=numero;
    return(inteiro!=numero);
}//VerificaNumeroInteiro


  //Converte(DesempilhaPd(&pd),&info,arq2);

void Converte(int removido_pilha,Armazena *info, FILE *arq2){

  PilhaEstatica peauxiliar;
  PilhaDinamica pdauxiliar;
//[cria 2 pilhas auxiliares (Estatica e dinamica)].  ------ [ok]
//[inicializar as 2 pilhas auxiliares (Estatica e dinamica)]
//[empilha o número convertido na pilha auxiliar ( pega o nmro convertido em binário e empilha ele na pilha)]
//Desempilha a pilha auxiliar e vai salvando no arquivo(desempilha a pilha auxiliar e salva o nmro em binário removido no arquivo).

  if(info->tipo_pilha == 'e'){
    IniciaPilhaEstatica(&peauxiliar);

  }else{
    IniciaPilhaDinamica(&pdauxiliar);

  }//else

  if(removido_pilha == 0){
    fprintf(arq2, "%d\n", removido_pilha);
  }else{
       while(removido_pilha > 0){
         int resto;
         resto = removido_pilha % 2;
         removido_pilha = removido_pilha / 2;

         if(info->tipo_pilha == 'e'){
           EmpilhaPilhaEstatica(&peauxiliar, resto);
         }else if(info->tipo_pilha=='d'){
          EmpilhaPilhaDinamica(&pdauxiliar, resto);
        }//else
      }//while
    }//else


    if(info->tipo_pilha == 'e'){

      while(!estaVaziaPilhaEstatica(&peauxiliar)){
      fprintf(arq2, "%d", DesempilhaPe(&peauxiliar));
      }//while
    fprintf(arq2,"\n");

    }else if(info->tipo_pilha =='d'){
      while(!estavaziaPilhaDinamica(&pdauxiliar)){
      fprintf(arq2, "%d", DesempilhaPd(&pdauxiliar));
      }//while
      fprintf(arq2,"\n");
    }//else
  }//Converte


//==============================================================================

int main(int argc,char *argv[]){
//váriaveis
    Armazena info;
    PilhaEstatica pe;
    PilhaDinamica pd;

//[0] - Fazer verificação da quantidade de argc passados, se for != 3, o código nem roda.
    if(argc!=3){
      printf("Quantidade de parametros invalidos\n");
      return 1;
    }//if


//[1] - Abre os arquivos e valida se os mesmos foram abertos
    FILE *arq = fopen(/*argv[1]*/"entrada02.txt","r");
    FILE *arq2 = fopen(/*argv[2]*/"saida02.txt", "w");
    if(arq == NULL || arq2 == NULL){
      printf("Erro na abertura do arquivo.\n");
      return 1;
    }//if

    info.tipo_pilha = fgetc(arq);

    //[2.1] - Utilizo o fgetc para pegar o caracter do arquivo e ver qual pilha será utilizada
     if(info.tipo_pilha == 'e'){
    //[6] - Inicializar a pilha ( Estatica ou Dinamica )
        IniciaPilhaEstatica(&pe);
    }else if(info.tipo_pilha =='d'){
      IniciaPilhaDinamica(&pd);
    }else{
      printf("Arquivo invalido\n");
      return 1;
    }

  while(!feof(arq)){
      fscanf(arq,"%f\n",&info.numero);
        if(VerificaNumeroInteiro(info.numero)){
          printf("Numero invalido\n");
          return 1;
        }else{
            if(info.tipo_pilha=='e'){
              EmpilhaPilhaEstatica(&pe,info.numero);
            }if(info.tipo_pilha=='d'){
              EmpilhaPilhaDinamica(&pd,info.numero);
            }//if
        }//else
  }//while

//[10] - Codificar a pilha que faz a impresão da pilha, para verificar se foi implementado corretamente.
    if(info.tipo_pilha=='e'){
        imprimePilhaEstatica(&pe);
          while(!estaVaziaPilhaEstatica(&pe)){
          Converte(DesempilhaPe(&pe),&info,arq2);
          }//while
    }else if(info.tipo_pilha=='d'){
        imprimePilhaDinamica(&pd);
        while(!estavaziaPilhaDinamica(&pd)){
          Converte(DesempilhaPd(&pd),&info,arq2);
    }//while
  }//else if

    fclose(arq);
    fclose(arq2);
  return 0;
}//main

//Pseudocódigo

//argc - é a qtd de parametros que roda. [ 3 parametros, sendo 0 main, 1 entrada.txt , 2 saida.txt]
//[0] - Fazer verificação da quantidade de argc passados, se for != 3, o código nem roda. -------------  [ok]
//[1] - Abre os arquivos e valida se os mesmos foram abertos.-------------  [ok]
//[2] - Criar uma struct para armazenar o que vamos retirar do arquivo ( caracter e números). -------------  [ok]
//[2.1] - Utilizo o fgetc para pegar o caracter do arquivo e ver qual pilha será utilizada. ----------------  [ok]
//[3] - Monto a estruturas ( struct ) do tipo da pilha ao foi pega ( fazer uma pilha de cada vez para não se confundir)-------------  [ok]
//[4] - Fazer condições aos quais irão atender ao caracter pego, if e else-------------  [ok]
//[5] - Implementar uma pilha de cada vez para não ter conflito.-------------  [ok]
//[6] - Inicializar a pilha ( Estatica ou Dinamica ).-------------  [ok]
//[7] - Fazer Funções para verificar se a pilha esta cheia ou vazia, pilhas Dinamicas nunca estarão cheias ( por causa do malloc)-------------  [ok]
//[8] - Pegar numero a numero do arquivo, enquanto o arquivo não chega no FIM, (feof).-------------  [ok]
//[9] - Após pegar o número, utilizar if e else para ver em qual pilha será implementado.-------------  [ok]
//[10] - Codificar a pilha que faz a impresão da pilha, para verificar se foi implementado corretamente.-------------  [ok]
//[11] - Codificar a pilha que faz a inserção do elemento, passar numero e váriavel da pilha para a função.-------------  [ok]
//[12] - Fazer função que desempilha a respectiva pilha e retorna o número removido.-------------  [ok]
//[13] - Pegar esse número removido, fazer uma função para transforma-lo em binário.-------------  [ok]
//[14] - Após transforma-lo em binário, Inserir esse elemento em binário em uma pilha auxiliar do mesmo formato ao qual foi removido.-------------  [ok]
//[15] - Desempilhar a pilha auxiliar e salva-lá em um arquivo.-------------  [ok]
