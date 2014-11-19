#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
int main(){
    char cur;
    string str;
    getline(cin, str);
    if(str == "0"){
        cout << 1 << endl;
        return 0;
    }
    int len = str.size();

    int numlen = min(len, 3);

    string numb = str.substr(len - numlen, numlen);
    int num = atoi(numb.c_str());
    switch(num % 4){
        case 1:
            cout << 2 << endl;
            break;
        case 2:
            cout << 4 << endl;
            break;
        case 3:
            cout << 8 << endl;
            break;
        case 0:
            cout << 6 << endl;
            break;
    }
}

