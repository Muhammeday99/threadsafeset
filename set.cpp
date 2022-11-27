#include "set.h"

template <class T>
ThreadSafeSet<T>::ThreadSafeSet()
{
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
  if (find(element))
  {
    return false;
  }
  std::vector<T> temp;
  for (size_t i = 0; i < this->container.size(); i++)
  {
    if (i == index)
    {
      temp.push_back(element);
      i--;
    }
    else
    {
      temp.push_back(this->container[i]);
    }
  }

  this->container = temp;
  return true;
}

template <class T>
bool ThreadSafeSet<T>::remove(const T &element)
{
  if (find(element))
  {
    std::vector<T> temp;
    for (size_t i = 0; i < this->container.size(); i++)
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
    return true;
  }
  return false;
}

template <class T>
bool ThreadSafeSet<T>::find(const T &element)
{
  int l = 0;
  int r = this->container.size() - 1;
  int mid;
  while (l < r)
  {
    mid = l + r / 2;
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
  if (this->container[l] < element)
    this->index = l + 1;
  else
    this->index = l;

  return false;
}

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
