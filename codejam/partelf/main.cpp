#include<fstream>
#include<iomanip>
#include<iostream>

using namespace std;

long find_min(long a, long c){
    long i = 0;
    long j = 1;
    while(c >= j){
        i++;
        j = j * 2;
    }
    while(a >= 2){
        a = a / 2;
        i--;
    }

    return i - 1;
}

bool check_pos(long a, long c){
    long i = 0;
    long j = 1;
    while(c % 2 == 0){
        c = c / 2;
        if(a %2 == 0){
            a = a / 2;
        }
    }
    if(c == 1 || c == a )
        return true;
    return false;

}

int main(int argc, char**argv)
{
 ifstream in;
 ofstream out;
 unsigned long a,c;
 char b;
 in.open("in");
 out.open("out");
 long ncases;
 in >> ncases;
 bool end = false;
 long ret;
 for(long i = 0; i < ncases; i++){
    ret = 0;
    in >> a;
    in >> b;
    in >> c;
    ret  = find_min(a, c);
    bool pos = check_pos(a,c);
    if(pos)
        out << "Case #" << i + 1<< ": " << ret << endl;
    else
        out << "Case #" << i + 1<< ": " << "impossible" << endl;
}
}


