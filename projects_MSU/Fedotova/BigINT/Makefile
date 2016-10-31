# For debug version:
CFLAGS = -g -O0 -L./lariph -Wno-aggregate-return

# For release version:
# CFLAGS = -L./lariph

CC = g++ $(CFLAGS)

LARIPH_FILES = lariph/lariph.cpp lariph/lamult.cpp \
	lariph/ladiv.cpp lariph/laitoa.cpp lariph/lmariph.cpp

all: stcalc

stcalc: stcalc.o BigInt.o BIStack.o lariph/liblariph.a
	$(CC) -o stcalc stcalc.o BigInt.o BIStack.o -llariph

stcalc.o: stcalc.cpp BigInt.h BIStack.h
	$(CC) -c stcalc.cpp

BigInt.o: BigInt.cpp BigInt.h lariph/lariph.h
	$(CC) -c BigInt.cpp

BIStack.o: BIStack.cpp BIStack.h BigInt.h
	$(CC) -c BIStack.cpp

lariph/liblariph.a: $(LARIPH_FILES)
	cd lariph; make liblariph.a; cd ..

tst: tst.cpp  BigInt.o lariph/liblariph.a
	$(CC) -o tst tst.cpp BigInt.o -llariph

clean:
	rm -f *.o *\~ stcalc tst
	cd lariph; make clean; cd ..
