#ifndef DESTRUTIVEL_H
#define DESTRUTIVEL_H
#include <main.h>

class Destrutivel
{
    public:
        Entidade* self;

        int hpMax;//maximo de pontos de vida
        int hp;//pontos de vida atual
        
        /// Atributos
        int vigor; //A resistencia a doenças e a saúde geral do personagem
        int resistencia;//A quantidade de dano que o personagem subtrai do dano final
        int resistenciaBase; //
        int agilidade; //A capacidade de esquivar de um golpe
        int agilidadeBase;//
        
        std::string nomeCadaver;//o nome que a entidade terá quando morrer

        Destrutivel();
        Destrutivel(Entidade *self, std::string nomeCadaver = "Cadaver");//ctor
        inline bool morreu()
        {
            if(hp<=0)
            {
                return true;
            }
            return false;
        }//Retorna verdadeiro se tiver morrido, falso se não

        int tomarDano(int dano);//subtrai o dano sofrido dos pontos de vida atuais e retorna a quantidade de dano que foi causada

        int curar(int valor);//recupera pontos de vida da entidade e retorna a quantidade de pvs curados

        void morrer();//Função virtual que mata a entidade, tirando-a do vetor entidades e enfiando-a no vetor mortos

        virtual ~Destrutivel();//dtor

    protected:

    private:
};

class destrutivelMonstro : public Destrutivel
{
    public:
        destrutivelMonstro(Entidade *self, std::string nomeCadaver);//ctor
        void morrer();
};

class destrutivelJogador : public Destrutivel
{
    public:
        destrutivelJogador(Entidade* self, std::string nomeCadaver);//ctor
        void morrer();
};

class DestrutivelTerreno
{
public:
    Tile* self;
    int hpMax;//maximo de pontos de vida
    int hp;//pontos de vida atual
    int resistencia;

    inline bool destruido()
    {
        if (hp <= 0)
        {
            return true;
        }
        return false;
    }//Retorna verdadeiro se tiver morrido, falso se não


    DestrutivelTerreno(Tile* self,int resistencia);//ctor
    void destruir();
    int tomarDano(int dano);//subtrai o dano sofrido dos pontos de vida atuais e retorna a quantidade de dano que foi causada

};
#endif // DESTRUTIVEL_H
