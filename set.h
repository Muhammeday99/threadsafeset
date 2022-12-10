#ifndef SET_H_

#include <stdlib.h>
#include <vector>
#include <iostream>
#include <functional>
#include <mutex>
#include <condition_variable>

template <class T>
class ThreadSafeSet{
  public:
    ThreadSafeSet();
    ThreadSafeSet(const ThreadSafeSet &other);
    ~ThreadSafeSet();

    bool insert(const T &element);
    bool insert(T &&element);
    bool remove(const T &element);
    bool find(const T &element);
    void iterate(std::function<void(const T&)>);
    
    inline T get(int index){return this->container[index];};
    inline int getSize(){return size;};

    template <class U>
    friend std::ostream &operator<<(std::ostream &os, const ThreadSafeSet<U> &set);

  private:
    std::vector<T> container;
    int size;
    int index;
    bool exists(const T &element);
    std::mutex m_mutex;
    std::condition_variable m_localCV;
};

template <class T>
ThreadSafeSet<T>::ThreadSafeSet()
{
  size = 0;
}

template <class T>
ThreadSafeSet<T>::ThreadSafeSet(const ThreadSafeSet &other)
{
  this->container = other.container;
}

template <class T>
ThreadSafeSet<T>::~ThreadSafeSet()
{
  
}

template <class T>
bool ThreadSafeSet<T>::insert(const T &element)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  if(size == 0){
    this->container.push_back(element);
    size++;
    return true;
  }
  if (find(element))
  {
    return false;
  }
  size++;
  std::vector<T> temp;
  int j=0;
  for (size_t i = 0; i < size; i++)
  {
    
    if (i == index)
    {
      temp.push_back(element);
    }
    else
    {
      temp.push_back(this->container[j]);
      j++;
    }
  }

  this->container = temp;
  return true;
}

template <class T>
bool ThreadSafeSet<T>::insert(T &&element){
  std::lock_guard<std::mutex> lock(m_mutex);
  if(size == 0){
    this->container.push_back(std::move(element));
    size++;
    return true;
  }
  if (find(element))
  {
    return false;
  }
  size++;
  std::vector<T> temp;
  int j=0;
  for (size_t i = 0; i < size; i++)
  {
    
    if (i == index)
    {
      temp.push_back(std::move(element));
    }
    else
    {
      temp.push_back(this->container[j]);
      j++;
    }
  }

  this->container = temp;
  return true;
}

template <class T>
bool ThreadSafeSet<T>::remove(const T &element)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  if (find(element))
  {
    std::vector<T> temp;
    for (size_t i = 0; i < size; i++)
    {
      if (i == index)
      {
        continue;
      }
      else
      {
        temp.push_back(this->container[i]);
      }
    }
    this->container = temp;
    size--;
    return true;
  }
  return false;
}

template <class T>
bool ThreadSafeSet<T>::find(const T &element)
{
  if(size == 0){
    return false;
  }
  int l = 0;
  int r = this->size - 1;
  int mid;
    
  while (l < r)
  {
    mid = (l + r) / 2;
    if (this->container[mid] < element)
    {
      l = mid + 1;
    }
    else
    {
      r = mid;
    }
  }
  if (this->container[l] == element)
  {
    this->index = l;
    return true;
  }
  else if (this->container[r] == element)
  {
    this->index = r;
    return true;
  }
  if(this->container[l] < element){
    this-> index = l+1;
  }else
    this->index = l;

  return false;
}

template <class T>
void ThreadSafeSet<T>::iterate(std::function<void(const T&)> func){
    std::lock_guard<std::mutex> lock(m_mutex);
    for(auto e : container){
      func(e);
    }
};

template <class U>
std::ostream &operator<<(std::ostream &os, const ThreadSafeSet<U> &set)
{
  try
  {
    os << "[";
    for (size_t i = 0; i < set.container.size(); i++)
    {
      os << set.container[i] << " ";
    }
    os << "]" << std::endl;
  }
  catch (std::exception e)
  {
    os << e.what() << std::endl;
  }
  return os;
}


#endif

