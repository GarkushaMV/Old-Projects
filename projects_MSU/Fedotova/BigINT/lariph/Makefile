# For debug
# CFLAGS = -L. -g -O0 -Wno-aggregate-return

CFLAGS = -L. -Wno-aggregate-return

COMPILER = g++
CC = $(COMPILER) $(CFLAGS)

OBJECTS = lariph.o lamult.o ladiv.o laitoa.o lmariph.o

all: liblariph.a

tests: latest lmtest

latest: latest.o liblariph.a
	$(CC) -o latest latest.o -llariph

lmtest: lmtest.o liblariph.a
	$(CC) -o lmtest lmtest.o -llariph

lariph.o: lariph.h lariph.cpp
	$(CC) -c lariph.cpp

latest.o: lariph.h latest.cpp
	$(CC) -c latest.cpp

lamult.o: lariph.h lamult.cpp
	$(CC) -c lamult.cpp

ladiv.o: lariph.h ladiv.cpp
	$(CC) -c ladiv.cpp

laitoa.o: lariph.h laitoa.cpp
	$(CC) -c laitoa.cpp

lmariph.o: lmariph.h lariph.h lmariph.cpp
	$(CC) -c lmariph.cpp

lmtest.o: lmariph.h lariph.h lmtest.cpp
	$(CC) -c lmtest.cpp

liblariph.a: $(OBJECTS)
	ar r liblariph.a $(OBJECTS)

clean:
	rm -rf *.o *.a *\~ latest lmtest
