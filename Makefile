CC = cc
CFLAGS = -g -02 -w

EXE_FILE = fizzbuzz
SRC = fizzbuzz.c

${EXE_FILE}: ${SRC}
	${CC} ${SRC} -o ${EXE_FILE}

clean:
	rm -f ${EXE_FILE}
