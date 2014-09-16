#include<iostream>

int main(){
    using namespace std;
    int y = 1900;
    int m = 0;
    int d = 0;
    int wd = 0;
    int res = 0;
    while (y != 2000 || d != 30 || m != 11){
        wd = (wd + 1 ) %7;
        d++;
        switch(m){
            case 0:
            case 2:
            case 4:
            case 6:
            case 7:
            case 9:
                if (d == 31){
                    d = 0;
                    m = (m + 1) % 12;
                }
                break;
            case 11:
                if (d == 31){
                    d = 0;
                    m = (m + 1) % 12;
                    y++;
                }
                break;
            case 3:
            case 5:
            case 8:
            case 10:
                if (d == 30){
                    d = 0;
                    m = (m + 1) % 12;
                }
                break;
            case 1:
                if (y % 4 == 0 && !(y % 100 != 0 && y % 400== 0) && d == 29){
                    d = 0;
                    m = (m + 1) % 12;
                }
                else if (d == 28){
                    d = 0;
                    m = (m + 1) % 12;
                }
                break;
        }
        if ( y >= 1901 && d == 0 && wd == 6){
            res ++;
        }

    }
    cout << res << endl;
}
