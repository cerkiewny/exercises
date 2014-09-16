#include<fstream>
#include<cmath>
#include<list>
#include<iomanip>
#include<iostream>
#include<cstring>
using namespace std;

long repstab[100][100];
long sum[100];

long calc_res(long x, long y){
    long ret = 0;
     for(long j = 0; j< x; j++){
         for(long k = 0; k< y; k++){
            ret += abs( repstab[j][k]- (sum[k] / x));
         }
     }
     return ret;
}

string remove_reps(string &in, long num){
    char cur;
    long reps = 0;
    string ret = "";
    cur = in[0];
    ret.push_back(cur);
    for(long i = 0; i < in.length(); i++){
        if(cur != in[i]){
            cur = in[i];
            ret.push_back(cur);
            repstab[num][ret.length() - 2] = reps;
            sum[ret.length() -2 ] += reps;
            reps = 0;
        }
        reps++;
    }
    ret.push_back(cur);
    sum[ret.length() -2 ] += reps;
    repstab[num][ret.length() - 2] = reps;
    return ret;
}

int main(int argc, char**argv)
{
 ifstream in;
 ofstream out;

 in.open("in");
 out.open("out");
 long nstrings;
 long ncases;
 long ret;
 in >> ncases;
 double growRate = 2;
 bool end = false;
 for(long i = 0; i < ncases; i++){
     long len;
     memset(repstab,1,sizeof(repstab));
     memset(sum,0,sizeof(sum));
     bool possible = true;
     in >> nstrings;
     string current;
     in >> current;
     string ref = remove_reps(current, 0);
     for(long j = 0; j < nstrings - 1; j++){
         in >> current;
         if(remove_reps(current, j + 1)!= ref){
             possible = false;
         }

     }
     ret = calc_res(nstrings, ref.length() - 1);
     for(long j = 0; j< nstrings; j++){
         for(long k = 0; k< ref.length() - 1; k++){
             cout << repstab[j][k];
             cout << " ";
         }
         cout << endl;
     }
     if(possible == true)
        out << "Case #" << i + 1<< ": " << ret << endl;
     else
        out << "Case #" <<i + 1 << ": " << "Fegla Won"<< endl;
    }
}

