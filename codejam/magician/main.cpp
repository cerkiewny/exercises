#include<fstream>
#include<iostream>

using namespace std;

int which(int a[], int b[]){
    int howmany = 0;
    int which = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(a[i]==b[j]){
                howmany++;
                which = a[i];
            }
        }
    }
    if(howmany ==1){
         return which;
    }
    if(howmany == 0){
        return 0;
    }
    return -1;

}

int main(int argc, char**argv)
{
 ifstream in;
 ofstream out;
 
 in.open("in");
 out.open("out");

 int a;
 int b;
 int c;
 in >> a;
 for(int i = 0; i < a ; i++)
 {
     int res1[4][4];
     in >> b;
     for(int j = 0; j < 4; j++)
     {
         in >> res1[j][0];
         in >> res1[j][1];
         in >> res1[j][2];
         in >> res1[j][3];
     }
     int res2[4][4];
     in >> c;
     for(int j = 0; j < 4; j++)
     {
         in >> res2[j][0];
         in >> res2[j][1];
         in >> res2[j][2];
         in >> res2[j][3];
     }
     int res = which(res1[b-1],res2[c-1]);

     if(res == 0)
         out << "Case #" << i + 1 << ": Volunteer cheated!" <<endl;
     if(res < 0)
         out << "Case #" << i + 1 << ": Bad magician!" << endl;
     if(res > 0)
         out << "Case #" << i + 1 << ": " << res << endl;

 }
}

