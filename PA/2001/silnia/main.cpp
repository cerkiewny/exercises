#include<iostream>
using namespace std;
int main(){
    int n;
    int ret = 1 ;
    cin >> n;
    if(n > 5){
        cout << 0 << endl;
    }
    else
    {
        for ( int i = 1; i <= n; i++) {
            ret *= i;
        }
        cout << ret % 10 << endl;
    }
}
