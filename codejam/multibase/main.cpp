

#include<iostream>
#include<string>

int main(){
    using namespace std;


    int T;
    int a[10];
    
    cin >> T;
    string str;
    getline(cin, str);

    while(T > 0){
        getline(cin, str);
        cout << str << endl;
        T--;
    }

}
