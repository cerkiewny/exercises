#include<string>
#include<iostream>
#include<fstream>

#define MAX 100000000

class RouteGenerator 
{
    private:
        int numpoints;
        int ** totalcosts;
        void Step();
        void WriteToStream(std::ostream &ostr);
    public:
        void PrintTotalcosts();
        RouteGenerator(std::string filename);
        void SaveRoutes(std::string filename);
};
