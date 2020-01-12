#include "utility.hh"
using namespace std;

int tirage_aleatoire(size_t size_vect){
  return int(rand()%(size_vect));
}

/*template <class T,class U>
vector<T*> operator+(vector<T*> lhs, U* rhs)
{
  lhs.push_back(rhs);
  return lhs;
}

template <class T,class U>
list<T*> operator+(list<T*> lhs, U* rhs)
{
  lhs.push_back(rhs);
  return lhs;
}*/
