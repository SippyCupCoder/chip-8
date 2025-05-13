EXEC = CHIP8

CC = g++

OPT = -O2

CFLAGS = -std=c++17 -Wall ${OPT} -lSDL2

${EXEC}:
	${CC} ${CFLAGS} *.cpp -o ${EXEC}

.PHONY: clean

clean:
	rm ${EXEC}