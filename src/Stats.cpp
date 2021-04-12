#include "Stats.h"
#include "main.h"

Stats::Stats()
{
	nivelBase = 1;
	nivelAjustado = nivelBase;
	//ctor
}

Habilidade::Habilidade()
{
	nivelBase = 1;
	nivelAjustado = nivelBase;
	xp = 0;
	xpProx = int(pow((100 * nivelBase), 1.5));
}
