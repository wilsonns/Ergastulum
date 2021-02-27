#include <main.h>
#include <time.h>

Engine engine(80, 50);

/// <summary>
/// TELA X = 79
/// TELA Y = 24
/// </summary>
/// <returns></returns>
/// 96 a madarastara
/// 
int main()
{
    //engine.mapa->cavar(1, 10, 1, 10);
    //engine.mapa->adcmonstro(3, 3);
    //engine.mapa->adcmonstro(10, 10);
    srand(time(NULL));
    engine.debug = false;
    /*
    engine.mapa->adcionarItem(6, 6, '/', 2, "Espada", 5, TCOD_silver);
    engine.mapa->adcionarItem(5, 1, '!', 1, "Pocao", 5, TCOD_pink);
    engine.mapa->adcionarItem(5, 5, '/', 2, "Porrete", 3, TCOD_brass);
    */
    while (engine.rodando == true || !TCOD_console_is_window_closed())
    {
        engine.atualizar();
        engine.render();
        auto root = TCODConsole::root;
        root->flush();
    }

    
    return 0;
}