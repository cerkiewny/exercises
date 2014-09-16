#include<stdio.h>
#include<fcntl.h>
#include<string.h>

int main()
{
	FILE * fin, * fout;
	int i, ncase, j, k, l, m, n, o;
	long long int N, A, B, C, D, x0, y0, X, Y, M, res;
	fin = fopen("in", "r");
	fout = fopen("out", "w");
	int rests[3][3] = {0};
	long long int i1, i2, i3;
	fscanf(fin, "%i\n", &ncase );
	
	printf("%i\n", ncase);

	for(i = 0; i < ncase; i++){
		memset(rests,0,sizeof(rests));
		res = 0;
		fscanf(fin, "%lli %lli %lli %lli %lli %lli %lli %lli\n", &N, &A, &B, &C, &D, &x0, &y0, &M);
		printf("%lli %lli %lli %lli %lli %lli %lli %lli\n", N, A, B, C, D, x0, y0, M);
		X = x0;
		Y = y0;
		
		rests[X%3][Y%3]++;

//		printf("%lli %lli\n", X, Y);
		for ( j = 1; j < N; j++ ){
			X = (A * X + B) % M;
			Y = (C * Y + D) % M;
			rests[X%3][Y%3]++;
//			printf("%lli %lli\n", X, Y);
		}
		for(j = 0; j < 3; j++){
			for(k = 0; k < 3; k++){
				for(l = 0; l < 3; l++){
					for(m = 0; m < 3; m++){
						for(n = 0; n < 3; n++){
							for(o = 0; o < 3; o++){
								if((((j + l + n) % 3) == 0) && ((k + m + o) % 3 ==0)){
									printf("%i %i %i %i %i %i\n", j, k, l, m, n, o);
									i1 = rests[j][k];
									i2 = rests[l][m];
									i3 = rests[n][o];
									printf("%lli %lli %lli\n", i1, i2, i3);
									if(j == l && k == m){
										i2--;
										if(j == n && k == o){
											i2--;
											i3--;
										}
									}
									else if(l == n && m == o){
										i3--;
									}
									printf("%lli\n", i1 * i2 * i3);
									res+= (i1 * i2 * i3);
								}
							}
						}
					}
				}
			}
		}
		fprintf(fout, "Case #%i: %lli\n", i+1 , res / 6);
		
	}

	fclose(fin);
	fclose(fout);

}
