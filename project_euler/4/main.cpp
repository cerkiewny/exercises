#include<iostream>
using namespace std;

bool is_pali(int in){
    int j = 0;
    int i = in;
    while ( i ){
        j *= 10;
        j += i % 10;
        i = i / 10;
    }
    return in == j;

}

int main(){
    int res = 0;
    for(int i = 100; i < 1000; i++){
        for(int j = i + 1; j < 1000; j++){
            if(is_pali(i*j) && (i * j) > res){
                res = i * j;
            }
        }
    }
    cout << res << endl;
}
