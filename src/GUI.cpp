#include "GUI.h"
#include <main.h>

GUI::GUI()
{
    msgs = newwin(2,2,0,0);
    //ctor
}

GUI::~GUI()
{
    //dtor
}

void GUI::render()
{
    box(msgs, 0, 0);
    mvwprintw(msgs, 1, 1, "TESTE DESGRAÇA");
    refresh();
    wrefresh(msgs);
    refresh();
}