#ifndef GUI_H
#define GUI_H

#include <main.h>

class GUI
{
    public:
        GUI();//ctor
        virtual ~GUI();//dtor
        WINDOW* msgs;//cria a janela de mensagens da interface
 
        void render();//desenhar a interface na tela

    protected:

    private:
};

#endif // GUI_H
