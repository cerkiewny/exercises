#include<stdio.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	FILE * fin, * fout;
	unsigned int ncase, i, j, k = 0, scope, num, current, remleft, count, remain, numres;
	long long int res;
	int end = 0;
	fin = fopen("in", "r");
	fout = fopen("out", "w");
	fscanf(fin, "%i\n", &ncase );
	printf("%i\n", ncase);

	for(i = 0; i < ncase; i++){
		fscanf(fin, "%i\n", &scope);
		fscanf(fin, "%i", &numres);
        fprintf(fout, "Case #%i: ", i+1);
        printf("%i\n", i);
		for(j=0; j < numres; j++){
			fscanf(fin, "%i", &num);
            remleft = num - 1;
            count = 1;
            end = 0;
            current = 0;
            remain = scope;
            while(1){
                current = (current + ( (count - 1) % remain)) % (remain);
                if(current == remleft){
                    break;
                }
                if(current < remleft){
                    remleft--;
                }
                count++;
                remain--;
            }
            res = count;
            if(j==numres-1) fprintf(fout, "%lli", res );
            else 
                fprintf(fout, "%lli ", res );
		}
        fprintf(fout, "\n" );
		
	}

	fclose(fin);
	fclose(fout);

}
