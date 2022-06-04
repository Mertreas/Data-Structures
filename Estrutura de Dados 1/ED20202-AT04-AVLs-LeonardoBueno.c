#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

//<TIPOS DE ESTRUTURAS>

//Estrutura da Arvore AVL
typedef struct NoAVL *PtrNoAVL;//Renomeará o ponteiro

typedef struct NoAVL {
    int chave;
    PtrNoAVL dir;
    PtrNoAVL esq;
    //fator de balanceamento
    int altura;
} NoAVL;
//------------------------------------------------------------------

//Estrutura de Fila Dinâmica
typedef struct NoFila *PtrNoFila;//Renomeará o ponteiro

typedef struct NoFila{
  int chave;
  PtrNoFila prox;
} NoFila;

typedef struct {
  PtrNoFila comeco;
  PtrNoFila fim;
  int qtdeElementos;
} FilaDinamica;

//------------------------------------------------------------------

//<FUNÇÕES>

//------------------------------------------------------------------
//LISTA
void IniciaFilaOrdenada(FilaDinamica *fila){
  fila->comeco = NULL;
  fila->fim = NULL;
  fila->qtdeElementos = 0;
}//void IniciaFilaOrdenada

bool estaVaziaListaOrdenada(FilaDinamica *fila){
  return(fila->qtdeElementos == 0);
}//estaVaziaListaOrdenada

void InsereListaOrdenada(FilaDinamica *fila, int x){

  PtrNoFila auxiliar;//ponteiro de nó de fila

  //Alocando memória para o ponteiro
  auxiliar = (PtrNoFila)malloc(sizeof(NoFila));
  auxiliar->chave = x;

  //Verificando se está vazia
  if (estaVaziaListaOrdenada(fila)){
    //começo e fim apontam pra auxiliar e proximo pra NULL
    fila->comeco = auxiliar;
    fila->fim = auxiliar;
    auxiliar->prox = NULL;

  }else{
    //auxiliar proximo é nulo, copia prox do fim da fila pra auxiliar e fim de fila recebe auxiliar
    auxiliar->prox = NULL;
    fila->fim->prox = auxiliar;
    fila->fim = auxiliar;
  }

  //incrementando elemento
  fila->qtdeElementos++;
}//InsereListaOrdenada

int DesenfileirarFilaDinamica(FilaDinamica *fila){
  int ret = -999;
  //ptr auxiliar (aux)
  PtrNoFila auxiliar;

  //nao posso remover se a fila estiver vazia
  if (!estaVaziaListaOrdenada(fila)){
    //auxiliar recebe o inicio da fila
    auxiliar = fila->comeco;
    //atualizar o início pro proximo dele
    fila->comeco = fila->comeco->prox;
    //copiar as informações pro usuário
    ret = auxiliar->chave;
    //desalocar memoria auxiliar
    free(auxiliar);
    //desencrementa qtdeElementos
    fila->qtdeElementos--;

  }else{
    printf("Warning: não removeu elementos pois a fila está vazia\n");
  }
  return(ret);
}//DesenfileirarFilaDinamica
// -------------------------------------------------------------

//FUNÇÕES ARVORE AVL
void iniciaAVL(PtrNoAVL *node){
  *node = NULL;
}//iniciaAVL

int ProfundidadeArvoreAVL(PtrNoAVL *node) {
  if ((*node) == NULL) return 0;

  else {

    int profunEsq = ProfundidadeArvoreAVL(&(*node)->esq);
    int profunDir = ProfundidadeArvoreAVL(&(*node)->dir);

    if (profunEsq > profunDir){
      return(profunEsq + 1);
    }else{
      return(profunDir + 1);
    }//else
  }//else
}//ProfundidadeArvoreAVL

int alturaArvoreAVL(PtrNoAVL node){
  if(node == NULL) return (0);
  else return ((node)->altura);
}//alturaArvoreAVL

int atualizaAltura(PtrNoAVL esq, PtrNoAVL dir){

  int ae = alturaArvoreAVL(esq);
  int ad = alturaArvoreAVL(dir);

  if(ae > ad) {
    return(ae + 1);
  } else {
    return(ad + 1);
  }//else
}//atualizaAltura

void DestruirArvoreAVL(PtrNoAVL *node){

  if((*node) != NULL ) {
    DestruirArvoreAVL( &(*node)->esq);
    DestruirArvoreAVL( &(*node)->dir);
    free(*node);
    *node = NULL;
  }//if
}//DestruirArvoreAVL

void rotacaoSimplesEsquerda (PtrNoAVL *node){
  printf("Rotacao simples para esquerda, com node: %d\n", (*node)->chave);

  PtrNoAVL u = (*node)->dir;
  (*node)->dir = u->esq;
  u->esq = (*node);

  //atualizar a altura dos nós modificados (node, u)
  (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);
  u->altura = atualizaAltura(u->esq, u->dir);

  //autualizacao da referencia do node
  (*node) = u;
}//rotacaoSimplesEsquerda

