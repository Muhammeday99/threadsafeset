#include "set.h"
#include <iostream>
#include<chrono>
#include <random>
#include <thread>
#include <vector>


ThreadSafeSet<int> mySet;
std::vector<int> toInsert;
void insert(const int id){
  while(toInsert.size() > 0){
    std::cout << "T" << id << ": inserting to set" << std::endl;
    if(mySet.insert(toInsert[toInsert.size()-1])){
      std::cout << "T" << id << ": inserted to set" << std::endl;
    }else {
      std::cout << "T" << id << ": failed to insert to set" << std::endl;
    }
    toInsert.pop_back();
    std::cout << toInsert.size() << std::endl;
  }
}

int main(){
  std::chrono::time_point<std::chrono::system_clock> start, end;

  start = std::chrono::system_clock::now();
  
  

  for (size_t i = 0; i < 10; i++)
  {
    toInsert.push_back((std::rand() % 1000) + 1);
  }
  std::cout << toInsert.size() << std::endl;
  std::vector<std::thread> tv;
  for (size_t i = 0; i < 10; i++)
  {
    tv.push_back(std::thread(insert,i));
  }

  for(size_t i = 0; i < 10; i++){
    tv[i].join();
  }
  end = std::chrono::system_clock::now();
  
  std::chrono::duration<double> elapsed_seconds = end - start;

  std::cout << elapsed_seconds.count() << std::endl;

  // start = std::chrono::system_clock::now();

  // mySet.find(10000);

  // end = std::chrono::system_clock::now();
  
  // elapsed_seconds = end - start;

  // std::cout << elapsed_seconds.count() << std::endl;

  return 0;
}