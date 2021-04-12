#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED


extern int LARGURA_TERM;
extern int ALTURA_TERM;

#include<iostream>
#include"libtcod.hpp"
#include<time.h>
#include<vector>
#include<cmath>
#include<list>
#include<stdarg.h>
#include<typeinfo>
#include<nlohmann/json.hpp>
#include<fstream>

using json = nlohmann::json;

class Destrutivel;
class Atacador;
class AI;
class Pegavel;
class Container;
class Pathfinding;
class Entidade;
struct Tile;
class Mapa;
class Engine;
class LOGGER;
class GUI;
class Stats;
class Habilidade;

#include<Destrutivel.h>
#include<Atacador.h>
#include<AI.h>
#include<Pegavel.h>
#include<Container.h>
#include<Pathfinding.h>
#include<Entidade.h>
#include<Mapa.h>
#include<Engine.h>
#include<LOGGER.h>
#include<GUI.h>
#include<Stats.h>

#endif // MAIN_H_INCLUDED
