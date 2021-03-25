md5: md5.o
	g++ -Wall -o md5 md5.o

md5.o: md5.cpp
	g++ -Wall -c md5.cpp

test: test.o md5Source.o
	g++ -Wall -o test test.o md5Source.o -L.

test.o: test.cpp
	g++ -Wall -c test.cpp

md5Source.o: md5Source.cpp
	g++ -Wall -I. -c md5Source.cpp

clean:
	rm *.o test md5
