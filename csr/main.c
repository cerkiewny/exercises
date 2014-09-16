#include<stdio.h>
#include<string.h>

int find_smallest_index();
/* storage place for double the amount of string (consider looping)*/
char curchar[202];

/* possible positions (the one that have not yet been discarded) */
int poss[100];

/* this algorithm is assuming that the A != a therefore every input
information should be converted to lower / UPPER case if it is not
valid (this gives more flexibility than simply assuming that a == A

*/

int main(int argc, char**argv)
{
    int ncases, i , len, j, k, l; 
    int false_guess;
    /* read in the number of cases */
    scanf("%d", &ncases);

    for(i = 0; i < ncases; i++){
        false_guess = 0;
        for(j = 0; j < 100; j++){
            poss[j] = 1;
        }
        scanf("%s", curchar);
        len = strlen(curchar);
        /* duplicate the string in buffer so we will get behavour of looping through
           could be optimised for space reasons with modulo operator, no need for size of
           100 characters */
        memcpy(&curchar[len], &curchar, len);
        /* fix the debug prints (trailing char of strings)*/
        curchar[2*len] = '\0';
        #ifdef TESTING
        printf("%s\n", curchar);
        #endif
        /* find the smallest not yet discarded moving index */
        while(find_smallest_index() < len){
            int cur_index = find_smallest_index();
            for(k = 0; k < len; k++){
                /* if character differ we need to discard the index
                   NOTE: during optimisation for the space with modulos
                   this needs to be changed or it will cause errors*/
                if(curchar[k] != curchar[k+cur_index]){
                    poss[cur_index - 1] = 0;
                    break;
                }
            }
                
            /* if nothing have discarded current index we have found the one we are intered in*/
            if(find_smallest_index() == cur_index)
                break;
            if(k!=0){
                for(l = 0; l < k - 1; l ++){
                    poss[l] = 0;
                }
            }
        }
        /* we will use this in place zero insertion not to copy string around */
        curchar[find_smallest_index()] = '\0';

        printf("%s\n", curchar );
    }
}


/* this fucntion returns the first index of possible movement the first one
in poss array which is not yet set to 0 */
int find_smallest_index(){
    int smallest = 0;
    while(poss[smallest]!=1 && smallest < 100){
        smallest++;
#ifdef TESTING
        printf("%i\n", poss[smallest]);
#endif
    }
    return smallest + 1;
}


#ifdef TESTING


#endif
