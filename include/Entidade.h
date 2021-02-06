#ifndef ENTIDADE_H
#define ENTIDADE_H
#include <main.h>

struct Nodo; //FORWARD DO NODO DECLARADO EM PATHFINDING.H

class Entidade
{
    public:
        //POSIÇÃO
        int x, y;
        char simbolo;
        int visao;
       
        const float GRAUPRAD = 3.14159f / 180;

        const char *nome; //Nome da entidade
        bool denso;//pode-se passar por essa entidade?

        Atacador *atacador;
        Destrutivel *destrutivel;
        AI *ai;
        Pathfinding* path;

        std::vector<Nodo*> caminho;

        Entidade(int x, int y,const char *nome, char simbolo);//CTOR

        virtual ~Entidade(); //DTOR

        void render(); //Desenha a entidade na tela

        void atualizar();

        
        /// FOV
        
        float maximo(float a, float b);
        
        int distanciaDiag(int x0, int y0, int x1, int y1);

        float lerp(float inicio, float fim, float t);

        void FOV();

        void fazerFOV(float i, float j, int v);

    protected:

    private:
};

#endif // ENTIDADE_H
