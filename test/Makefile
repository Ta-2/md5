test: test.o
	g++ -Wall -o test test.o -L../lib -lmd5

test.o: test.cpp
	g++ -Wall -I../include -c test.cpp

.PHONY: clean rebuild
clean:
	-rm ../lib/*.o *.o test

rebuild:
	-rm ../lib/*
	g++ -Wall -I../include \
	-o ../lib/md5.o \
	-c ../src/md5Source.cpp
	ar rcs ../lib/libmd5.a ../lib/md5.o
