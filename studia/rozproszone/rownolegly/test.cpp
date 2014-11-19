#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define lba_iter 200
int main(){
   float a[lba_iter], b[lba_iter];
   int ind_lok[lba_iter], tab_it_wyk[2*lba_iter];
   double sum;
   double xsum;
   int it_wpis;
   int i, iter_no, j, k;
   FILE *fp;
   for(i=0;i<lba_iter;i++){
         a[i]=i;b[i]=i+2;
}
   it_wpis=0.; sum=0.;
#pragma omp parallel private(xsum,iter_no,ind_lok, k, j) \
                        shared(sum,it_wpis, tab_it_wyk)
{
   double coslicz, sinlicz, arglicz;
   xsum = 0.0; iter_no=0;
#pragma omp for
   for(i=0;i<lba_iter;i++){
         sinlicz = sin((double)a[i]*b[i]);
         arglicz=0;
         for(k=1; k< 5000;k++){
            arglicz=arglicz+k*sinlicz;
            coslicz=cos(arglicz*arglicz);
         }
         xsum = xsum+coslicz;
         ind_lok[iter_no] = i;
         iter_no=iter_no+1;
   }
#pragma omp critical
   {
      for(j=0; j< iter_no; j++){
          tab_it_wyk[it_wpis+j] = ind_lok[j];
      }
      it_wpis = it_wpis + iter_no;
      sum = sum + xsum;
   }
}
   fp=fopen("wyniki.dat", "w");
   for(i=0;i<lba_iter;i++){
       fprintf(fp,"%d ",tab_it_wyk[i]);
       if(i>0 && (i+1)%10==0)fprintf(fp,"\n");
   }
   fprintf(fp,"\n%lf\n", sum);
   printf("Suma=%lf\n", sum);
}

