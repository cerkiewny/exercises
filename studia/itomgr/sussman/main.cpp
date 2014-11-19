#include<fstream>
#include<iostream>
#include<string>


using namespace std;

int main(){
    ifstream in;
    int nblocks;
    in.open("in");
    in >> nblocks;
    for(int i = 0; i < nblocks; i++){
        char tmp;
        in >> tmp;
        cout << tmp;
    }

}
