#include <main.h>
#include <time.h>

Engine engine(80, 50);

int main()
{
    srand(time(NULL));
    engine.debug = false;
    auto root = TCODConsole::root;

    while(engine.rodando == true)
    {
        if (TCOD_console_is_window_closed())
        {
            break;
            
        }
        engine.atualizar();
        engine.render();
    }
    return 0;
}