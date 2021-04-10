#ifndef LOGGER_H
#define LOGGER_H
#include <main.h>

class LOGGER
{
    public:
        LOGGER();
        virtual ~LOGGER();
        std::ofstream debug;
        std::ofstream log;
        void logar(std::ofstream arquivo, std::string texto, ...);
    protected:

    private:
};

#endif // LOGGER_H
