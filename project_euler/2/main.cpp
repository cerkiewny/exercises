#include <iostream>
using namespace std;
int main(){

    int res = 0;
    int a = 1;
    int b = 2;
    int temp = 0;
    while(b < 4000000){
        if(b % 2 == 0) res += b;
        temp = a + b;
        a = b;
        b = temp;
    }
    cout << res << endl;

}
