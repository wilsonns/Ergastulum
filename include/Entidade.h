#ifndef ENTIDADE_H
#define ENTIDADE_H
#include <main.h>

struct Nodo; //FORWARD DO NODO DECLARADO EM PATHFINDING.H

class Entidade
{
    public:
        //POSIÇÃO
        int x, y;//posição x e y da entdidade
        char simbolo; //simnbolo desenhado
        int visao; //raio da visão da entidade
       
        const float GRAUPRAD = 3.14159f / 180; //Graus para radianos

        const char *nome; //Nome da entidade
        bool denso;//pode-se passar por essa entidade?

        Atacador *atacador; //é uma entidade capaz de atacar?
        Destrutivel *destrutivel; //é uma entidade mortal/destrutivel?
        AI *ai;//é uma entidade que se auto-atualiza?
        Pegavel* pegavel;//é uma entidade que pode ser pega e guardada em um contaienr?
        Container* container;//é uma entidade que pode guardar outras entidades?

        std::vector<Nodo*> caminho;//O caminho retornado pelas funções de pathfinding

        Entidade(int x, int y,const char *nome, char simbolo);//CTOR

        virtual ~Entidade(); //DTOR

        void render(); //Desenha a entidade na tela

        void atualizar();//chama a atualização da IA da entidade

        
        /// FOV
        
        float maximo(float a, float b);//retorna o valor maior
        
        int distanciaDiag(int x0, int y0, int x1, int y1);//retorna a distancia  entre os pontos

        float lerp(float inicio, float fim, float t);//retorna a interpolação linear

        void FOV();//realiza todos os calculos de FOV()

    protected:

    private:
};

#endif // ENTIDADE_H
