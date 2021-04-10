#ifndef ATACADOR_H
#define ATACADOR_H
#include<main.h>

class Atacador
{
    
    public:        
        //Atributos
        std::unordered_map<std::string, float> atributos;        
        void adcionarAtributo(std::string atributo, float valorInicial);
        void modificarAtributo(std::string atributo, float valor);

        //Habilidades

        std::unordered_map<std::string, float> habilidades;
        void adcionarHabilidade(std::string habilidade, float valorInicial);
        void modificarHabilidade(std::string habilidade, float valor);

        Atacador(float forca = 1, float destreza = 1, float ataque = 0);//ctor
        virtual ~Atacador();//dtor

        

        void atacar(Entidade *self, Entidade *alvo);//self ataca o alvo destrutivel e causa dano

    protected:

    private:
};

#endif // ATACADOR_H
