C_FLAGS = -Wall -std=c99
EXECUTAVEL = gps

#regra geral
all: $(EXECUTAVEL)

#regra de ligação para o executável
gps: gps.o sumarizador.o lista_bicicleta.o fila.o inicio.o
	gcc gps.o sumarizador.o lista_bicicleta.o fila.o inicio.o -o gps

#regras de compilação
gps.o: gps.c sumarizador.h lista_bicicleta.h fila.h
	gcc -c gps.c $(C_FLAGS)

sumarizador.o: sumarizador.c sumarizador.h inicio.h
	gcc -c sumarizador.c $(C_FLAGS)

lista_bicicleta.o: lista_bicicleta.c lista_bicicleta.h fila.h inicio.h
	gcc -c lista_bicicleta.c $(C_FLAGS)

fila.o: fila.c fila.h sumarizador.h inicio.h
	gcc -c fila.c $(C_FLAGS)

inicio.o: inicio.c inicio.h
	gcc -c inicio.c $(C_FLAGS)

#remoção de arquivos temporários
clean:
	rm -f *~ *.o
purge:
	rm -f gps