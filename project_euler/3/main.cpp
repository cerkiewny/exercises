#include <iostream>

using namespace std;

int main(){
    long long num = 600851475143;
    int cur_number = 2;
    int res = 2;

    while(num != 1){
        if(num % cur_number == 0){
            num = num / cur_number;
            res = cur_number;
        }
        else{
            cur_number += 1;
        }
    }
    cout << res << endl;
}
