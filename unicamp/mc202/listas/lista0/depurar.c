/* ------------------------------------------------------------------
   MC202 - Estruturas de Dados - 2s2026
   Laboratorio 00 - Exercicio 4: caca aos erros

   Este programa DEVERIA ler tres notas, calcular a media e dizer se o
   aluno foi aprovado (media maior ou igual a 5,0). Ele contem TRES
   erros: dois impedem a compilacao e um compila normalmente, mas
   produz resposta errada em pelo menos um caso.

   Sua tarefa: encontrar e corrigir os tres erros, sem mudar a logica
   pretendida do programa.

   Compile com:  gcc -Wall -Wextra -o depurar depurar.c
   Teste com:    echo "5 5 5" | ./depurar     (deve dizer Aprovado)
                 echo "4 5 6" | ./depurar     (deve dizer Aprovado)
                 echo "2 3 4" | ./depurar     (deve dizer Reprovado)
   ------------------------------------------------------------------ */

#include <stdio.h>

#define MEDIA_MINIMA 5.0

int main(void)
{
  float n1, n2, n3;
  float media;

  printf("Digite as tres notas: ");
  scanf("%f %f %f", &n1, &n2, &n3);

  media = (n1 + n2 + n3) / 3;

  printf("Media: %.2f\n", media);

  if (media >= MEDIA_MINIMA)
    printf("Aprovado\n");
  else
    printf("Reprovado\n");

  return 0;
}