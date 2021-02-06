#include <main.h>


Engine engine;


int main()
{
    
    initscr();
    noecho();
    raw();

    start_color();

    init_pair(1, 15, 0); //CINZA ESCURO
    init_pair(2, 8, 0); // BRANCO
    init_pair(3, 10, 0);//VERDE
    init_pair(4, 12, 0);//vermelho
 
    
    keypad(stdscr, true);

    for (int x = 1; x < 10; x++)
    {
        for (int y = 1; y < 10; y++)
        {
            engine.mapa->cavar(x, y);
        }
    }

    for (int x = 15; x < 22; x++)
    {
        for (int y = 1; y < 10; y++)
        {
            engine.mapa->cavar(x, y);
        }
    }

    for (int x = 1; x < 16; x++)
    {
        engine.mapa->cavar(x, 8);
    }

    engine.adcmonstro(5, 5);
    while (engine.rodando == true)
    {
        engine.render();
        engine.atualizar();
    }

    clear();


    endwin();

    return 0;
}
