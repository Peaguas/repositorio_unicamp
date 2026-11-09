'''
Leia um caractere maiúsculo, que indica uma operação que deve ser realizada e uma matriz M[12][12]. Em seguida, calcule e mostre 
a soma ou a média considerando somente aqueles elementos que estão na área inferior da matriz, conforme ilustrado abaixo (área verde).

Entrada
A primeira linha de entrada contem um único caractere Maiúsculo O ('S' ou 'M'), indicando a operação (Soma ou Média) 
que deverá ser realizada com os elementos da matriz. Seguem os 144 valores de ponto flutuante de dupla precisão (double) 
que compõem a matriz.

Saída
Imprima o resultado solicitado (a soma ou média), com 1 casa após o ponto decimal.
'''
def cria_matriz(i,j):
    matriz = []    
    linha = [0]*i
    for coluna in range(j):
        matriz.append(linha)
    return matriz

op = input()
soma = 0
media = 0
matriz=cria_matriz(12,12)

for i in range(len(matriz)):
    for j in range(len(matriz[i])):
        n = float(input())
        matriz[i][j]=n

for i in matriz:
    for j in matriz[i]:
        if i+j>=12:
            soma+=matriz[i][j]
media = soma/30

if op=='S':
    print(f'{soma:.1f}')
elif op=="M":
    print(f'{media:.1f}')