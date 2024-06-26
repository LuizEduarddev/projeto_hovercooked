all: program

program: main_file.o pedidos.o preparo.o pronto.o tela.o
	gcc -o programa main_file.o pedidos.o preparo.o pronto.o tela.o -lncurses
	rm -f main_file.o pedidos.o preparo.o pronto.o tela.o

pedidos.o: pedidos.c pedidos.h
	gcc -c pedidos.c -o pedidos.o -lncurses

preparo.o: preparo.c preparo.h
	gcc -c preparo.c -o preparo.o -lncurses

pronto.o: pronto.c pronto.h
	gcc -c pronto.c -o pronto.o -lncurses

tela.o: tela.c tela.h
	gcc -c tela.c -o tela.o -lncurses

main_file.o: main_file.c tela.h
	gcc -c main_file.c -o main_file.o -lncurses

clean:
	rm -rf *.o *~ programa
