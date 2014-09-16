#include<fstream>
#include<iomanip>
#include<iostream>

using namespace std;

int vals[10000];
int chang[10000];

int main(int argc, char**argv)
{
    ifstream in;
    ofstream out;
    unsigned long a,b,c;
    in.open("in");
    out.open("out");
    int ncases;
    in >> ncases;
    bool end = false;
    int ret;
    for(int i = 0; i < ncases; i++){
         int m, wanted;
         for(int j = 0; j < 10000; j++){
             vals[j] = 0;
             chang[j] = 0;
         }
         in >> m >> wanted;
         for(int j = 0; j < m; j++){
                if ( j < ( m - 1 ) / 2){
                    in >> vals[j];
                    in >> chang[j];
                }
         }

     }
}


