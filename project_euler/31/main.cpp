#include<iostream>


int coins[] = {1, 2, 5 ,10, 20, 50, 100, 200};

int howmany(int i, int max){
    int lres = 0;
    if (i == 0)
        return 1; 
    for(int j = 0; j < 8; j++){
        if(coins[j] <= max && i - coins[j] >= 0)
            lres += howmany(i - coins[j], coins[j]);
    }
    return lres;
}

int main(){

    std::cout << howmany(200, 200) << std::endl;
}

