#ifndef GUI_H
#define GUI_H

#include <main.h>

class GUI
{
    public:
        GUI();
        virtual ~GUI();
        WINDOW* msgs;
        PANEL* pmsgs;
        
        void render();

    protected:

    private:
};

#endif // GUI_H
