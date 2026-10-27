/*
Criar uma matriz n*n FEITO
Encher aleatoriamente com os numeros de 1 ate n*n FEITO
Permitir input de chute FEITO
Esconder depis de uns certo tempo FEITO
Melhorar display FEITO
Debugar para matrizes < 1 FEITO
Documentar tudo certinho
Tirar ambiguidades
Aceitar outros tipos de input
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <windows.h>
    
#define TEMPO_ESPERA( segundos ) Sleep( (segundos) * 1000 )
#define LIMPAR_TELA "cls"

//============================================ Aloca espaços na memoria =======================================

int **CriaMatriz(int nlin, int ncol){
    int **m = (int **)calloc(nlin, sizeof(int *));

    for (int l = 0; l < nlin; l++){
        m[l] = (int *)calloc(ncol, sizeof(int));
    }
    return m;
}

void DestroiMatriz (int ***m, int nlin, int ncol){
    if((*m)!=NULL){
        for(int l=0; l < nlin; l++){
            free((m[l]));
            m[l] = NULL;
        }
        free((*m));
        (*m) = NULL;
    }
}

int *CriaVetor(int tam){
    int *v = (int *)calloc(tam, sizeof(int));
    return v;
}

void DestroiVetor(int **v, int n){
    if ((*v)!=NULL){
        free(*v);
        *v = NULL;
    }
}

//==================================================================================================

void EmbaralhaVetor(int *v, int tam){
    srand(time(NULL)); //cria semente de numeros aleatoria
    
    for (int i = 0; i<tam; i++){
        int coef_troca = rand() % tam; //aleatoriza coef entre 0 e tam pra trocar
        int temp = v[i]; //guarda valor de v em i
        v[i] = v[coef_troca]; //troca pelo aleatorio
        v[coef_troca] = temp; //recupera valor
    }

}

void *VetorAleatorio(int n){
    if(n<1){
        return 0; //Vetor invalido
    }

    int tam = n*n;
    int *v = CriaVetor(tam); 

    for (int i=0; i<tam; i++){
        v[i] = (int) i+1; //cria vetor linear de 1 ate n^2
    }

    EmbaralhaVetor(v, tam);

    return v;
}


int **MatricionaVetor(int* v, int nlin, int ncol){
    /*Transforma vetor linear em matriz*/

    int **m = CriaMatriz(nlin, ncol);
    
    for (int i=0; i<nlin*ncol; i++){
        m[i/ncol][i%ncol] = v[i];
    }
    return m;
}

void ImprimeVetorMatricionado(int *v, int n){
    /*Imprime o vetor gradeado bonitinho*/

    /*printf("  ");
    for (int i=0; i<n; i++){ \\tentativa de numerar linhas e colunas
        printf("  %02d  ", i+1);
    }*/
    printf("\n");
    printf("  ");
    for (int i=0; i<n; i++){
        printf("%c ", 43);
        printf("%c%c", 61, 61); //imprime o teto
        printf(" %c", 43);
    }
    printf("\n");
    printf("  ");
    for (int i=1; i<(n*n)+1; i++){
        printf("%c", 124);
        printf(" %02d ", v[i-1]); //imprime os numeros e as paredes
        printf("%c", 124);
        if (i%n == 0){
            printf("\n");
            printf("  ");
            for (int i=0; i<n; i++){
                printf("%c ", 43);
                printf("%c%c", 61, 61); //imprime o chao
                printf(" %c", 43);
            }
            printf("\n");
            printf("  ");
        }
    }
    printf("\n");
}

//======================== obseleto, imprime sem grade =========================
/*void ImprimeVetMatGradeado(int *v, int n){
    int nlin=0, ncol=0;
    for (int i=1; i<(n*n)+1; i++){
        printf(" %02d ", v[i-1]);
        printf("%c", 124);
        if (i%n == 0){
            printf("\n");
        }
    }
    printf("\n");
}*/

//========================== pra imprimir a matriz m, mas é desnecessário ===========================
/*void ImprimeMatriz(int **m, int nlin, int ncol){
  for(int l=0; l < nlin; l++){
    for(int c=0; c < ncol; c++)
      printf("%03d ", m[l][c]);
    printf("\n");
  }
}*/

int Chute(int **m, int linha, int coluna, int num, int n){
    if (linha<=0 || linha>n || coluna<=0 || coluna>n){
        printf("Coordenadas fora do escopa aceitavel.\n");
        return 0;
    } else if (m[linha-1][coluna-1] == (int) num){
        printf("Certo!\n");
        return 1;
    } else{
        printf("Errado...\n");
        return 0;
    }
}

int main(){
    system("cls");
    int *v = NULL;
    int **m = NULL;
    int n, linha, coluna; 
    int num = 0;

    printf("Digite o tamanho da matriz: ");
    scanf("%d", &n);
    printf("\n");
    
    //caso matriz invalida
    while (n<=0 || sizeof(n)!=(4ULL)){
        printf("Insira um inteiro maior que 0\n");
        printf("Digite o tamanho da matriz: ");
        scanf("%d", &n);
        printf("\n");
    }

    int tam = n*n;
    
    v = VetorAleatorio(n);
    m = MatricionaVetor(v, n, n);
    ImprimeVetorMatricionado(v, n);

    TEMPO_ESPERA(30);
    system("cls");

    /*int verifica = 1;
    while(verifica && num<tam){
        num++;
        printf("Insira a posicao do numero %d no formato 'linha coluna': ", num, n);
        scanf("%d %d", &linha, &coluna);
        verifica = Chute(m, linha, coluna, num, n);
    }

    if (num == tam){
        printf("Parabens, voce ganhou!\nAumente a dificuldade\n");
    } else{
        printf("Tente de novo.\n");
    }
    ImprimeVetorMatricionado(v, n);*/
    
    DestroiVetor(&v, tam);
    DestroiMatriz(&m, n, n);
    return 0;
}