EXEC = CHIP8

CC = g++

OPT = -O2

CFLAGS = -std=c++17 -Wall ${OPT}

${EXEC}:
	${CC} ${CFLAGS} -Isrc/include -Lsrc/lib main.cpp chip8.cpp -lmingw32 -lSDL2main -lSDL2 -o ${EXEC}

.PHONY: clean

clean:
	rm ${EXEC}