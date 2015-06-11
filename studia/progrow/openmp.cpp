#include <iostream>
#include <stack>
#include <cmath>


class solver {
  public: 
    double end;
    double beg;
    int depth;
    double (*func)(double);
    int base;


    std::stack<double> int_res;

    ~solver(){};

    solver ( double beg, double end, int depth, double (*func)(double), int base) : int_res(){
      this->beg = beg;
      this->end = end;
      this->depth = depth;
      this->func = func;
      this->base = base;
    }

    int count(int i){return pow(base, i);}

    double calculatet0(int i){
      //std::cout << " 0 from " << i << std::endl;
      double ret = 0.0;
      double step = (end - beg) / count(i);
      ret += func(beg) / 2;
      ret += func(end) / 2;
#pragma omp parallel
      for(int j = 1; j < count(i) - 1; j ++){
        double temp = func(beg + j * step);
        int_res.push(temp);
      }
      while(!int_res.empty()){
            ret += int_res.top();
            int_res.pop();
      }
      ret *= step;
      return ret;
    }
    
    double solve(){
      return calculateti(depth, depth);
    }

    double calculateti(int i, int j){
      //std::cout << i << " " << j << std::endl;
      //if (cache[j * depth + i] != 0.0){
         //return cache[j * depth + i];
      //}
      if(j == 0){
        double ret = calculatet0(i);
        // cache[j * depth + i] = ret;
        return ret;
      }

      else{
        double ret = 0.0;
        double part1 = calculateti(i, j-1);
        double part2 = calculateti(i-1, j-1);
        double denom = pow(count(i) / count(i-j), 2.0) - 1;

        ret = part1 + (part1 - part2) / denom;
        //cache[j * depth + i] = ret;
        return ret;
      }
      
    }
};

double sinxdivx(double val){
  return val == 0 ? 1.0f : sin(val) / val;
}

int main(){
  std::cout << "Podaj wartosc M" << std::endl;
  int m;
  std::cin >> m;
  double beg;
  std::cout << "Podaj wartosc poczatku przedzialu" << std::endl;
  std::cin >> beg;
  double end;
  std::cout << "Podaj wartosc konca przedzialu" << std::endl;
  std::cin >> end;
  std::cout << "Podaj baze potengowania ilosci przedzialow" << std::endl;
  int base;
  std::cin >> base;

  for (int i = 2; i < m; i++){
    solver  s (beg, end, i, sinxdivx, base);
    std::cout << "Result " << s.solve() << std::endl;
  }
}
