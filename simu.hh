/*#ifndef SIMU_HPP_
#define SIMU_HPP_

#include <iostream>
#include <vector>
#include "screen.hh"
#include "object.hh"

class Simu{
  Screen s;
  std::vector<Object*> vect_objet;

  public:
    Simu(float w,float h):s(Screen(w,h)){}
    ~Simu(){
      //for(size_t i=0;i<vect_objet.size();i++){
      //  delete vect_objet[i];
      //}
    }

    Simu& operator+=(Object* rhs);
    friend Simu operator+(Simu lhs,Object* rhs);
    void update();
};

#endif
*/
