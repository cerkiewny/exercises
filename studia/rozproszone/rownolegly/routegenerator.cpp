#include"routegenerator.h"
#include<omp.h>

static bool end = false;

RouteGenerator::RouteGenerator(std::string filename) : numpoints(0){
    std::ifstream Reader(filename.c_str());
    std::string line;
    if(Reader.is_open()){
        Reader >> numpoints;
        int numentries;
        Reader >> numentries;
        int point1;
        int point2;
        int cost;
        totalcosts = new int * [numpoints];
        for(int i = 0; i < numpoints; i++){
            totalcosts[i] = new int[numpoints];
        }


        for(int i = 0; i < numpoints; i++){
            for(int j = 0; j < numpoints; j++){
                totalcosts[i][j] = MAX;
            }
        }
        for(int i = 0; i < numpoints; i++){
            totalcosts[i][i] = 0;
        }
        while (numentries--) 
        {
            Reader >> point1;
            Reader >> point2;
            Reader >> cost;
            if(totalcosts[point1 - 1][point2 - 1] > cost)
            {
                totalcosts[point1 - 1][point2 - 1] = cost;
            }
        }
        Reader.close();
    }
    PrintTotalcosts();
    while(!end){
        Step();
    }
    PrintTotalcosts();
    return;
}

void RouteGenerator::Step(){
    omp_lock_t writelock[numpoints];
    for(int curLock = 0; curLock < numpoints; curLock++){
        omp_init_lock(&writelock[curLock]);
    }
    end = true;
    for(int curSrc = 0; curSrc < numpoints; curSrc++){
        #pragma omp parallel for num_threads(3) shared(end)
        for(int curDest = 0; curDest < numpoints; curDest++){
            for(int curInt = 0; curInt < numpoints; curInt++){
                //printf("out : %d\n", omp_get_thread_num());
                if(totalcosts[curSrc][curDest] > (totalcosts[curSrc][curInt] + totalcosts[curInt][curDest])){
                    while(!omp_test_lock(&writelock[curSrc])){
                        //printf("sleeping: %d %d\n", omp_get_thread_num(), curSrc);
                        usleep(200);
                    }
                    totalcosts[curSrc][curDest] = totalcosts[curSrc][curInt] + totalcosts[curInt][curDest];
                    omp_unset_lock(&writelock[curSrc]);
                    #pragma omp critical
                    {
                        printf("yep\n");
                        end = false;
                    }
                }
            }
        }
    }
    for(int curLock = 0; curLock < numpoints; curLock++){
        omp_destroy_lock(&writelock[curLock]);
    }
    for(int i = 0; i < numpoints; i++){
        if(totalcosts[i][i]){
            end = true;
            std::cout << "negative value cycle detected!!!!!!\n";
        }
    }
}

void RouteGenerator::PrintTotalcosts(){
    WriteToStream(std::cout);
}

void RouteGenerator::WriteToStream(std::ostream &ostr){
    for(int i = 0; i < numpoints; i++){
        for(int j = 0; j < numpoints; j++){
            if(totalcosts[i][j]!= MAX)
                ostr << totalcosts[i][j] << " ";
            else
                ostr << "N/A" << " ";
        }
        ostr << std::endl;
    }

}

void RouteGenerator::SaveRoutes(std::string output){
    std::ofstream ostr;
    ostr.open(output.c_str());
    if(ostr.is_open()){
        WriteToStream(ostr);
        ostr.close();
    }
    return;
}
