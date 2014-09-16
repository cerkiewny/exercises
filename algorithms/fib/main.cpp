#include<iostream>

void mult(int (&ar1)[4], int ar2[4]){
   int temp[4];
   temp[0] = ar1[0] * ar2[0] + ar1[1] * ar2[3]; 
   temp[1] = ar1[0] * ar2[1] + ar1[1] * ar2[3]; 
   temp[2] = ar1[2] * ar2[0] + ar1[3] * ar2[2]; 
   temp[3] = ar1[2] * ar2[1] + ar1[3] * ar2[3]; 
   for(int i = 0; i < 4; i++){
       ar1[i] = temp[i];
   }
}


int main(){
    using namespace std;
    int n;


    cin >> n;

    int arr[4] = {1,1,0,1};
    
    int res[4]  = {1,1,0,1};
    while(n > 0){
        if(n % 2 == 1){
            mult(res, arr);
        }
        n = n / 2;
        mult(arr, arr);
    }
    for(int i = 0; i < 4; i++){
       cout << res[i] << " ";
    }
    cout <<  endl;
}
