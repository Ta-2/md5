#include "./md5Header.hpp"

ui T[TableSize] = {};
//ui md5::A = 0x67452301;
//ui md5::B = 0xEFCDAB89;
//ui md5::C = 0x98BADCFE;
//ui md5::D = 0x10325476;

void CalcT(){
	for(int i = 1; i <= TableSize; i++)
		T[i-1] = (ui)(4294967296 * fabs(sin(i)));
}

md5::md5(string input){
	if(!T[0])CalcT();
	int len = input.length()*8;
	int padding = 0;
	
	if(!(padding = ((512+(448-(len%512)))%512)))padding = 512;

	ByteBlock.reserve(len+padding+64);
	for(char c: input)
		ByteBlock.push_back(CBS{c});	

	ByteBlock.push_back(CBS{(char)(0b10000000)});
	for(padding-=8; padding; padding-=8)
		ByteBlock.push_back(CBS{(char)(0b00000000)});

	LTW2 ltw2{len};
	ByteBlock.push_back(ltw2.w2.cbss1.cbs1);
	ByteBlock.push_back(ltw2.w2.cbss1.cbs2);
	ByteBlock.push_back(ltw2.w2.cbss1.cbs3);
	ByteBlock.push_back(ltw2.w2.cbss1.cbs4);
	ByteBlock.push_back(ltw2.w2.cbss2.cbs1);
	ByteBlock.push_back(ltw2.w2.cbss2.cbs2);
	ByteBlock.push_back(ltw2.w2.cbss2.cbs3);
	ByteBlock.push_back(ltw2.w2.cbss2.cbs4);
}
string md5::CalcHash(){
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
		}
		
P(1, &AA, &BB, &CC, &DD, wb[0], 7, 1); P(1, &DD, &AA, &BB, &CC,  wb[1], 12, 2); P(1, &CC, &DD, &AA, &BB, wb[2], 17, 3); P(1, &BB, &CC, &DD, &AA, wb[3], 22, 4);
P(1, &AA, &BB, &CC, &DD, wb[4], 7, 5); P(1, &DD, &AA, &BB, &CC,  wb[5], 12, 6); P(1, &CC, &DD, &AA, &BB, wb[6], 17, 7); P(1, &BB, &CC, &DD, &AA, wb[7], 22, 8);
P(1, &AA, &BB, &CC, &DD, wb[8], 7, 9); P(1, &DD, &AA, &BB, &CC,  wb[9], 12,10); P(1, &CC, &DD, &AA, &BB,wb[10], 17,11); P(1, &BB, &CC, &DD, &AA,wb[11], 22,12);
P(1, &AA, &BB, &CC, &DD,wb[12], 7,13); P(1, &DD, &AA, &BB, &CC, wb[13], 12,14); P(1, &CC, &DD, &AA, &BB,wb[14], 17,15); P(1, &BB, &CC, &DD, &AA,wb[15],22,16);

P(2, &AA, &BB, &CC, &DD, wb[1], 5,17); P(2, &DD, &AA, &BB, &CC, wb[6], 9,18); P(2, &CC, &DD ,&AA, &BB,wb[11],14,19); P(2, &BB, &CC, &DD, &AA, wb[0],20,20);
P(2, &AA, &BB, &CC, &DD, wb[5], 5,21); P(2, &DD, &AA, &BB, &CC,wb[10], 9,22); P(2, &CC, &DD, &AA, &BB,wb[15],14,23); P(2, &BB, &CC, &DD, &AA, wb[4],20,24);
P(2, &AA, &BB, &CC, &DD, wb[9], 5,25); P(2, &DD, &AA, &BB, &CC,wb[14], 9,26); P(2, &CC, &DD, &AA, &BB, wb[3],14,27); P(2, &BB, &CC, &DD, &AA, wb[8],20,28);
P(2, &AA, &BB, &CC, &DD,wb[13], 5,29); P(2, &DD, &AA, &BB, &CC, wb[2], 9,30); P(2, &CC, &DD, &AA, &BB, wb[7],14,31); P(2, &BB, &CC, &DD, &AA,wb[12],20,32);

P(3, &AA, &BB, &CC, &DD, wb[5], 4,33); P(3, &DD, &AA, &BB, &CC, wb[8],11,34); P(3, &CC, &DD, &AA, &BB,wb[11],16,35); P(3, &BB, &CC, &DD, &AA,wb[14],23,36);
P(3, &AA, &BB, &CC, &DD, wb[1], 4,37); P(3, &DD, &AA, &BB, &CC, wb[4],11,38); P(3, &CC, &DD, &AA, &BB, wb[7],16,39); P(3, &BB, &CC, &DD, &AA,wb[10],23,40);
P(3, &AA, &BB, &CC, &DD,wb[13], 4,41); P(3, &DD, &AA, &BB, &CC, wb[0],11,42); P(3, &CC, &DD, &AA, &BB, wb[3],16,43); P(3, &BB, &CC, &DD, &AA, wb[6],23,44);
P(3, &AA, &BB, &CC, &DD, wb[9], 4,45); P(3, &DD, &AA, &BB, &CC,wb[12],11,46); P(3, &CC, &DD, &AA, &BB,wb[15],16,47); P(3, &BB, &CC, &DD, &AA, wb[2],23,48);

P(4, &AA, &BB, &CC, &DD, wb[0], 6,49); P(4, &DD, &AA, &BB, &CC, wb[7],10,50); P(4, &CC, &DD, &AA, &BB,wb[14],15,51); P(4, &BB, &CC, &DD, &AA, wb[5],21,52);
P(4, &AA, &BB, &CC, &DD,wb[12], 6,53); P(4, &DD, &AA, &BB, &CC, wb[3],10,54); P(4, &CC, &DD, &AA, &BB,wb[10],15,55); P(4, &BB, &CC, &DD, &AA, wb[1],21,56);
P(4, &AA, &BB, &CC, &DD, wb[8], 6,57); P(4, &DD, &AA, &BB, &CC,wb[15],10,58); P(4, &CC, &DD, &AA, &BB, wb[6],15,59); P(4, &BB, &CC, &DD, &AA,wb[13],21,60);
P(4, &AA, &BB, &CC, &DD, wb[4], 6,61); P(4, &DD, &AA, &BB, &CC,wb[11],10,62); P(4, &CC, &DD, &AA, &BB, wb[2],15,63); P(4, &BB, &CC, &DD, &AA, wb[9],21,64);

		AA += A; BB += B; CC += C; DD += D;

		}
	Word Aa{ .word=AA }, Bb{ .word=BB }, Cc{ .word=CC }, Dd{ .word=DD };
	Aa.Swap(); Bb.Swap(); Cc.Swap(); Dd.Swap();
	char temp[255];
	sprintf(temp, "%x", Aa.word); ans += temp;
	sprintf(temp, "%x", Bb.word); ans += temp;
	sprintf(temp, "%x", Cc.word); ans += temp;
	sprintf(temp, "%x", Dd.word); ans += temp;
	
	return ans;
}
void md5::P(int n, ui* a, ui* b, ui* c, ui* d, Word k, int s, int i){
	*a = *b + (((*a + (*F[n-1])(*b, *c, *d)) + k.word + T[i-1]) << s);
}

