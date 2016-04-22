#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "memory.hpp"

namespace mars {

unsigned int memory::memsize = 8000;
unsigned int memory::memoffset = 5000;

memory::memory() : mem(memory::memsize), programs(){
  
}

void memory::print(unsigned int location){
  std::cout << mem.at(location) << std::endl;
};

void memory::load_all(std::vector<program> warriors){
  boost::random::random_device rng;
  boost::random::uniform_int_distribution<> rand(1, memsize);
  std::vector<unsigned int> locations;
  bool intersect;
  do {
    locations.clear();
    for(int i = 0; i < warriors.size(); i ++){
      locations.push_back(rand(rng));
      //std::cout << locations.at(i) << " ";
    }
    for(int i = 0; i < warriors.size(); i ++){
      intersect = false;
      for(int j = 0; j < warriors.size(); j ++){
        for(int k = 0; k < warriors.size(); k ++){
          if(j != k){
            if(locations.at(j) + warriors.at(j).instructions.size() % memsize > locations.at(k) &&
                locations.at(j) < locations.at(k)) {
              intersect = true;
            }
          }
        }
      }
    }
  } while(intersect);
  for(int i = 0; i < warriors.size(); i++){
    load(locations.at(i), warriors.at(i));
  }
}

void memory::load(unsigned int where, program p){
  for(int i = 0; i < p.instructions.size(); i++){
    mem.at(i + where) = p.instructions.at(i);
  }
  std::queue<process> newprog;
  programs.push_back(newprog);
  process tmp(where);
  programs.at(programs.size() - 1).push(tmp);
}

unsigned int memory::resolve_adr(address which, unsigned int where){
  unsigned int ret = where;
  if(which.mode == address::modes::IMMIDIATE) {
    if(which.offset < 0){
      throw command_invalid("IMMIDIATE address < 0"); 
    } else {
      ret = which.offset;
    }
  } else if (which.mode == address::modes::DIRECT) {
    ret += which.offset;
  } else if (which.mode == address::modes::INDIRECT_B) {
    int tmp = mem.at((which.offset + ret) % memsize).address_b.offset;
    ret += tmp;
  } else if (which.mode == address::modes::PREDECREMENT_B) {
    mem.at((which.offset + ret) % memsize).address_b.offset--;
    int tmp = mem.at((which.offset + ret) % memsize).address_b.offset;
    ret += tmp;
  } else if (which.mode == address::modes::POSTINCREMENT_B) {
    int tmp = mem.at((which.offset + ret) % memsize).address_b.offset;
    mem.at((which.offset + ret) % memsize).address_b.offset++;
    ret += tmp;
  } else if (which.mode == address::modes::INDIRECT_A) {
    int tmp = mem.at((which.offset + ret) % memsize).address_a.offset;
    ret += tmp;
  } else if (which.mode == address::modes::PREDECREMENT_A) {
    mem.at((which.offset + ret) % memsize).address_a.offset--;
    int tmp = mem.at((which.offset + ret) % memsize).address_a.offset;
    ret += tmp;
  } else if (which.mode == address::modes::POSTINCREMENT_A) {
    int tmp = mem.at((which.offset + ret) % memsize).address_a.offset;
    mem.at((which.offset + ret) % memsize).address_a.offset++;
    ret += tmp;
  }
  //std::cout << ret << std::endl;
  return ret % memsize;
}

void memory::exec_command(unsigned int which, process &proc){
  bool valid = true;
  try {
    //std::cout << "executing at " << proc.exec_addr << std::endl;
    instruction cur_instr = mem.at(which % memsize);
    std::cout << cur_instr << std::endl;
    proc.exec_addr ++; 
    proc.exec_addr %= memsize; 
    //std::cout << cur_instr << std::endl;
    
    unsigned int addr_a = resolve_adr(cur_instr.address_a, which);
    unsigned int addr_b = resolve_adr(cur_instr.address_b, which);
    
    if(cur_instr.kind == instruction::kinds::DAT){
      valid = false;
    } else if (cur_instr.kind == instruction::kinds::MOV) {
      mem.at(addr_b) = mem.at(addr_a);
    } else if (cur_instr.kind == instruction::kinds::ADD) {
    } else if (cur_instr.kind == instruction::kinds::SUB) {
    } else if (cur_instr.kind == instruction::kinds::MUL) {
    } else if (cur_instr.kind == instruction::kinds::DIV) {
    } else if (cur_instr.kind == instruction::kinds::MOD) {
    } else if (cur_instr.kind == instruction::kinds::JMP) {
      proc.exec_addr = addr_a;
    } else if (cur_instr.kind == instruction::kinds::JMZ) {
    } else if (cur_instr.kind == instruction::kinds::JMN) {
    } else if (cur_instr.kind == instruction::kinds::DJN) {
    } else if (cur_instr.kind == instruction::kinds::SPL) {
    } else if (cur_instr.kind == instruction::kinds::SLT) {
    } else if (cur_instr.kind == instruction::kinds::CMP) {
    } else if (cur_instr.kind == instruction::kinds::SEQ) {
    } else if (cur_instr.kind == instruction::kinds::SNE) {
    } else if (cur_instr.kind == instruction::kinds::NOP) {
    } else if (cur_instr.kind == instruction::kinds::LDP) {
    } else if (cur_instr.kind == instruction::kinds::STP) {
    }
  } catch (command_invalid in) {
    valid = false;
    std::cout << in.why << std::endl;
  }
  if(valid){
    programs.at(turn).push(proc);
  }

}

void memory::exec_turns(int howmany){
  std::cout << "executing turns: " << howmany << std::endl;
  for(int i = 0; i < howmany; i ++){
    int tmp = 0;
    int stilalive = 0;
    for(int j = 0; j < programs.size(); j++){
      turn = j;
      if(!programs.at(j).empty()){
        process exec = programs.at(j).front();
        programs.at(j).pop();
        exec_command(exec.exec_addr, exec);
        stilalive ++;
        tmp = j;
      }
    }
    if(stilalive == 1){
      std::cout << "winner is warrior number" << tmp << std::endl; 
      return;
    } else if(stilalive == 0){
      std::cout << "draw" << tmp << std::endl; 
      return;
    }
  }
}

}
