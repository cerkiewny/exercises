#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<math.h>

long long int primes[1000003] = {0};
long long int numbers[1000003] = {0};
long long int composite[1000003] = {0};

void update(long long int j, long long int val){
	if(numbers[j] == 0 || numbers[j] == 1){
		numbers[j] = val;
	}
	else if(numbers[j] < val){
		update(val, numbers[j]);
	}
	else if (numbers[j] > val){
		update(numbers[j], val);
		numbers[j] = val;		
	}
}

int main()
{
	FILE * fin, * fout;
	long long int ncase, l, isfirst, numof, mingroup;
	long long int col = 0;
	long long int i, j, k, temp, first;
	long long int A, B;
	long long int res, P, match, bigest, prevmatch;
	fin = fopen("in", "r");
	fout = fopen("out", "w");
	fscanf(fin, "%lli\n", &ncase );
	printf("%lli\n", ncase);
	for(k = 2; k < 1000002; k ++){
		if(primes[k] > 0)
			continue;
		j = k + k;
		while(j < 1000002){
			primes[j]++;
			j += k;
		}
	}
	for(i = 0; i < ncase; i++){
		res = 0;
		memset(numbers, 0, sizeof(numbers));
		memset(composite, 0, sizeof(composite));
		fscanf(fin, "%lli %lli %lli\n", &A, &B, &P);
		res = B - A + 1;

		for(j = P; j < (B - A + 1); j++){
			if(primes[j] > 0){
				continue;
			}
			numof = 0;
			first = A % j;
			if(first != 0){
				first = j - first;
			}
			k = first;
			mingroup = j;
			while(k < (B - A + 1)){
				if(composite[k] > 0){
					update(j, composite[k]);
					composite[k] = j;
				}
				else{
					numof++;
					composite[k] = j;
					res--;
				}
				k+= j;
			}
			if(numbers[j] == 0){
				numbers[j] = 1;
			}
			
		}
/**		for(j = P; j < (B - A + 1); j++){
			printf("%d ", numbers[j]);
		}
		printf("\n", numbers[j]);
		for(j = P; j < (B - A + 1); j++){
			printf("%d ", composite[j]);
		}
		printf("\n", numbers[j]);
**/
		for(j = P; j < (B - A + 1); j++){
			if(numbers[j] == 1){
				res++;
//				printf("%d\n", res);
			}
		}
		printf("%lli\n", i + 1);
		fprintf(fout, "Case #%lli: %lli\n", i + 1, res);
	}

	fclose(fin);
	fclose(fout);

}
