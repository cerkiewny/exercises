#include<iostream>
#include<sstream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

struct numb{
  string whole;
  int len;
  int sign;
};


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

bool grtr(numb lh, numb rh){
  for(int i = 0 ; i < lh.whole.size(); i ++){
    if (lh.whole[i] > rh.whole[i]){
      return true;
    } if (lh.whole[i] < rh.whole[i]){
      return false;
    }
 }
  return false;
}

numb add(numb lh, numb rh){
  numb ret;
  ret.len = rh.len;
  if(!grtr(lh,rh)){
    swap(lh, rh);
  }
  ret.sign = lh.sign;
  int carry = 0;
  int i = rh.whole.size() - 1;
  while(i >= 0){
    char a, b;
    if(i >= rh.whole.size()){
      b = '0';
    } else {
      b = rh.whole[i];
    }
    if(i >= lh.whole.size()){
      a = '0';
    } else {
      a = lh.whole[i];
    }
    //cout << "chars " <<  a << " " << b << endl;
    char res = (a - 48) + lh.sign * rh.sign * (b - 48);
    if (carry)
      res+=carry;
    carry = 0;
    if(res < 0){
      res += 10;
      carry = -1;
    }
    if(res > 9){
      res -= 10;
      carry = +1;
    }
    ret.whole.insert(0,1,(char(res + 48)));
    i--;
  }
  if(carry){
    ret.whole.insert(0,1,'1');
  }

  return ret;
}

int main(){
  int n;

  cin >> n;
  numb res;
  res.whole = "0";
  res.len = 0;
  res.sign  = 1;
  string tmp;
  for(int i = 0; i < n; i++){
    cin >> tmp;
    std::vector<std::string> sv = split(tmp, ',');
    numb a;
    a.sign = 1;
    if(sv[0][0] == '-'){
      a.sign = -1;
      sv[0].erase(0,1);
    } else if(sv[0][0] == '+'){
      sv[0].erase(0,1);
    } 
    a.whole = sv[0];
    if(sv.size() > 1){
      a.whole += sv[1];
      a.len = sv[1].size();
      //cout << " len " << a.len << endl;
     } else
      a.len= 0;
    while(res.len > a.len){
      a.len++;
      a.whole.push_back('0');
    }
    while(res.len < a.len){
      res.len++;
      res.whole.push_back('0');
    }
    while(res.whole.size() < a.whole.size()){
      res.whole.insert(0, 1, '0');
    }
    while(res.whole.size() > a.whole.size()){
      a.whole.insert(0, 1, '0');
    }
    //cout << res.whole << " " << a.whole << endl;
    res = add(res, a);
    //cout << res.sign << " " << res.whole << ' ' << res.len << endl; 
  }
  while(res.whole[res.whole.size() - 1] == '0' && res.len > 0){
    res.whole = res.whole.substr(0, res.whole.size()-1);
    res.len --;
  }
  while(res.whole.size() > res.len + 1 && res.whole[0] == '0'){
    res.whole = res.whole.substr(1, res.whole.size());
  }
  if(res.len != 0){
    res.whole.insert(res.whole.size() - res.len, 1, ',');
  }
  if(res.sign == -1 && res.whole != "0")
    cout << '-';
  cout << res.whole << endl; 

}
