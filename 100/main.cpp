#include <iostream>

using namespace std;

int main(void){
  int i,j;
  int tmp;
  int length = 0;
  int tmp_len = 1;
  bool switched = false;
  while(cin >> i >> j){
    if(i > j){
      tmp = i;
      i = j;
      j = tmp;
      switched = true;
    }
    length = 0;
    for(int a = i; a <= j; a++){
      tmp = a;
      tmp_len = 1;
      while(tmp != 1){
	if(tmp %2 == 0)
	  tmp /= 2;
	else{
	  tmp *= 3;
	  tmp += 1;
	}
	tmp_len++;
      };
      if(length < tmp_len)
	length = tmp_len;
    }
    if(switched)
      cout << j << " " << i << " " << length << endl;
    else
      cout << i << " " << j << " " << length << endl;
    switched = false;
  }
  return 0;
}
