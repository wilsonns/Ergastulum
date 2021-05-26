#ifndef CORPO_H
#define CORPO_H

#include<main.h>

class Parte
{
  public:
    Parte* pai;
    std::vector<Parte*> filhos;
    int hp;
    int maxHp;
};

#endif // CORPO_H

