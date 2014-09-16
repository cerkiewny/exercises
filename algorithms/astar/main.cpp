#include<iostream>
#include<algorithm>
#include<queue>

class point_info{
    public:
        static int nrows;
        static int ncols;
        int x;
        int y;
        int cost_est;
        int cost_so_far;
        int x_par;
        int y_par;
        
        point_info(int x, int y, int xpar, int ypar, int cost_so_far){
            this->x = x;
            this->y = y;
            this->x_par = xpar;
            this->y_par = ypar;
            this->cost_so_far = cost_so_far;
            cost_est = nrows - x + ncols - y + cost_so_far;
        }
};

int point_info::nrows = 0;
int point_info::ncols = 0;

class cmpest 
{
    public:

    bool operator() (const point_info& a, const point_info &b) const
    {
        return a.cost_est < b.cost_est;
    }
};

int nrows, ncols;

int to_1d(int x, int y){
    return x * ncols + y;
}


int main(int argc, char * argv[]){
    using namespace std;
    int end = 0;
    cin >> nrows >> ncols;
    point_info cur = point_info(0, 0, 0, 0, 0);
    point_info::nrows = nrows;
    point_info::ncols = ncols;
    int * map = new int[nrows * ncols];
    for (int i = 0 ; i < nrows; i ++){
        for (int j = 0 ; j < ncols; j ++){
            cin >> map[i * ncols + j];
        }
    }
    for (int i = 0 ; i < nrows; i ++){
        for (int j = 0 ; j < ncols; j ++){
            cout << map[i * ncols + j] << " ";
        }
        cout << endl;
    }


    int * seen = new int [nrows * ncols];
    fill_n(seen, nrows * ncols, 0);
    
    priority_queue<point_info, vector<point_info>, cmpest> pq;
    pq.push(cur);
    seen[0] = 1;
    while(!end && !pq.empty()){
        cur = pq.top();
        pq.pop();
        for(int i = -1; i < 2; i++){
            for(int j = -1; j < 2; j++){
                if(cur.x + i >= 0 &&
                   cur.y + j >= 0 &&
                   cur.x + i < nrows &&
                   cur.y + j < ncols &&
                   seen[to_1d(cur.x + i, cur.y + j)] == 0 &&
                   map[to_1d(cur.x + i, cur.y + j)] != 1 ){
                        seen[to_1d(cur.x + i, cur.y + j)] = 1;
                        point_info next = point_info(cur.x + i, cur.y + j, cur.x, cur.y, cur.cost_so_far + 1);
                        pq.push(next);
                        cout << next.x << " " << next.y << endl;
                        if(next.x == nrows -1 && next.y == ncols - 1){
                            end = 1;
                        }
                }
            }
        }
    }
    if(end == 1){
        cout << "possible" << endl;
        
    }
    else{
        cout << "not possible" << endl;
    }
    
}
