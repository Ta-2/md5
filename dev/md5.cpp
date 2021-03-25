#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#define TableSize 64
#define pi 3.141592653589793
using namespace std;
typedef unsigned int ui;

ui T[TableSize] = {};
void CalcT(){
	//cout << "create Table" << endl;
	for(int i = 0; i < TableSize; i++){
		T[i] = (ui)(4294967296*fabs(sin(i+1)));
		//cout << hex << T[i] << ", ";
	}
}
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

class md5{
private:
	ui A = 0x67452301, B = 0xEFCDAB89, C = 0x98BADCFE, D = 0x10325476; 
	string plain, ans;
	vector<CBS> ByteBlock;
public:
	md5(string input){
		if(!T[0])CalcT();
		//for(ui t: T)cout << t << ",";
		//cout << endl;
		plain = input;
		int len = input.length()*8;
		int padding = 0;
		
		if(!(padding = ((512+(448-(len%512)))%512)))padding = 512;
		//cout << dec << "len: " << len << ", padding: " << padding << "check: " << ((len+padding)%512) << endl;
		ByteBlock.reserve(len+padding+64);
		for(char c: plain){
			ByteBlock.push_back(CBS{c});	
		}
		/*
		cout << endl << "ByteBlock(int)" << endl;
		for(CBS b: ByteBlock)b.PrintCint();
		cout << endl;
		cout << "ByteBlock(Bit)" << endl;
		for(CBS b: ByteBlock)b.PrintBits();
		cout << endl;
		*/
		ByteBlock.push_back(CBS{(char)(0b10000000)});
		for(padding-=8; padding; padding-=8) ByteBlock.push_back(CBS{(char)(0b00000000)});
		//cout << dec << ByteBlock.size()*8 << ", " << ByteBlock.capacity() << endl;

		LTW2 ltw2{(int)(plain.size()*8)};
		//cout << "ltw2:" << endl;
		//ltw2.Print2W();
		//cout << endl;
		ByteBlock.push_back(ltw2.w2.cbss1.cbs1);
		ByteBlock.push_back(ltw2.w2.cbss1.cbs2);
		ByteBlock.push_back(ltw2.w2.cbss1.cbs3);
		ByteBlock.push_back(ltw2.w2.cbss1.cbs4);
		ByteBlock.push_back(ltw2.w2.cbss2.cbs1);
		ByteBlock.push_back(ltw2.w2.cbss2.cbs2);
		ByteBlock.push_back(ltw2.w2.cbss2.cbs3);
		ByteBlock.push_back(ltw2.w2.cbss2.cbs4);
		
		/*int i = 0;
		for(auto rplain = plain.rbegin(); i < 8; ++rplain, i++)
			ByteBlock.push_back(CBS{*rplain});
		*/
		//cout<< ByteBlock.size()*8 << ", " << ByteBlock.capacity() << endl;
		/*
		cout << "ByteBlock(int)" << endl;
		for(CBS w: ByteBlock){
			w.PrintCint();
			cout << ".";
		}
		cout << endl << "ByteBlock(bits)" << endl;
		for(CBS w: ByteBlock){
			w.PrintBits();
		}
		cout << endl;
		*/
		
	}

