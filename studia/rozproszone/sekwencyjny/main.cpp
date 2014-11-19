#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<ctype.h>
#include"routegenerator.h"

int main(int argc, char *argv[]){
    char *filename = (char *)"in";
    char *outname = (char *)"out";
    int c;

    opterr = 0;

    while ((c = getopt (argc, argv, "f:o:")) != -1)
    switch (c){
        case 'o':
            outname = optarg;
            //printf("%s\n",outname);
            break;
        case 'f':
            filename = optarg;
            //printf("%s\n",filename);
            break;
        default:
            abort ();
    }

    RouteGenerator rt = RouteGenerator(filename);
    rt.SaveRoutes(outname);
    return 0;
}
