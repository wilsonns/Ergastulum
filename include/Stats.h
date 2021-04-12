#ifndef STATS_H_INCLUDED
#define STATS_H_INCLUDED

class Stats
{
public:
	Stats();
	int nivelBase;
	int nivelAjustado;
};


class Habilidade : public Stats
{
public:
	Habilidade();
	void adcionarXp(int xp);
	int subirNivel();
	int xp, xpProx;
};

#endif // STATS_H_INCLUDED
