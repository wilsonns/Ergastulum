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

    renderBarra(1, 1, LARGURA_BARRA, engine.jogador->getAtributo("PV"), engine.jogador->getAtributo("PVmax"), TCOD_light_red, TCOD_darker_red);
    renderBarra(1, 2, LARGURA_BARRA, engine.jogador->getAtributo("PF"), engine.jogador->getAtributo("PFmax"), TCOD_light_yellow, TCOD_darker_yellow);
    renderBarra(1, 3, LARGURA_BARRA, engine.jogador->getAtributo("Mana"), engine.jogador->getAtributo("Manamax"), TCOD_light_blue, TCOD_darker_blue);

    con->printf(1, 0, "%s", engine.jogador->nome.c_str());
    /*con->printf(1, 3, "Arma:%s", engine.jogador->container->arma? engine.jogador->container->arma->nome.c_str():"Desarmado");
    */
   

    int y = 1;
    float coefCor = 0.2f;
    if (log.size() > 5)
    {
        Mensagem* mensagem = *log.begin();
        engine.logger->msgLog(*mensagem);
        log.erase(log.begin());
    }
    
        for (std::vector<Mensagem*>::iterator it = log.begin();it != log.end();it++)
        {
            Mensagem* mensagem = *it;
            con->setDefaultForeground(mensagem->cor*coefCor);
            con->printf(X_MENSAGEM, y, mensagem->texto.c_str());
            y++;
            if (coefCor < 1.0f)
            {
                coefCor += 0.2f;
            }
        }
    renderMouse();
    TCODConsole::blit(con, 0, 0, engine.largura, ALTURA_PAINEL, 
        TCODConsole::root, 0, engine.altura - ALTURA_PAINEL);
    if (janela)
    {
        janela->con->printFrame(0, 0, janela->largura, janela->altura,true, TCOD_BKGND_DEFAULT, janela->titulo.c_str());
        TCODConsole::blit(janela->con, 0, 0, janela->largura, janela->altura, TCODConsole::root, janela->posx, janela->posy, 0.7, 0.7);
    }
}///Desenha a moldura da UI

void GUI::renderBarra(int x, int y, int largura, int valor, int valormax, const TCODColor& corBarra, const TCODColor& corFundo, bool nome)
{
    con->setDefaultBackground(corFundo);
    con->rect(x, y, largura, 1, false, TCOD_BKGND_SET);

    float larguraBarra = ((float)valor / (float)valormax) * largura;

    if (larguraBarra > 0)
    {
        con->setDefaultBackground(corBarra);
        con->rect(x, y, larguraBarra, 1, false, TCOD_BKGND_SET);
    }

    con->setDefaultForeground(TCOD_white);
    con->printf(x + largura / 2, y, TCOD_BKGND_NONE, TCOD_CENTER, "%i/%i", valor, valormax);

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

Janela* GUI::criarJanela(std::string titulo, int largura, int altura, int posx, int posy)
{
    Janela* janela = new Janela(titulo, largura, altura, posx, posy);

    return janela;
}