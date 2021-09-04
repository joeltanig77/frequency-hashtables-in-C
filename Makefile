CPP = gcc
FLAGS = -Wall -pedantic -g

EXEC = wordpairs
OBJS = main.o getWord.o hashTable.o crc64.o readWordPairs.o sortHashTable.o

default:${EXEC}

clean:
	rm -f ${EXEC}
	rm -f *.o

bug: ${EXEC}
	gdb -tui --args ./${EXEC} -10 dracula.txt dracula.txt dracula.txt dracula.txt dracula.txt dracula.txt

valgrind: ${EXEC}
	valgrind -s --leak-check=full --track-origins=yes ./${EXEC} -10 dracula.txt dracula.txt dracula.txt dracula.txt dracula.txt dracula.txt

run: ${EXEC}
	./${EXEC} -10 dracula.txt dracula.txt dracula.txt dracula.txt dracula.txt dracula.txt

${EXEC}:${OBJS}
	${CPP} ${FLAGS} -o ${EXEC} ${OBJS}

.c.o:
	${CPP} ${FLAGS} -c $<

main.o: main.c crc64.c readWordPairs.c sortHashTable.c getWord.h crc64.h readWordPairs.h sortHashTable.h
hashtable.o: getWord.c crc64.c readWordPairs.c getWord.h crc64.h readWordPairs.h
readWordPairs.o: getWord.c readWordPairs.c getWord.h readWordPairs.h
sortHashTable.o: sortHashTable.c sortHashTable.h
