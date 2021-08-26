CPP = gcc
FLAGS = -Wall -pedantic -g

EXEC = freq
OBJS = main.o getWord.o hashTable.o

default:${EXEC}

clean:
	rm -f ${EXEC}
	rm -f *.o

valgrind: ${EXEC}
	gdb -tui ./${EXEC}

run: ${EXEC}
	./${EXEC} test.txt

${EXEC}:${OBJS}
	${CPP} ${FLAGS} -o ${EXEC} ${OBJS}

.c.o:
	${CPP} ${FLAGS} -c $<

main.o: main.c crc64.c getWord.h crc64.h
hashtable.o: getWord.c getWord.h
