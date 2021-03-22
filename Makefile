md5: md5.o
	g++ -Wall -o md5 md5.o

md5.o: md5.cpp
	g++ -Wall -c md5.cpp
