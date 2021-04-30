#ifndef LOGGER_H
#define LOGGER_H
#include <main.h>

struct Mensagem;

class LOGGER
{
    public:
        LOGGER();
        virtual ~LOGGER();
        std::ofstream debug;
        std::ofstream log;
        void debugLog(std::string texto, ...);
        void msgLog(Mensagem mensagem);
    protected:

    private:
};

#endif // LOGGER_H
