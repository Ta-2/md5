#include "./md5Header.hpp"

int main(){
	md5 m("abc");
	string ans = m.CalcHash();
	cout << "answer" << ans << endl;

	return 0;
}
