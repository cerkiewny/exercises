#include<iostream>
#include<queue>
#include<vector>
using namespace std;
int nums[1000001];

class sum{
    public:

        int val;
        int count;
        int num;
        deque<int> vals;
        sum(int n) : val(0), count(0), vals() {num = n;}
        int push(int i) {
            val += i;
            if (count < num)
                vals.push_back(i);
            else{
                val -= vals[0];
                vals.pop_front();
            }
        }
};

int main(){
    using namespace std;
    for(int i = 0; i < 1000000; i ++){
        nums[i] = 1;
    }
    nums[0] = 0;
    nums[1] = 0;
    for(int i = 2; i < 1000000; i ++){
        if(nums[i] != 0){
            int j = 2 * i;
            while(j < 1000000){
                nums[j] = 0;
                j += i;
            }
        }
    }
    
    int res = 2;
    int sumr = 0;

    vector<int> primes;
    for(int i = 2; i < 500000; i ++){
        if(nums[i] == 1){
            primes.push_back(i);
        }
    }
    bool seen = true;
    while(seen){
        seen = false;
        sum tmps(res);
        int i = 0;
        for( ; i <= res; i++){
            tmps.push(primes[i]);
        }
        if(tmps.val <= 1000000){
            seen = true;
        }
        while (tmps.val < 1000000 && i < primes.size()){
            if(nums[tmps.val] == 1){
                sumr = tmps.val;
                cout << primes[i] << endl;
            }
            i++;
            tmps.push(primes[i]);
        }
        res++;
    }

    cout << res;
    cout << " " << sumr << endl;
}
