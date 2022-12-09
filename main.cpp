#include "set.h"
#include <iostream>
#include<chrono>
#include <random>
#include <thread>
#include <vector>
#include <string>

#define NUM_THREADS 5


ThreadSafeSet<int> mySet;
std::vector<int> toInsert;
void insert(const int id){
    int temp = toInsert[toInsert.size()-(id+1)]; 
    toInsert.pop_back();
    std::cout << "T" << id << ": inserting to set" << std::endl;
    if(mySet.insert(temp)){
      std::cout << "T" << id << ": inserted to set" << std::endl;
    }else {
      std::cout << "T" << id << ": failed to insert to set" << std::endl;
    }

    std::cout << mySet;
}

int main(){
  std::chrono::time_point<std::chrono::system_clock> start, end;

  start = std::chrono::system_clock::now();
  // std::string s = "abc";
  // mySet.insert(std::move(s));
  // std::cout << mySet;

  // mySet.iterate([](const std::string &str){
  //   std::cout << str + "ef" << std::endl;
  // });

  for (size_t i = 0; i < 10; i++)
  {
    toInsert.push_back((std::rand() % 1000) + 1);
  }
  std::cout << toInsert.size() << std::endl;
  std::vector<std::thread> tv;
  for (size_t i = 0; i < NUM_THREADS; i++)
  {
    tv.push_back(std::thread(insert,i));
  }

  for(size_t i = 0; i < NUM_THREADS; i++){
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