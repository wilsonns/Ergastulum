#include "GUI.h"
#include <main.h>

GUI::GUI()
{
    con = new TCODConsole(engine.largura, 7);
    //ctor
}

GUI::~GUI()
{
    delete con;
    log.clear();
    //dtor
}

void GUI::render()
{
    con->setDefaultBackground(TCOD_lighter_gray);
    con->clear();

    renderBarra(1, 1, LARGURA_BARRA, engine.jogador->destrutivel->hp, engine.jogador->destrutivel->hpMax, TCOD_light_red, TCOD_darker_red);
    con->printf(1, 2, "Forca:%i", engine.jogador->atributos["Forca"]->nivelAjustado);

   

    int y = 1;
    if (log.size() > 5)
    {
        log.erase(log.begin());
    }
    
        for (std::vector<Mensagem*>::iterator it = log.begin();it != log.end();it++)
        {
            Mensagem* mensagem = *it;
            con->setDefaultForeground(mensagem->cor);
            con->printf(X_MENSAGEM, y, mensagem->texto.c_str());
            y++;
        }
    renderMouse();
    TCODConsole::blit(con, 0, 0, engine.largura, ALTURA_PAINEL, 
        TCODConsole::root, 0, engine.altura - ALTURA_PAINEL);
}///Desenha a moldura da UI

void GUI::renderBarra(int x, int y, int largura, int valor, int valormax, const TCODColor& corBarra, const TCODColor& corFundo)
{
    con->setDefaultBackground(corFundo);
    con->rect(x, y, largura, 1, false, TCOD_BKGND_SET);

    int larguraBarra = valor / valormax * largura;
    if (larguraBarra > 0)
    {
        con->setDefaultBackground(corBarra);
        con->rect(x, y, largura, 1, false, TCOD_BKGND_SET);
    }
    con->setDefaultBackground(TCOD_white);
    con->printf(x + largura / 2, y, TCOD_BKGND_NONE, TCOD_CENTER, "%s:%i/%i", engine.jogador->nome.c_str(), valor, valormax);
}


void GUI::mensagem(const TCODColor& cor, std::string texto, ...)
{
    va_list ap;//declara a lista de variáveis variádicas(os "...")
    va_start(ap, texto);//define a lista de variáveis variádicas(ap) e após qual variável se iniciam as variáveis variádicas(texto)
    std::string busca = "{}";//A variável que vai ser substituída pelo texto no loop while abaixo
    while (texto.find(busca)!=std::string::npos)
    {
        std::size_t ini = texto.find(busca);
        texto.erase(ini, busca.length());
        texto.insert(ini, va_arg(ap, std::string));
    }

    va_end(ap);//encerra a lista de variáveis variádicas
    Mensagem* msg = new Mensagem(texto, cor);
    log.push_back(msg);
}

void GUI::renderMouse()
{
    if (!engine.mapa->estaNoFOV(engine.mouse.cx, engine.mouse.cy))
    {
        return;
    }
    std::string buf;
    bool primeiro = true;

    if (TCOD_console_has_mouse_focus())
    {
        for (std::vector<Entidade*>::iterator it = engine.entidades.begin();it != engine.entidades.end();it++)
        {
            Entidade* entidade = *it;
            {
                int x = engine.mouse.cx;
                int y = engine.mouse.cy;

                if (entidade->x == x && entidade->y == y)
                {
                    if (!primeiro)
                    {
                        buf += ",";
                    }
                    else
                    {
                        primeiro = false;
                    }
                    buf += entidade->nome.c_str();
                }
            }
        }
    }
    con->setDefaultForeground(TCOD_white);
    con->printf(1, 0, buf.c_str());
}