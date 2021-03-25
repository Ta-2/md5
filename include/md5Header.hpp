#ifndef MD5H
#define MD5H

#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#define TableSize 64
#define pi 3.141592653589793
typedef unsigned int ui;
using namespace std;

extern ui T[TableSize];
void CalcT();

typedef struct ByteStruct{
private:
	ui bit1: 1;
	ui bit2: 1;
	ui bit3: 1;
	ui bit4: 1;
	ui bit5: 1;
	ui bit6: 1;
	ui bit7: 1;
	ui bit8: 1;
public:
	void PrintBits(){
		cout << bit8;
		cout << bit7;
		cout << bit6;
		cout << bit5;
		cout << bit4;
		cout << bit3;
		cout << bit2;
		cout << bit1;
	}
} Byte;

typedef union Char_BitStruct{
	char c;
	Byte bits;
	
	void PrintBits(){
		bits.PrintBits();
		cout << ".";
	}
	void PrintC(){ cout << c; }
	void PrintCint(){
		cout << hex << ((int)(c) & 0x000000ff);
	}
} CBS;

typedef struct CBSs{
	CBS cbs1;
	CBS cbs2;
	CBS cbs3;
	CBS cbs4;
	
	void PrintCBSs(){
		cbs4.PrintBits();
		cbs3.PrintBits();
		cbs2.PrintBits();
		cbs1.PrintBits();
	}
	void PrintCint(){
		cbs4.PrintCint();
		cbs3.PrintCint();
		cbs2.PrintCint();
		cbs1.PrintCint();
		cout << ".";
	}
	void Swap(){
		char temp;
		temp = cbs1.c; cbs1.c = cbs4.c; cbs4.c = temp;
		temp = cbs2.c; cbs2.c = cbs3.c; cbs3.c = temp;
	}
} CBSS;

typedef union CBS_Word{
	CBSS cbss;
	ui word;
	void PrintWord(){ cbss.PrintCBSs(); }
	void PrintCint(){ cbss.PrintCint(); }
	void Swap(){ cbss.Swap(); }
} Word;

typedef struct Word2{
	CBSS cbss1;
	CBSS cbss2;

	void PrintCBSSs(){
		cbss2.PrintCBSs();
		cbss1.PrintCBSs();
	}
	void PrintCint(){
		cbss2.PrintCint();
		cbss1.PrintCint();
	}
} W2;

typedef union LongTo2W{
	long int l;
	W2 w2;
	
	void Print2W(){ w2.PrintCint(); }
}LTW2;

class md5 {
private:	
	ui A = 0x67452301;
	ui B = 0xEFCDAB89;
	ui C = 0x98BADCFE;
	ui D = 0x10325476;
	string ans;
	vector<CBS> ByteBlock;
	ui (*F[4])(ui, ui, ui) = { F1, F2, F3, F4 };
	static ui F1(ui x, ui y, ui z){ return (x & y) | (~x & z); }
	static ui F2(ui x, ui y, ui z){ return (x & z) | (y & ~z); }
	static ui F3(ui x, ui y, ui z){ return (x ^ y ^ z); }
	static ui F4(ui x, ui y, ui z){ return (y ^ (x | ~z)); }
public:
	md5(string);
	string CalcHash();
	void P(int, ui*, ui*, ui*, ui*, Word, int, int);
}; 

#endif
