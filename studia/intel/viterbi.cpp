#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

vector<string> &split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

class observation{
  public:
    string name;
    float prop;
};

class state{

  public:
    state(int n) {
      emmision_prob = new float[n](); 
    }
    string name;
    float init_prop;
    float * emmision_prob;
    std::vector<observation *> observ;
    int state_c;
  
};


void viterbi(vector<state *> states, string in, string out){
  for(int i = 0; i < states.size();i ++){
    cout << states[i]->name << endl; 
    for(int j = 0; j < states[i]->observ.size(); j ++){
      cout << states[i]->observ[j]->name;
      cout << states[i]->observ[j]->prop;
      cout << endl;
    }
  }
  
  ifstream infile;
  infile.open(in);
  ofstream res;
  res.open(out);
  string curline;

  vector < vector < float >  * > V; 
  getline(infile, curline); 
  vector<float> * iniProp;
  vector< vector < int > * > * paths;
  paths = new vector< vector < int > * >();
  //for i in states
  for(int i = 0; i < states.size(); i++){
    iniProp = new vector<float>();
      int observ_in;
      for( observ_in = 0; observ_in < states[i]->observ.size(); observ_in++){
        if(states[i]->observ[observ_in]->name == curline)
          break;
      }
    iniProp->push_back(states[i]->init_prop * states[i]->observ[observ_in]->prop);
    cout <<  states[i]->init_prop * states[i]->observ[observ_in]->prop << endl;

    paths->push_back(new vector< int > ());
    (paths[0])[i]->push_back(i);;
  }
  V.push_back(iniProp);
  while(getline(infile, curline)){
    vector< vector < int > * > * newpaths;
    newpaths = new vector< vector < int > * >();
    for(int i = 0; i < states.size(); i++){
      newpaths->push_back(new vector< int > ());
      iniProp = new vector<float>();
      int beststate;
      int observ_in;
      for( observ_in = 0; observ_in < states[i]->observ.size(); observ_in++){
        if(states[i]->observ[observ_in]->name == curline)
          break;
      }
      float prob = 0.0;
      for(int j = 0; j < states.size(); j++){
        if(prob < (*V[V.size() - 1])[j] * states[j]->emmision_prob[i] * states[i]->observ[observ_in]->prop){
          prob =  (*V[V.size() - 1])[j] * states[j]->emmision_prob[i] * states[i]->observ[observ_in]->prop;
          beststate = j;

        }
        V[V.size() - 1]->push_back(prob);
        newpaths[i] = paths[j];
        
      }
      //cout << states[0]->observ[beststate]->name << endl;
      iniProp->push_back(states[i]->init_prop * states[i]->observ[observ_in]->prop);
    }
    V.push_back(iniProp);
    
  }
  for(int i = 0 ; i < V.size(); i ++){
    for(int j = 0 ; j < V[i]->size(); j++){
      cout << (*V[i])[j] << " ";
    }
    cout << endl;
  }
  res.close();
  infile.close();

}


int main(){
 
  ifstream fprop;
  fprop.open("propagation.mat");
  string line;

  getline(fprop, line);
  vector<string> sline = split(line, ' ');

  int states_c = sline.size();

  vector<state *> states;

  for(int i = 0; i < states_c; i++){
    state * cur = new state(states_c);
    cur->name = sline[i];
    fprop >> cur->init_prop;
    states.push_back(cur);
  }   
  for(int i = 0; i < states_c; i++){
    for(int j = 0; j < states_c; j++){
      fprop >> states.at(i)->emmision_prob[j];
    }
  }   

  getline(fprop, line);
  getline(fprop, line);
  getline(fprop, line);

  vector<string> obsnames = split(line, ' ');
  for(int i = 0; i < states_c; i++){
    for(int j = 0; j < obsnames.size(); j++){
      observation * cur = new observation();
      cur->name = obsnames[j];
      fprop >> cur->prop;
      states[i]->observ.push_back(cur);

    }
  }
  string filename = "hmmtest.in";
  string outfile = "hmmtest.res";
  viterbi(states, filename, outfile);
}
