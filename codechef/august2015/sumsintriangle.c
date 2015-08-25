#include <stdio.h>


int nums[100];
int main(){
  int ncases;

  scanf("%hi", &ncases);
  for(int i = 0; i < ncases; i ++){
    int cursize;
    scanf("%hi", &cursize);
    for(int j = 0 ; j < cursize + 2; j++){
      nums[j] = 0;
    }

    for(int j = 0 ; j < cursize; j++){
      int parents[2];
      int tmp;
      parents[0] = 0;
      parents[1] = nums[0];
      for(int k = 0; k <= j; k++){
        scanf("%hi", &tmp);
        int chosen = (parents[0] > parents[1] ? parents[0] : parents[1]);
        nums[k] = chosen + tmp;
        parents[0] = parents[1];
        parents[1] = nums[k + 1];
      }
      

    }
    int max = 0;
    for(int k = 0; k <= cursize + 1; k++){
      if (nums[k] > max){
        max = nums[k];
      }
    }
    printf("%hi\n", max);
  }
}
