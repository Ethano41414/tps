CC=gcc
CFLAGS=-Wall -Wextra -g
LDFLAGS=-lm
SRC=code.c
all:teZZt.h main main_tests polonian_calculator graphic_pcalculator
main:code.o main.o
	${CC} -o main code.o main.o ${LDFLAGS}
main_tests:code.o main_tests.o teZZt.o
	${CC} -o main_tests code.o main_tests.o teZZt.o ${LDFLAGS}
polonian_calculator:module.o code.o polonian_calculator.o
	${CC} -o polonian_calculator code.o module.o polonian_calculator.o ${LDFLAGS}
graphic_pcalculator:module.o code.o graphic_pcalculator.o
	${CC} -o graphic_pcalculator code.o module.o graphic_pcalculator.o ${LDFLAGS}
code.o:code.c code.h
	${CC} ${CFLAGS} code.c -c
module.o:module.c module.h
	${CC} ${CFLAGS} module.c -c
main.o:code.h teZZt.h main.c
	${CC} ${CFLAGS} main.c -c
main_tests.o:code.h teZZt.h main_tests.c
	${CC} ${CFLAGS} main_tests.c -c
polonian_calculator.o:code.h module.h polonian_calculator.c
	${CC} ${CFLAGS} polonian_calculator.c -c
graphic_pcalculator.o:code.h module.h graphic_pcalculator.c
	${CC} ${CFLAGS} graphic_pcalculator.c -c
teZZt.o:teZZt.h teZZt.c
	${CC} ${CFLAGS} -c teZZt.c
clean:
	rm -f *.gch teZZt.o main.o main_tests.o code.o 
teZZt.h:
	wget -nc https://gitlab.com/kiux/teZZt/-/raw/master/teZZt.c
	wget -nc https://gitlab.com/kiux/teZZt/-/raw/master/teZZt.h
update:teZZt.h
