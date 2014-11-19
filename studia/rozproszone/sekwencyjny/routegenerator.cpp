#include"routegenerator.h"

RouteGenerator::RouteGenerator(std::string filename) : numpoints(0){
    std::ifstream Reader(filename.c_str());
    std::string line;
    end = false;
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
    end = true;
    for(int curSrc = 0; curSrc < numpoints; curSrc++){
        for(int curDest = 0; curDest < numpoints; curDest++){
            for(int curInt = 0; curInt < numpoints; curInt++){
                if(totalcosts[curSrc][curDest] > totalcosts[curSrc][curInt] + totalcosts[curInt][curDest]){
                    totalcosts[curSrc][curDest] = totalcosts[curSrc][curInt] + totalcosts[curInt][curDest];
                    end = false;
                    }
            }
        }
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
