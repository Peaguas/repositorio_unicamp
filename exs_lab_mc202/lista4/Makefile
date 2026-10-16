# MC202 - Estruturas de Dados - 2s2026
# Voce edita apenas main.c

CC     = gcc
CFLAGS = -Wall -g -std=c99

all: main

main: main.c
	$(CC) $(CFLAGS) -o main main.c

# compila e executa
teste: main
	./main

# compara a sua saida com a esperada (util antes de entregar)
confere: main
	@./main > /tmp/mc202_$$$$.txt 2>&1; \
	if diff -u gabarito/saida_esperada.txt /tmp/mc202_$$$$.txt > /tmp/mc202_diff_$$$$.txt; \
	then echo "OK: a saida bate com a esperada."; \
	else echo "DIFERENCAS (esperado < / obtido >):"; cat /tmp/mc202_diff_$$$$.txt; fi; \
	rm -f /tmp/mc202_$$$$.txt /tmp/mc202_diff_$$$$.txt

# verificacao mais rigorosa dos avisos do compilador
rigoroso: main.c
	$(CC) -Wall -Wextra -pedantic -g -std=c99 -o main main.c

# procura vazamentos e acessos invalidos de memoria
valgrind: main
	valgrind --leak-check=full --show-leak-kinds=all ./main

# executa sob o depurador
gdb: main
	gdb ./main

limpa:
	rm -f main *.o

.PHONY: all teste confere rigoroso valgrind gdb limpa
