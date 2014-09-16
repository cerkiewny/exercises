#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>     /* qsort */

int values[1000];

int compare (const void * a, const void * b)
{
      return -( *(int*)a - *(int*)b );
}

int main()
{
	FILE * fin, * fout;
	int i, ncase, j, k, nlet, maxlet, keynum, mult;
	long long int res;
	fin = fopen("in", "r");
	fout = fopen("out", "w");
	fscanf(fin, "%i\n", &ncase );
	printf("%i\n", ncase);

	for(i = 0; i < ncase; i++){
        res = 0;
        fscanf(fin, "%i %i %i\n", &maxlet, &keynum, &nlet);
        for(j=0;j<nlet;j++){
            fscanf(fin, "%i ", &values[j]);
            printf("%i ", values[j]);
        }
        qsort(values, nlet, sizeof(int), compare);
        for(j=0;j<nlet;j++){
            printf("%i ", values[j]);
        }

        printf("\n");
        mult = 1;
        k = 0;
        for(j=0;j<nlet;j++){
            k++;
            res+= mult * values[j];
            if(k == keynum){
                mult++;
                k = 0;
            }
            printf("res: %i\n", res);
        }
        printf("res: %i\n", res);
		fprintf(fout, "Case #%i: %lli\n", i+1 , res );
		
	}

	fclose(fin);
	fclose(fout);

}
