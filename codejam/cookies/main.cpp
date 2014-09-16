#include<fstream>
#include<iomanip>
#include<iostream>

using namespace std;

int main(int argc, char**argv)
{
 ifstream in;
 ofstream out;

 in.open("in");
 out.open("out");
 double c,f,x;
 int ncases;
 in >> ncases;
    double growRate = 2;
 bool end = false;
 for(int i = 0; i < ncases; i++){
    in >> c >> f >> x;
    double begTime = 0;
    double growRate = 2;
    double current = x / growRate;
    double nexstep = current;
    end = false;
    while(!end){
        begTime += c / growRate;
        growRate += f;
        nexstep = begTime + (x / growRate);
        if(nexstep > current){
            end = true;
        }
        else{
			current = nexstep;
			end = false;
        }
    }
    cout << "Case #" << i + 1<< ": " << setprecision(14) << current << endl;
 }
}


