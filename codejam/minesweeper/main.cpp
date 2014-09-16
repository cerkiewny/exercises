#include<fstream>
#include<iomanip>
#include<iostream>

using namespace std;

bool end;

int rf, cf, tf;

void solve(int r, int c, int t){
        int res = 0;
        if (end)
        {
            return;
        }
        if (t < (c - 1) && r > 2){
            rf = r;
            cf = c;
            tf = t;
            end = true;
        }

        if (t < (r -1) && c > 2){
            rf = r;
            cf = c;
            tf = t;
            end = true;
        }
        else{
            if(t >= r ){
                solve(r, c - 1, t - r);
            }
            if(t >= c){
                solve(r - 1, c, t - c);
            }

        }
}

int main(int argc, char**argv)
{
 ifstream in;
 ofstream out;

 in.open("in");
 out.open("out");
 int ncases;
 int r, c, t;
 in >> ncases;
 for(int i = 0; i < ncases; i++){
    in >> r >> c >> t;
    end = false;
    if((r*c-1) == t){
        end = true;
        rf = 1; cf = 1; tf = 1;
    }

    if(r == 1|| c == 1){
        rf = r, cf = c, tf = t;
        end = true;
    }
    solve(r,c,t);
    char toprint;

    cout << "Case #" << i + 1<< ":" << endl;
    if(tf == 0){
        rf++;
    }
    if(end){
    for(int j=0; j < r; j++){
        for(int k=0; k < c; k++){
            toprint = 'x';
            if((j < rf) && (k < cf)){
                toprint = '.';
            }
            if (k == 0 && j == 0){
                toprint = 'c';
            }
            if(j == (rf - 1) && k >= (cf - t) ){
                toprint = 'x';
            }
            cout << toprint << " ";
        }
        cout << endl;
    }
    }
    else
        cout << "Impossible" << endl;
 }
}


