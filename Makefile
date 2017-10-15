CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lm

LogisticRegression:LogisticRegression.o
	${CC} ${CFLAGS} LogisticRegression.o ${CFLAGS} -o LogisticRegression

LogisticRegression.o:
	${CC} ${CFLAGS} -c LogisticRegression.cpp

clean:
	rm *.o
	rm LogisticRegression