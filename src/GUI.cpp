#include "GUI.h"
#include <main.h>

GUI::GUI()
{
    msgs = newwin(5,COLS-2,LINES-6,0);
    pmsgs = new_panel(msgs);

    //ctor
}

GUI::~GUI()
{
    //dtor
}

void GUI::render()
{
    show_panel(pmsgs);
    update_panels();
    doupdate();
}