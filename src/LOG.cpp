#include "LOG.h"
#include <main.h>

LOG::LOG()
{
    abrir();
    //ctor
}

void LOG::abrir()
{
    myfile.open("debug.txt");
}

LOG::~LOG()
{
    //dtor
}

void LOG::inserirmsg(std::string txt,...)
{
    myfile << txt << std::endl;
}
