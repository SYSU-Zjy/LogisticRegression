#all : hello another
 
#hello : hello.cpp
#    g++ -o $@ $<
 
#another : another.cpp
#    g++ -o $@ $<

CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lm

#LogisticRegression:LogisticRegression.o
#	${CC} ${CFLAGS} LogisticRegression.o ${CFLAGS} -o LogisticRegression
#$<依赖   $@目标

LogisticRegression:LogisticRegression.o
	${CC} ${CFLAGS} $< ${CFLAGS} -o $@

LogisticRegression.o:
	${CC} ${CFLAGS} -c LogisticRegression.cpp

clean:
	rm *.o
	rm LogisticRegression