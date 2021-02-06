#ifndef LOG_H
#define LOG_H
#include <main.h>

class LOG
{
    public:
        LOG();
        virtual ~LOG();

        std::ofstream myfile;

        void abrir();

        void inserirmsg(std::string txt,...);

    protected:

    private:
};

#endif // LOG_H
