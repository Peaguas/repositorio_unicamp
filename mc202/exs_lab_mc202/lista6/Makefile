# MC202 - Estruturas de Dados - 2s2026
# Voce edita apenas main.c

CC     = gcc
CFLAGS = -Wall -g -std=c99

all: main

main: main.c
	$(CC) $(CFLAGS) -o main main.c

# executa com um caso de teste:  make teste CASO=testes/aberto1.in
# CASO = testes/aberto1.in
CASO = aberto1.txt
teste: main
	./main < $(CASO)

# roda TODOS os casos abertos e compara com a saida esperada
confere: main
	@for f in testes/aberto*.in; do \
	  b=`basename $$f .in`; \
	  if ./main < $$f | diff -q - testes/$$b.res > /dev/null 2>&1; \
	  then echo "OK     $$b"; \
	  else echo "FALHA  $$b   (esperado < / obtido >)"; \
	       ./main < $$f | diff -u testes/$$b.res - | head -30; fi; \
	done

# verificacao mais rigorosa dos avisos do compilador
rigoroso: main.c
	$(CC) -Wall -Wextra -pedantic -g -std=c99 -o main main.c

# procura vazamentos e acessos invalidos de memoria
valgrind: main
	valgrind --leak-check=full --show-leak-kinds=all ./main < $(CASO)

gdb: main
	gdb ./main

limpa:
	rm -f main *.o

.PHONY: all teste confere rigoroso valgrind gdb limpa
