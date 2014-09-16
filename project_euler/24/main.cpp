
#include <iostream>     // std::cout
#include <algorithm>   

int main(){
    int myints[]= {0, 1, 2, 3 ,4 ,5 ,6 ,7 ,8 ,9};
    int i = 0;
    do {
        std::next_permutation(myints,myints+10);
        i++;
    } while( i < 999999);

    for( int j = 0 ; j < 10; j ++){
        std::cout << myints[j];
    }
    std::cout << std::endl;
}
