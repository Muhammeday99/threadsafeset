#include "set.h"
#include <iostream>
#include <chrono>
#include <random>
#include <thread>
#include <vector>
#include <string>

#define NUM_THREADS 3

std::chrono::milliseconds timespan(200);

ThreadSafeSet<int> mySet;
std::vector<int> toInsert;
void insert(const int id)
{
  // int temp = toInsert[toInsert.size()-(id+1)];
  // toInsert.pop_back();
  int counter = 0;
  while (counter < 100)
  {
    int temp = (std::rand() % 100000) + 1;
    // std::cout << "T" << id << ": inserting to set" << std::endl;
    if (mySet.insert(temp))
    {
      // std::cout << "T" << id << ": inserted to set" << std::endl;
      toInsert.push_back(temp);
      counter++;
    }
    // else
    // {
    //   std::cout << "T" << id << ": failed to insert to set" << std::endl;
    // }
    
  }
}

void find(const int id)
{
  int counter = 0;
  while (counter < 100)
  {
    int temp = (std::rand() % 100) + 1;
    std::cout << "T" << id << ": finding " << temp << " in set" << std::endl;
    if (mySet.find(temp))
    {
      std::cout << "T" << id << ": found " << temp << " in set" << std::endl;
    }
    else
    {
      std::cout << "T" << id << ": failed to find " << temp << " in set" << std::endl;
    }
    counter++;
  }
}

void removeFromSet(const int id)
{
  int counter = 0;
  while (counter < 100)
  {
    if (toInsert.size() > 0)
    {
      // int rand = (std::rand() % toInsert.size());
      int temp = toInsert[toInsert.size()-1];
      std::cout << "T" << id << ": removing " << temp << " from set" << std::endl;
      if (mySet.remove(temp))
      {
        std::cout << "T" << id << ": removed " << temp << " from set" << std::endl;
        // toInsert[rand] = toInsert.back();
        toInsert.pop_back();
      }
      else
      {
        std::cout << "T" << id << ": failed to remove " << temp << " from set" << std::endl;
      }
      std::cout << toInsert.size() << std::endl;
      // std::this_thread::sleep_for(timespan);
      counter++;
    }
    
  }
}

int main()
{
  std::chrono::time_point<std::chrono::system_clock> start, end;

  start = std::chrono::system_clock::now();
  // std::string s = "abc";
  // mySet.insert(std::move(s));
  // std::cout << mySet;

  // mySet.iterate([](const std::string &str){
  //   std::cout << str + "ef" << std::endl;
  // });
  std::vector<std::thread> tv;
  // for (size_t i = 0; i < NUM_THREADS; i++)
  // {
  //   tv.push_back(std::thread(insert,i));
  // }

  // tv.push_back(std::thread(find,2));
  tv.push_back(std::thread(insert, 0));
  tv.push_back(std::thread(removeFromSet, 1));

  for (size_t i = 0; i < 2; i++)
  {
    tv[i].join();
  }
  end = std::chrono::system_clock::now();

  std::chrono::duration<double> elapsed_seconds = end - start;

  std::cout << elapsed_seconds.count() << std::endl;

  std::cout << mySet.getSize() << std::endl;
  if(mySet.getSize() < 30){
    std::cout << mySet;
    for(int a : toInsert){
      std::cout << a << ", ";
    }
    std::cout << std::endl;
  }
  // start = std::chrono::system_clock::now();

  // mySet.find(10000);

  // end = std::chrono::system_clock::now();

  // elapsed_seconds = end - start;

  // std::cout << elapsed_seconds.count() << std::endl;

  return 0;
}