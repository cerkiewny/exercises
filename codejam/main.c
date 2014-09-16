#include<stdio.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	FILE * fin, * fout;
	int i, ncase;
	long long int res;
	fin = fopen("in", "r");
	fout = fopen("out", "w");
	fscanf(fin, "%i\n", &ncase );
	printf("%i\n", ncase);

	for(i = 0; i < ncase; i++){


		fprintf(fout, "Case #%i: %lli\n", i+1 , res );
		
	}

	fclose(fin);
	fclose(fout);

}
