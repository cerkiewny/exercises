#include<fstream>
#include<string>
#include<sstream>
#include<cmath>
#include<iostream>
#include<vector>
#include<fstream>

struct point{
    double first;
    double second;
    std::string name;
    std::vector<point> assigned;
};

double distance(point & a, point & b){
    double resa = a.first - b.first;
    resa = resa * resa;

    double resb = a.second- b.second;
    resb = resb * resb;
    
    return sqrt(resa + resb);
}

int main(int argc, char* argv[]){
    int debuglvl = 0;
    char c;
    while ((c = getopt (argc, argv, "d:")) != -1)
        switch (c)
        {
           case 'd':
             debuglvl = atoi(optarg);
             break;
           default:
             abort ();
        }

    std::cout << debuglvl << std::endl;
    // open input file
    std::ifstream data_file("in");
    std::ofstream result_file("OUTPUT.TXT");
    
    //point storage
    std::vector<point> points;
    //read file
    while(data_file){
        point pt;
        data_file >> pt.first;
        data_file.ignore(1);
        data_file >> pt.second;
        points.push_back(pt);
//        std::cout << pt.first << "," << pt.second << std::endl;
    }

    //initialize centers of celoids
    std::vector<point> centers;
    point temp;
    temp.name = "Adam";
    temp.first = -0.357;
    temp.second = -0.253;
    centers.push_back(temp);
    temp.name = "Bob";
    temp.first = -0.357;
    temp.first = -0.055;
    temp.second = 4.392;
    centers.push_back(temp);
    temp.name = "Charley";
    temp.first = -0.357;
    temp.first = 2.674;
    temp.second = -0.001;
    centers.push_back(temp);
    temp.name = "David";
    temp.first = -0.357;
    temp.first = 1.044;
    temp.second = -1.251;
    centers.push_back(temp);
    temp.name = "Edward";
    temp.first = -0.357;
    temp.first = -1.495;
    temp.second = -0.09;
    centers.push_back(temp);

//    std::cout << distance(temp, temp2) << std::endl;

    //did we finish?
    bool end = false;
    //debug purpose only
    int iters = 0;
    while(!end){
        iters ++;

        std::ofstream ot;
        //visualization output
        if(debuglvl > 1){
            std::stringstream tmp;
            tmp << "testout" << iters;
            std::string name = tmp.str();

            ot.open (name);
        }
        end = true;
        //for each of the centers (celoids efectively) clear point assigned
        //this could be handling the rolling avarage on the celoids on the 
        //assignment change but the double issues need to be concidered -
        //long addition and substitution of a small number from large one has
        //a big error therefore its propably better to recalculate all
        for(auto lpoint = centers.begin(); lpoint != centers.end(); lpoint++){
            lpoint->assigned.clear();
        }
        //for each point calculate the distance of closest celoid center
        //this also could have been done better - by KD tree segmentation
        //but it would only be efficient for a higher nubmer of celoids
        for(auto lpoint = points.begin(); lpoint != points.end(); lpoint++){
            auto min = centers.begin();
            for(auto center = centers.begin(); center != centers.end(); center++){
                if(distance(*center, *lpoint) < distance(*min, *lpoint)){
                    min = center;
                }
            }
            min->assigned.push_back(*lpoint);
        }
        //visualization purpose only
        int counter = 0;
        //now for eaqch of the celoids calculate center of mass
        for(auto lpoint = centers.begin(); lpoint != centers.end(); lpoint++){
            counter++;
            int weight = 0;
            double x = 0.0;
            double y = 0.0;
            for(auto current_assigned = lpoint->assigned.begin(); current_assigned != lpoint->assigned.end(); current_assigned++){
                weight++;
                //std::cout << current_assigned->first << "," << current_assigned->second << "," << counter << std::endl;
                if(debuglvl > 1){
                    ot << current_assigned->first << "," << current_assigned->second << "," << counter << std::endl;
                }
                x += current_assigned->first;
                y += current_assigned->second;
            }
            x /= weight;
            y /= weight;
            point celcenter;
            celcenter.first = x;
            celcenter.second = y;
            //if none of the celoiuds centers have moved it means we are finished
            //so set end to false if at least one coordinate of at lesat one celoid changed
            if((lpoint->first - x) > 0){
                lpoint->first = x;
                end = false;
            }
            if((lpoint->second - y) > 0){
                lpoint->second = y;
                end = false;
            }
        }
        if(debuglvl > 1){
            ot.close();
        }

        //write the file for visualization
        if(debuglvl > 1){
            std::stringstream tmp;
            tmp << "testout" << iters << "pts";
            std::string name = tmp.str();
            std::ofstream otpts;
            otpts.open (name);
            int i = 0;
            for(auto lpoint = centers.begin(); lpoint != centers.end(); lpoint++){
                i++;

                std::cout << i << ": " << lpoint->first << " " << lpoint->second << std::endl;
                otpts << lpoint->first << "," << lpoint->second << "," << i << std::endl;
            }
            otpts.close();
        }
    }

    //set precision of the result
    result_file.setf(std::ios_base::fixed, std::ios_base::floatfield);
    result_file.precision(3);
    //write it to a file
    double totalmet = 0.0;
    for(auto lpoint = centers.begin(); lpoint != centers.end(); lpoint++){
        double metric = 0.0;
        for(auto current_assigned = lpoint->assigned.begin(); current_assigned != lpoint->assigned.end(); current_assigned++){
            metric += distance(*current_assigned, *lpoint);
        }
        result_file << "error=" << metric << std::endl;
        result_file << lpoint->name << std::endl;
        totalmet += metric;
    }
    result_file.close();
    std::cout << "iters done: " << iters << std::endl;
    data_file.close();
}
