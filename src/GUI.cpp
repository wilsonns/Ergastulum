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
    con->printf(1, 2, "Forca:%i", engine.jogador->atacador->forca);

   

    int y = 1;
    if (log.size() <= 5) {
        for (Mensagem mensagem:log)
        {
            con.setDefaultForeground(mensagem.cor);
            con.printf(X_MENSAGEM, y, mensagem.texto);
            y++;
        }
    }
    else if (log.size() > 5)
    {
        for (Mensagem* mensagem = log.end()-5;mensagem != log.end();mensagem++)
        {
            con->setDefaultForeground(mensagem->cor);
            con->printf(X_MENSAGEM, y, mensagem->texto);
            y++;
        }
    }
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
    con->printf(x + largura / 2, y,TCOD_BKGND_NONE, TCOD_CENTER,"%s:%i/%i",engine.jogador->nome,valor,valormax);
}


void GUI::mensagem(const TCODColor& cor, const char* texto, ...)
{
    va_list ap;
    char buf[128];
    va_start(ap, texto);
    vsprintf(buf, texto, ap);
    va_end(ap);

    char* lineBegin = buf;
    char* lineEnd;
    do {
        // make room for the new message
        /*if (log.size() == ALTURA_PAINEL_MSG) {
            Mensagem* toRemove = log.get(0);
            log.remove(toRemove);
            delete toRemove;
        }*/

        // detect end of the line
        lineEnd = strchr(lineBegin, '\n');
        if (lineEnd) {
            *lineEnd = '\0';
        }

        // add a new message to the log
        Mensagem* msg = new Mensagem(lineBegin, cor);
        log.push_back(msg);

        // go to next line
        lineBegin = lineEnd + 1;
    } while (lineEnd);
}