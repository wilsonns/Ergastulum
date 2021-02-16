#include <main.h>
#include <time.h>


Engine engine;

/// <summary>
/// TELA X = 79
/// TELA Y = 24
/// </summary>
/// <returns></returns>

int LARGURA_TERM = 90;
int ALTURA_TERM = 30;
int main()
{
    int px, py;
    px = py = 10;
    engine.mapa->cavar(1, 10, 1, 10);

    TCODConsole::initRoot(80, 50, "Joguim sem Nome do Will",false);
    srand(time(NULL));
    while (engine.rodando == true || !TCOD_console_is_window_closed())
    {
        engine.atualizar();
        engine.render();
        auto root = TCODConsole::root;
        /*
        TCOD_key_t key;
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &key, NULL);
        switch (key.vk)
        {
        case TCODK_UP:
            py--;
            break;
        case TCODK_DOWN:
            py++;
            break;
        case TCODK_LEFT:
            px--;
            break;
        case TCODK_RIGHT:
            px++;
            break;
        }
        root->putChar(px, py, '@', TCOD_BKGND_NONE);
        */
        root->flush();
    }

    
    return 0;
}