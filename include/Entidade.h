#ifndef ENTIDADE_H
#define ENTIDADE_H
#include <main.h>

struct Nodo; //FORWARD DO NODO DECLARADO EM PATHFINDING.H

class Entidade
{
    public:
        //POSI��O
        int x, y;//posi��o x e y da entdidade
        int simbolo; //simnbolo desenhado
        int visao; //raio da vis�o da entidade
        int tamanho; //uma abstra��o do tamanho de uma entidade; 1 - rato, 5- humano, 10 - carro, assim por diante
        
        TCODColor cor;

        std::string nome; //Nome da entidade
        bool denso;//pode-se passar por essa entidade?

        Atacador *atacador; //� uma entidade capaz de atacar?
        Destrutivel *destrutivel; //� uma entidade mortal/destrutivel?
        AI *ai;//� uma entidade que se auto-atualiza?
        Item* item;//� uma entidade que pode ser pega e guardada em um contaienr?
        Container* container;//� uma entidade que pode guardar outras entidades?

        //Atributos e Habilidades
        std::unordered_map<std::string, Habilidade*> habilidades;
        std::unordered_map<std::string, Stats*> atributos;

        //Fun��es para Habilidades e Atributos
        void adcionarAtributo(std::string s_atributo);
        void modificarAtributo(std::string s_atributo, int valor);//preciso verificar se preciso deletar individualmente cada habilidade/atributo

        void adcionarHabilidade(std::string s_habilidade);
        void modificarHabilidade(std::string s_habilidade, int valor);
        void uparHabilidade(std::string s_habilidade, int xp);

        int getAtributo(std::string atributo);
        int getHabilidade(std::string habilidade);

        std::vector<Nodo*> caminho;//O caminho retornado pelas fun��es de pathfinding

        Entidade(int x, int y,int simbolo, int tamanho, int visao,  std::string nome, const TCODColor cor);//CTOR
        virtual ~Entidade(); //DTOR

        float distancia(Entidade* alvo);

        /// FOV
        float maximo(float a, float b);//retorna o valor maior
        int distanciaDiag(int x0, int y0, int x1, int y1);//retorna a distancia  entre os pontos
        float lerp(float inicio, float fim, float t);//retorna a interpola��o linear

        void FOV();//realiza todos os calculos de FOV()

        void render(); //Desenha a entidade na tela
        void atualizar();//chama a atualiza��o da IA da entidade

        //////FLAGS

};
/*

class Mobilia : public Entidade//////UM TIPO DE ENTIDADE QUE REPRESENTA PORTAS, BA�S, E TODOS OS OUTROS TIPOS DE OBJETOS DO MAPA
{
public:
    Mobilia(int x, int y, int simbolo, int simboloAberto, std::string nome, const TCODColor cor);

    int simboloAberto;
    bool trancado;

    bool abrir();
    bool fechar();
};
*/
#endif // ENTIDADE_H
