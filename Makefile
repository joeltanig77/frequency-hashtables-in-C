CPP = gcc
FLAGS = -Wall -pedantic -g

EXEC = wordpairs
OBJS = main.o getWord.o hashTable.o crc64.o

default:${EXEC}

clean:
	rm -f ${EXEC}
	rm -f *.o

bug: ${EXEC}
	gdb -tui --args ./${EXEC} -44 gettysburg.txt

valgrind: ${EXEC}
	valgrind --leak-check=full --track-origins=yes ./${EXEC} -44 gettysburg.txt

run: ${EXEC}
	./${EXEC} -44 gettysburg.txt

${EXEC}:${OBJS}
	${CPP} ${FLAGS} -o ${EXEC} ${OBJS}

.c.o:
	${CPP} ${FLAGS} -c $<

main.o: main.c crc64.c getWord.h crc64.h
hashtable.o: getWord.c crc64.c getWord.h crc64.h
