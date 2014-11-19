#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
int main(int argc, char **argv){
    int n = 200;
    srand (time(NULL));
    omp_set_num_threads(4);
    int i = 0;
    int sum;
    #pragma omp parallel for shared(i, sum) 
        for (i = 1;i<n; i++){sum += i;std::cout << i << std::endl << "thread num:" << omp_get_thread_num() << std::endl;}
    return 0;
}