void rotacaoSimplesDireita (PtrNoAVL *node){
  printf("Rotacao simples para direita, com node: %d\n", (*node)->chave);

  PtrNoAVL u = (*node)->esq;
  (*node)->esq = u->dir;
  u->dir = (*node);

  //atualizar a altura dos nós modificados (node, u)
  (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);
  u->altura = atualizaAltura(u->esq, u->dir);

  //autualizacao da referencia do node
  (*node) = u;
}//rotacaoSimplesDireita

void rotacaoDuplaEsquerda (PtrNoAVL *node){
  printf("Rotacao dupla para esquerda, com node: %d\n", (*node)->chave);

  PtrNoAVL u, v;
  u = (*node)->dir;
  v = u->esq;

  (*node)->dir = v->esq;
  u->esq = v->dir;
  v->esq = (*node);
  v->dir = u;

  //atualizar a altura dos nós modificados (node, u, v)
  (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);
  u->altura = atualizaAltura(u->esq, u->dir);
  v->altura = atualizaAltura(v->esq, v->dir);

  //autualizacao da referencia do node
  (*node) = v;
}//rotacaoDuplaEsquerda

void rotacaoDuplaDireita (PtrNoAVL *node){
  printf("Rotacao dupla para direita, com node: %d\n", (*node)->chave);

  PtrNoAVL u, v;
  u = (*node)->esq;
  v = u->dir;

  (*node)->esq = v->dir;
  u->dir = v->esq;

  v->dir = (*node);
  v->esq = u;

  //atualizar a altura dos nós modificados (node, u, v)
  (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);
  u->altura = atualizaAltura(u->esq, u->dir);
  v->altura = atualizaAltura(v->esq, v->dir);

  //autualizacao da referencia do node
  (*node) = v;
}//rotacaoDuplaDireita

void AplicarRotacoes(PtrNoAVL *node){

  int ad = alturaArvoreAVL((*node)->dir);
  int ae = alturaArvoreAVL((*node)->esq);

  // Verificar se é rotacao para direita
  if(ae > ad) {
    PtrNoAVL temp = (*node)->esq;
    int temp_ad = alturaArvoreAVL(temp->dir);
    int temp_ae = alturaArvoreAVL(temp->esq);
    // temp_ae > ou >= temp_ad
    if(temp_ae > temp_ad) {
      rotacaoSimplesDireita(&(*node));
    } else {
      rotacaoDuplaDireita(&(*node));
    }//else
  }//if
  // Senao é rotacao para esquerda
  else { //(ad > ae) rotacao para esq
    PtrNoAVL tmp2 = (*node)->dir;
    int tmp2_ad = alturaArvoreAVL(tmp2->dir);
    int tmp2_ae = alturaArvoreAVL(tmp2->esq);

    if(tmp2_ad > tmp2_ae){
      rotacaoSimplesEsquerda(&(*node));
    } else {
      rotacaoDuplaEsquerda(&(*node));
    }//else
  }//else
}//AplicarRotacoes

bool InserirAVL(PtrNoAVL *node, int x){

  //condicao final da recusao (positiva)
  if((*node) == NULL) {
    (*node) = (PtrNoAVL)malloc(sizeof(NoAVL));
    (*node)->dir = (*node)->esq = NULL;
    (*node)->chave = x;
    (*node)->altura = 1;
    return true;
  }//if

  //elemento ja existe
  if((*node)->chave == x) return false;

  bool auxiliar;

  // 3. Laço de chamadas recusivas
  if(x < (*node)->chave) {
    auxiliar = InserirAVL(&(*node)->esq, x);
  } else {
    auxiliar = InserirAVL(&(*node)->dir, x);
  }//else

  // Daqui para baixo começa o codigo só tem na AVL
  // Se o auxiliar for falso, nao houve mudança na arvore
  if(!auxiliar) return (false);

  // Se houve modificacao na arvore
  // Precisamos checar o desbalanceamento
  int ae;
  int ad;

  // Calculando as alturas das sub-arvores
  ae = alturaArvoreAVL((*node)->esq);
  ad = alturaArvoreAVL((*node)->dir);

  // Verificando desbalanceamento
  if((ad - ae) == +2 || (ad - ae) == -2) {
    // desbalancemaneto
    AplicarRotacoes(&(*node));
  }//if

  // ajuste da altura do no corrente
  (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);
  return(true);
}//InserirAVL

PtrNoAVL maxAVL (PtrNoAVL *node) {

  PtrNoAVL auxiliar;

  if((*node)->dir == NULL) {
    auxiliar = (*node);
    (*node) = (*node)->esq;
    return(auxiliar);
  }//if

  return(maxAVL(&(*node)->dir));
}//maxAVL

PtrNoAVL minAVL (PtrNoAVL *node) {

  PtrNoAVL ret;

  if((*node)->esq == NULL) {
    ret = (*node);
    (*node) = (*node)->dir;
    return(ret);
  }//if

  return(minAVL(&(*node)->esq));
}//minAVL

