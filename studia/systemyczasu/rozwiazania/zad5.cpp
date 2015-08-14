#include<iostream>
#include <chrono>
#include <iomanip>
#include <list>


using namespace std;

uint16_t crc_next(uint16_t crc, uint8_t data)

{
    uint8_t it;
    crc ^= (uint16_t)data << 7;
    for (it = 0; it < 8; it++) {
        crc <<= 1;
        if (crc & 0x8000) {
            crc ^= 0xc599;
        }
    }
    return crc & 0x7fff;

}

 



int main(){

  unsigned int crc_reg = 0;
  std::string msg;
  std::cout << "podaj ciąg bitów do kodowania \n";
  std::cin >> msg; 

  unsigned int numrep = 0;
  std::cout << "podaj ilość powtórzeń obliczeń\n";
  std::cin >> numrep; 
  int msglen = msg.size();
  if (msglen > 96){
    std::cout << "wiadomość za długa \n";
    return 0;
  }
  for(int i = 0; i < msglen; i++){
    if ((msg[i] - 0x30) < 0 || (msg[i] - 0x30) > 1){
      std::cout << "niewłaściwy znak podaj jedynie 1 i 0\n";
      return 0;
    }
  }
 

  list<uint8_t> data;
  uint8_t cur = 0;
  for ( int i = 0; i < msglen; i++){
    cur <<= 1;
    cur += (msg[i] - 0x30);
    if( (i + 1) % 8 == 0){
      data.push_back(cur); 
      cur = 0;
    }
  } 
  if(msglen %8 != 0){
    data.push_back(cur); 
  }

  uint16_t crc = 0;
  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  for (int j = 0; j < numrep; j++){
    for ( auto cur = data.begin(); cur != data.end(); cur++){
      crc = crc_next(crc, *cur);
    }
  }
  

  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  
  std::cout << "Czas trwania ms = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() <<
    "." << (chrono::duration_cast<chrono::nanoseconds> (end - begin).count() % 1000) << "ms" <<std::endl;
  std::cout << "Czas sredni wykonania = " <<
    "." << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() / numrep << "us" <<std::endl;
  std::cout  << "0x" << std::hex << (crc ) << std::endl;

}
