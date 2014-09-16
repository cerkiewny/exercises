#include<iostream>
#include<map>
using namespace std;

int rests[101];

class info{
public:
    int present[100];

    int pres ( int in){
        return present[in];
    }

    info (){
        for(int i = 0; i < 100; i++)
            present[i] = 0;
    }

    
    void set(int a){
        present[a] = 1;
    }
};

ostream& operator<<(ostream& os, info & in)
{
    int tmp = 0;
    bool seen = false;
    for(int i = 99; i > -1; i--){
        if( in.present[i]){
            seen = true;
            cout << 1;
        }
        else if(seen)
            cout << 0;
    }
    cout << endl;
    return os;
}

int main(){
    int ncases;
    cin >> ncases;
    for(int i = 0; i < ncases; i++){
        int curnum;
        cin >> curnum;
        rests[0] = 1 % curnum;
        for(int j = 0; j < 100; j++){
            rests[j + 1] = (rests[j] * 10) % curnum;
        }


        map <int, info> rest;
        rest.clear();
        map <int, int> pointless;
        pointless.clear();
        for(int j = 0; j < 100; j++){
            if(rest.find(rests[j]) == rest.end()){
                info tmp;
                tmp.set(j);
                rest[rests[j]] = tmp;
            }
            int point = 1;
            if(pointless.find(rests[j]) == pointless.end() ||!(pointless[rests[j]] == 0)){
                for( map<int, info>::iterator k = rest.begin(); k != rest.end(); k ++){
                    if(rest.find((rests[j] + k->first ) % curnum) == rest.end() && k->second.pres(j) == 0){
                        point = 0;
                        pointless.clear();
                        info tmp = k->second;
                        tmp.set(j);
                        rest[(rests[j] + k->first) % curnum] = tmp;
                    }

                }
            }
            pointless[rests[j]] = point;
            if(rest.find(0) != rest.end()){
                cout << rest[0];
                break;
            }
        }
        if(rest.find(0) == rest.end()){
            cout << "BRAK" << endl;
        }
    }
    
}