bool RemoveAVL(PtrNoAVL *node, int chave, char opcao) {

  bool auxiliar;
  int altura_esq, altura_dir;

  if((*node) == NULL) {
    printf("Não possui elemento %d para ser removido!\n", chave);
    return (false);
  }//if

  //remoção
  if((*node)->chave == chave) {

    PtrNoAVL tmp = (*node);
    //subnode esquerdo é nulo (cai aqui se for folha)
    if((*node)->esq == NULL) {
      (*node) = (*node)->dir;
    }//if

    //subnode direito é nulo (poderia cair aqui)
    else if((*node)->dir == NULL) {

      (*node) = (*node)->esq;

    } else {

        if (opcao == 'e') {
          tmp = maxAVL(&(*node)->esq);
        }else{
          tmp = minAVL(&(*node)->dir);
        }//if

      (*node)->chave = tmp->chave;
    }//else

    free(tmp);
    return true;
  }//if

  if((*node)->chave > chave){
    auxiliar = RemoveAVL(&(*node)->esq, chave,opcao);
  } else {
    auxiliar = RemoveAVL(&(*node)->dir, chave,opcao);
  }//else

  if(auxiliar == false) return (false);
  else {
    altura_esq  = ProfundidadeArvoreAVL(&(*node)->esq);
    altura_dir = ProfundidadeArvoreAVL(&(*node)->dir);

    if((altura_esq - altura_dir) == 2 )
      AplicarRotacoes(&(*node));

    (*node)->altura = atualizaAltura((*node)->esq, (*node)->dir);
    return(true);
  }//else
}//RemoveAVL

void EscrevernoArquivo(PtrNoAVL *node, int nivel, FILE* arqsai){
  if ((*node)!=NULL && nivel == 0) {

    int ae = alturaArvoreAVL((*node)->esq);
    int ad = alturaArvoreAVL((*node)->dir);

    fprintf(arqsai, " %d (%d),", (*node)->chave, ad - ae);

  }else if((*node) != NULL){

    EscrevernoArquivo(&(*node)->esq, nivel - 1, arqsai);
    EscrevernoArquivo(&(*node)->dir, nivel - 1, arqsai);

  }//else if
}//EscreveNoArquivo

void GeraArquivo(PtrNoAVL *node, FILE* arqsai){

  int altura = ProfundidadeArvoreAVL(&(*node));

  for (int i = 0; i < altura; i++) {

    EscrevernoArquivo(&(*node),i,arqsai);
    fprintf(arqsai, "\n" );

  }//for
}//GeraArquivo

//------------------------------------------------------------------------------
int main(int argc, const char * argv[]){

  PtrNoAVL node;
  FilaDinamica fila;
  int num;
  char* numero;
  char op;
  char primeiralinha[100];

  //Fazer verificação da quantidade de argc passados, se for != 3, o código nem roda.
      if(argc!=3){
        printf("Quantidade de parametros invalidos\n");
        return 1;
      }//if

  FILE *arqen = fopen(argv[1], "r");
  FILE *arqsai = fopen(argv[2], "w");

  if(arqen == NULL){
    printf("Erro ao abrir o arquivo de entrada\n");
    exit(1);
  }//if

  if(arqsai == NULL){
    printf("Erro ao abrir o arquivo de saida\n");
    exit(1);
  }//if

  //Iniviando AVL e Fila
  iniciaAVL(&node);
  IniciaFilaOrdenada(&fila);

  //Lendo a primeira linha
  fgets(primeiralinha, 99, arqen);

  numero = strtok(primeiralinha,",");

  while(numero != NULL){

    num = strtol(numero, NULL, 10);
    InserirAVL(&node, num);
    numero = strtok(NULL,",");

  }//while

  //Lendo a segunda linha
  fgets(primeiralinha, 99, arqen);

  numero = strtok(primeiralinha,",");

  while (numero != NULL){

    num=strtol(numero, NULL, 10);
    InsereListaOrdenada(&fila, num);
    numero = strtok(NULL,",");

  }//while

  op = fgetc(arqen);
  op = tolower(op);

  if (op!='e' && op!= 'd') {

    fprintf(arqsai, "Arquivo é inválido!\n");
    exit(1);

  }//if

  fprintf(arqsai, "[*]antes\n");

  //Imprimindo o inicio
  GeraArquivo(&node, arqsai);

  while (!estaVaziaListaOrdenada(&fila)) {

    num = DesenfileirarFilaDinamica(&fila);
    RemoveAVL(&node, num, op);

  }//while

  fprintf(arqsai, "\n[*]depois\n");
  GeraArquivo(&node, arqsai);

  printf("\n\nTudo certo, o arquivo de saida foi gerado com sucesso!\n");

  DestruirArvoreAVL(&node);
  return 0;
}//main
