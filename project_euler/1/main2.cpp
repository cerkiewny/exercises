#include<iostream>

int sumN(int a, int n,int d){
    return (n * ( 2 * a + ( n - 1 ) * d )) / 2;
}

int main(){
    using namespace std;
    int sum3 = sumN(3, 1000 / 3, 3);
    int sum5 = sumN(5, 1000 / 5, 5);
    int sum15 = sumN(15, 1000 / 15, 15);

    cout << sum3 + sum5 - sum15 << endl;
}
