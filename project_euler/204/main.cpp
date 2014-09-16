#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;

void print_int(int i)
{
    cout << i << " ";

}


bool is_prime(int i){
    for(int j = 2; j< i; j++){
        if(i%j ==0)
            return false;
    }
    return true;
}

int how_many(int num, vector<int>::iterator cur, vector<int> &primes ){
    if(num < 100){
        int blah = 0;

        for(vector<int>::iterator k = primes.begin(); k < primes.end(); k++)
        {
            if (*k < num) blah++;
            else break;
        }
        return blah; 
    }
    int sum = 0;
    
    vector<int>::iterator it = cur;
    while(it != primes.begin()){
        cout << *it << endl;
        sum += how_many(num / (*it), it, primes);
        it--;
    }
    return sum;

}

int main(){
    vector<int> primes;

    for(int i = 2; i < 100; i++){
        if(is_prime(i)){
            primes.push_back(i);
        }
    }


    for_each(primes.begin(), primes.end(), print_int);
    cout <<endl;


    cout << how_many(1000000000, primes.end() - 1, primes) << endl;

    return 0;
}
