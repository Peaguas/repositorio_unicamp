# MC202 - Estruturas de Dados - 2s2026
# Laboratorio 00: ambiente, compilacao e depuracao
# Voce edita main.c (exercicios 1 a 3) e depurar.c (exercicio 4)

CC     = gcc
CFLAGS = -Wall -g -std=c99

all: main

main: main.c
	$(CC) $(CFLAGS) -o main main.c

# O programa depurar.c NAO compila de proposito: e o Exercicio 4.
# Depois de corrigir os tres erros, use "make depurar".
depurar: depurar.c
	$(CC) $(CFLAGS) -o depurar depurar.c

teste: main
	./main

confere: main
	@./main > /tmp/mc202_$$$$.txt 2>&1; \
	if diff -u saida_esperada.txt /tmp/mc202_$$$$.txt > /tmp/mc202_diff_$$$$.txt; \
	then echo "OK: a saida bate com a esperada."; \
	else echo "DIFERENCAS (esperado < / obtido >):"; cat /tmp/mc202_diff_$$$$.txt; fi; \
	rm -f /tmp/mc202_$$$$.txt /tmp/mc202_diff_$$$$.txt

rigoroso: main.c
	$(CC) -Wall -Wextra -pedantic -g -std=c99 -o main main.c

# Executa sob o depurador. Comandos uteis dentro do gdb:
#   break MaiorElemento   (para a execucao ao entrar na funcao)
#   run                   (inicia)
#   next / step           (avanca uma linha / entra na funcao)
#   print v[i]            (mostra o valor de uma expressao)
#   continue / quit
gdb: main
	gdb ./main

valgrind: main
	valgrind --leak-check=full --show-leak-kinds=all ./main

limpa:
	rm -f main depurar *.o

.PHONY: all teste confere rigoroso gdb valgrind limpa