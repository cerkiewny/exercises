#include<iostream>

int main(){
    long long int res = 0;
    for (int i = 1 ; i < 1001; i++){
        long long int ltemp = i;
        for(int j = 1; j < i; j++){
            ltemp = ( ltemp * i ) % 10000000000LL;
        }
        res = (res + ltemp) % 10000000000LL;
    }
    std::cout << res << std::endl;
}