	string CalcuHash(){
		ui AA = A, BB = B, CC = C, DD = D;
		for(int i = 0; i < (int)ByteBlock.size(); i+=64){
			Word wb[16];
			for(int j = 0; j < 16; j++){
				wb[j] = {CBSS{
					ByteBlock[i+4*j+0],
					ByteBlock[i+4*j+1],
					ByteBlock[i+4*j+2],
					ByteBlock[i+4*j+3]
				}};
				//cout << (i+4*j+3)  << ", " << (i+4*j+2)  << ", " << (i+4*j+1)  << ", " << (i+4*j+0)  << ", " << endl;
			}
			//cout << "word X: " << endl;
			/*
			int ii = 0;
			for(Word w: wb) {
				cout << dec << " <" << ii << ">"; 
				w.PrintCint();
				ii++;
			}
			cout << endl;
			*/
P(1, &AA, &BB, &CC, &DD, wb[0], 7, 1); P(1, &DD, &AA, &BB, &CC,  wb[1], 12, 2); P(1, &CC, &DD, &AA, &BB, wb[2], 17, 3); P(1, &BB, &CC, &DD, &AA, wb[3], 22, 4);
P(1, &AA, &BB, &CC, &DD, wb[4], 7, 5); P(1, &DD, &AA, &BB, &CC,  wb[5], 12, 6); P(1, &CC, &DD, &AA, &BB, wb[6], 17, 7); P(1, &BB, &CC, &DD, &AA, wb[7], 22, 8);
P(1, &AA, &BB, &CC, &DD, wb[8], 7, 9); P(1, &DD, &AA, &BB, &CC,  wb[9], 12,10); P(1, &CC, &DD, &AA, &BB,wb[10], 17,11); P(1, &BB, &CC, &DD, &AA,wb[11], 22,12);
P(1, &AA, &BB, &CC, &DD,wb[12], 7,13); P(1, &DD, &AA, &BB, &CC, wb[13], 12,14); P(1, &CC, &DD, &AA, &BB,wb[14], 17,15); P(1, &BB, &CC, &DD, &AA,wb[15],22,16);

//cout << "stage 1" << endl;
P(2, &AA, &BB, &CC, &DD, wb[1], 5,17); P(2, &DD, &AA, &BB, &CC, wb[6], 9,18); P(2, &CC, &DD ,&AA, &BB,wb[11],14,19); P(2, &BB, &CC, &DD, &AA, wb[0],20,20);
P(2, &AA, &BB, &CC, &DD, wb[5], 5,21); P(2, &DD, &AA, &BB, &CC,wb[10], 9,22); P(2, &CC, &DD, &AA, &BB,wb[15],14,23); P(2, &BB, &CC, &DD, &AA, wb[4],20,24);
P(2, &AA, &BB, &CC, &DD, wb[9], 5,25); P(2, &DD, &AA, &BB, &CC,wb[14], 9,26); P(2, &CC, &DD, &AA, &BB, wb[3],14,27); P(2, &BB, &CC, &DD, &AA, wb[8],20,28);
P(2, &AA, &BB, &CC, &DD,wb[13], 5,29); P(2, &DD, &AA, &BB, &CC, wb[2], 9,30); P(2, &CC, &DD, &AA, &BB, wb[7],14,31); P(2, &BB, &CC, &DD, &AA,wb[12],20,32);

//cout << "stage 2" << endl;
P(3, &AA, &BB, &CC, &DD, wb[5], 4,33); P(3, &DD, &AA, &BB, &CC, wb[8],11,34); P(3, &CC, &DD, &AA, &BB,wb[11],16,35); P(3, &BB, &CC, &DD, &AA,wb[14],23,36);
P(3, &AA, &BB, &CC, &DD, wb[1], 4,37); P(3, &DD, &AA, &BB, &CC, wb[4],11,38); P(3, &CC, &DD, &AA, &BB, wb[7],16,39); P(3, &BB, &CC, &DD, &AA,wb[10],23,40);
P(3, &AA, &BB, &CC, &DD,wb[13], 4,41); P(3, &DD, &AA, &BB, &CC, wb[0],11,42); P(3, &CC, &DD, &AA, &BB, wb[3],16,43); P(3, &BB, &CC, &DD, &AA, wb[6],23,44);
P(3, &AA, &BB, &CC, &DD, wb[9], 4,45); P(3, &DD, &AA, &BB, &CC,wb[12],11,46); P(3, &CC, &DD, &AA, &BB,wb[15],16,47); P(3, &BB, &CC, &DD, &AA, wb[2],23,48);

//cout << "stage 3" << endl;
P(4, &AA, &BB, &CC, &DD, wb[0], 6,49); P(4, &DD, &AA, &BB, &CC, wb[7],10,50); P(4, &CC, &DD, &AA, &BB,wb[14],15,51); P(4, &BB, &CC, &DD, &AA, wb[5],21,52);
P(4, &AA, &BB, &CC, &DD,wb[12], 6,53); P(4, &DD, &AA, &BB, &CC, wb[3],10,54); P(4, &CC, &DD, &AA, &BB,wb[10],15,55); P(4, &BB, &CC, &DD, &AA, wb[1],21,56);
P(4, &AA, &BB, &CC, &DD, wb[8], 6,57); P(4, &DD, &AA, &BB, &CC,wb[15],10,58); P(4, &CC, &DD, &AA, &BB, wb[6],15,59); P(4, &BB, &CC, &DD, &AA,wb[13],21,60);
P(4, &AA, &BB, &CC, &DD, wb[4], 6,61); P(4, &DD, &AA, &BB, &CC,wb[11],10,62); P(4, &CC, &DD, &AA, &BB, wb[2],15,63); P(4, &BB, &CC, &DD, &AA, wb[9],21,64);
//cout << "stage 4" << endl;
		AA += A; BB += B; CC += C; DD += D;

		//cout << hex << "AA: " << AA << ", BB: " << BB << ", CC: " << CC << ", DD: " << DD << endl;
		}
		Word Aa{ .word=AA }, Bb{ .word=BB }, Cc{ .word=CC }, Dd{ .word=DD };
		//Aa.PrintWord(); cout << "::"; Bb.PrintWord(); cout << "::"; Cc.PrintWord(); cout << "::"; Dd.PrintWord(); cout << endl;
		Aa.Swap(); Bb.Swap(); Cc.Swap(); Dd.Swap();
		//Aa.PrintWord(); cout << "::"; Bb.PrintWord(); cout << "::"; Cc.PrintWord(); cout << "::"; Dd.PrintWord(); cout << endl;
		//cout << hex << "Aa: " << Aa.word << ", Bb: " << Bb.word << ", Cc: " << Cc.word << ", Dd: " << Dd.word << endl;
		char temp[255];
		sprintf(temp, "%x", Aa.word); ans += temp;
		sprintf(temp, "%x", Bb.word); ans += temp;
		sprintf(temp, "%x", Cc.word); ans += temp;
		sprintf(temp, "%x", Dd.word); ans += temp;
		//cout << ans << endl;
		return ans;
	}

	void P(int n, ui* a, ui* b, ui* c, ui* d, Word k, int s, int i){
/*
cout << "a" << endl;
cout << *a << endl;
cout << *b << endl;
cout << *c << endl;
cout << *d << endl;
cout << (*F[n-1])(*a, *b, *c) << ", " << n-1 << endl;
cout << k.word << endl;
cout << T[i-1] << endl;
cout << endl;
*/
		*a = *b + (((*a + (*F[n-1])(*b, *c, *d)) + k.word + T[i-1]) << s);
}
	
	ui (*F[4])(ui, ui, ui) = { F1, F2, F3, F4};
	static ui F1(ui x, ui y, ui z){ return (x & y) | (~x & z); }
	static ui F2(ui x, ui y, ui z){ return (x & z) | (y & ~z); }
	static ui F3(ui x, ui y, ui z){ return (x ^ y ^ z); }
	static ui F4(ui x, ui y, ui z){ return (y ^ (x | ~z)); }
};

int main(){
	string a("");
	for(int i = 0; i < 20; i++)a += ('a'+i);
	cout << "a: " << a << endl;
	md5 m1("abc");
	string ans = m1.CalcuHash();
	cout << "answer: " << ans << endl;

	return 0;
}
