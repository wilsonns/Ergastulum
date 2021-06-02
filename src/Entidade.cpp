#include "Entidade.h"

Entidade::Entidade(int x, int y, int simbolo,int tamanho ,int visao, std::string nome, const TCODColor cor)
{
    this->x = x;
    this->y = y;
    this->simbolo = simbolo;
    this->tamanho = tamanho;
    this->nome = nome;
    this->cor = cor;

    /// <summary>
    /// Decidi mais ou menos o tema: Conan/Hyperborea
    /// Esquema de atributos:
    /// Fisicos: Força = a quantidade de dano que um golpe causa
    /// -influencia 1.0x o HP do personagem
    /// Vigor = a saude do personagem para resistir à venenos e outras fontes de dano contínuo
    /// -Influencia 0.5x o HP do personagem
    /// -Aumenta em 0.5x a fadiga do personagem
    /// -Aumenta em 1x o bonus para resistencia do personagem
    /// Destreza = a capacidade do personagem de acertar outro, bem como sua capacidade de esquiva e de causar danos críticos
    /// -Influencia em 1.0x a chance de acerto do personagem
    /// -Influencia em 0.75x a defesa do personagem
    /// -Influencia em 0.25x a defesa à dano ranged
    /// -Aumenta em 0.3% a chance de dano crítico
    /// Magia = quantidade de dano que um feitiço causa
    /// - influencia 0.5x no Mana do personagem
    /// Vontade = a perseverança crua do personagem, sua capacidade de continuar mesmo sob pressão
    /// -Aumenta em 1x o bonus pra resistencia do personagem
    /// -Aumenta em 0.5x a fadiga do personagem
    /// -influencia 1.0x o Mana do personagem
    /// Astucia = a destreza magica
    /// -Aumenta em 0.5% a chance de crítico do personagem com magia
    /// -Influencia em 1.5x a chance de acerto do personagem com magia



    adcionarAtributo("Forca"); 
    adcionarAtributo("Vigor"); 
    adcionarAtributo("Destreza");
    adcionarAtributo("Magia");
    adcionarAtributo("Vontade");
    adcionarAtributo("Astucia");
    
    modificarAtributo("Forca", 5);
    modificarAtributo("Vigor", 5);
    modificarAtributo("Destreza",5);
    modificarAtributo("Magia", 5);
    modificarAtributo("Vontade", 5);
    modificarAtributo("Astucia", 5);


    /// <summary>
    /// Atributos Secundários:
    /// PV/PVMax = pontos de vida do personagem
    /// PF/PFMax = os pontos de fadiga do personagem que modificam suas ações quando está cansado
    /// Mana/ManaMax = os pontos de magia que o personagem tem; Está ligado aos pontos de fadiga
    /// Percepção = a capacidade basica do personagem de perceber coisas fora do comum como inimigos escondidos ou armadilhas
    /// e também o seu campo de visão basico
    /// Defesa = a esquiva contra ataques físicos
    /// Defesa Ranged = mesmo
    /// Largura/Altura = a quantidade de espaços horizontais/verticais que a criatura ocupa

    adcionarAtributo("PVmax");
    adcionarAtributo("PV");
    adcionarAtributo("PFmax");
    adcionarAtributo("PF");
    adcionarAtributo("Manamax");
    adcionarAtributo("Mana");
    adcionarAtributo("Percepcao");
    adcionarAtributo("Defesa");
    adcionarAtributo("Defesa a Distancia");

    modificarAtributo("PVmax", (getAtributo("Forca")+round(getAtributo("Vigor")*0.5)));
    modificarAtributo("PFmax", round(getAtributo("Vigor") * 0.5)+ round(getAtributo("Vontade") * 0.5));
    modificarAtributo("Manamax", round(getAtributo("Magia") * 0.5)+getAtributo("Vontade"));
    modificarAtributo("Percepcao", getAtributo("Astucia"));
    modificarAtributo("Defesa", round(getAtributo("Destreza") * 0.75));
    modificarAtributo("Defesa a Distancia", round(getAtributo("Destreza") * 0.25));

    adcionarAtributo("PV");
    adcionarAtributo("PF");
    adcionarAtributo("Mana");

    modificarAtributo("PV", getAtributo("PVmax"));
    modificarAtributo("PF", getAtributo("PFmax"));
    modificarAtributo("Mana", getAtributo("Manamax"));

    this->visao = getAtributo("Percepcao");

    denso = true;
    ai = NULL;
    container = NULL;
    engine.logger->debugLog("{} criado", nome);
//ctor
}

Entidade::~Entidade()
{
    if (ai) { delete ai; }
    if (container) { delete container; }
    engine.logger->debugLog("{} destruido", nome);
    //dtor
}

float Entidade::distancia(Entidade* alvo)
{
    int dx = alvo->x - x;
    int dy = alvo->y - y;
    float distancia = sqrtf(dx * dx + dy * dy);
    return distancia;
}

void Entidade::render()
{
    TCODConsole::root->setCharBackground(x,y,TCOD_black);
    TCODConsole::root->setChar(x, y, simbolo);
    TCODConsole::root->setCharForeground(x, y, cor);
}

void Entidade::atualizar()
{
     if (ai) { ai   ->atualizar(); }
}
float Entidade::maximo(float a, float b)
{
    return a > b ? a : b;
}
int Entidade::distanciaDiag(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0, dy = y1 - y0;
    return maximo(abs(dx), abs(dy));
}

float Entidade::lerp(float inicio, float fim, float t)
{
    return inicio + t * (fim - inicio);
}

void Entidade::FOV()
{
    if (!engine.debug)
    {
        for (unsigned short int i = 0; i < 360; i++)
        {
            unsigned int nx = 0;
            unsigned int ny = 0;
            float grau = i * 0.0174532f;
            nx = round(cos(grau) * visao) + x;
            ny = round(sin(grau) * visao) + y;

            int d = distanciaDiag(x, y, nx, ny);
            for (int j = 0; j < d; j++)
            {
                int tx = lerp(x, nx, j / ((float)d));
                int ty = lerp(y, ny, j / ((float)d));

                if (tx < 0 || tx > engine.mapa->largura) continue;
                if (ty < 0 || ty > engine.mapa->altura) continue;

                engine.mapa->tornarVisivel(tx, ty);
                engine.mapa->tornarExplorado(tx, ty);

                if (engine.mapa->eOpaco(tx, ty))
                {
                    break;
                }
            }
        }
    }
    else
    {
        for (int x = 0; x < engine.mapa->largura; x++)
        {
            for (int y = 0; y < engine.mapa->altura; y++)
            {
                engine.mapa->tornarVisivel(x, y);
            }
        }
    }
}

void Entidade::adcionarAtributo(std::string s_atributo, int nivel)
{
    atributos.emplace(s_atributo,nivel);
}


void Entidade::modificarAtributo(std::string s_atributo, int valor)
{
    if (atributos.find(s_atributo) != atributos.end())
    {
        atributos[s_atributo] += valor;
    }
}


void Entidade::adcionarHabilidade(std::string s_habilidade, int nivel)
{
    habilidades.emplace(s_habilidade,nivel);
}

void Entidade::modificarHabilidade(std::string s_habilidade, int valor)
{
    if (habilidades.find(s_habilidade) != habilidades.end())
    {
        habilidades[s_habilidade] += valor;
    }
}

void Entidade::uparHabilidade(std::string s_habilidade, int xp)
{/*
    if (habilidades.find(s_habilidade) != habilidades.end())
    {
        habilidades[s_habilidade]->xp += xp;
        if (habilidades[s_habilidade]->xp >= habilidades[s_habilidade]->xpProx)
        {
            habilidades[s_habilidade]->nivelBase += 1;
            habilidades[s_habilidade]->nivelAjustado += 1;
            habilidades[s_habilidade]->xp -= habilidades[s_habilidade]->xpProx;
            habilidades[s_habilidade]->xpProx = (int)pow((100 * habilidades[s_habilidade]->nivelBase),1.5);
            if (this == engine.jogador)
            {
                engine.gui->mensagem(TCOD_light_yellow, "{} de {} subiu de nivel!", s_habilidade, this->nome);
            }
        }
    }*/
}

int Entidade::getAtributo(std::string atributo)
{
    return atributos[atributo];
}


int Entidade::getHabilidade(std::string habilidade)
{
    if (habilidades.find(habilidade) != habilidades.end())
    {
        return habilidades[habilidade];
    }
    else
    {
        return NULL;
    }
}

/*    
  COMBATE  
*/


int Entidade::tomarDano(int dano)
{
    modificarAtributo("PV", dano*(-1));
    if (getAtributo("PV") <= 0)
    {
        this->morrer();
    }
    return dano;
}


int Entidade::curar(int valor)
{
    modificarAtributo("PV", valor);
    int pv = getAtributo("PV");
    int pvmax = getAtributo("PVmax");
    if (pv > pvmax)
    {
        valor = pv - pvmax;
        modificarAtributo("PV", getAtributo("PVmax"));
    }
    return valor;
}


void Entidade::morrer()
{
    simbolo = '%';
    engine.gui->mensagem(TCOD_darker_red, "{} morreu!", nome);
    nome = "Cadaver de "+nome;
    denso = false;
    ai = NULL;
    for (std::vector<Item*>::iterator it = container->inventario.begin(); it != container->inventario.end(); it++)
    {
        Item* item = *it;
        item->soltar();
    }
    engine.mapa->adcionarItem(x, y, simbolo, nome, "Cadaver", "", 0, TCOD_darker_red, 0);
    engine.entidades.erase((std::find(engine.entidades.begin(), engine.entidades.end(), this)));
}

void Entidade::atacar(Entidade* alvo)
{
    if (!alvo->morreu())
    {
        //Primeiro passo: self ataca e o alvo tenta se esquivar
        //Tipo de dano

        Item* arma = container->arma;
        std::string tipo;

        if (arma)
        {
            tipo = arma->tipo;
        }
        else
        {
            tipo = "Desarmado";
        }
        
        /*int hit = alvo->getAtributo("Defesa");
        int habilidade;

        if (getHabilidade(tipo) != NULL)
        {
            habilidade = getHabilidade(tipo);
        }
        else
        {
            habilidade = getAtributo("Destreza") - 5;
        }
        */

        int acerto = 50 + (alvo->getAtributo("Defesa") - getAtributo("Destreza"));
        
        ///ACERTO
        int to_hit = engine.random(0, 100, 0);
        if (acerto > to_hit)
        {
            
            /// DANO
            if (true)
            {/*
                std::string dano = engine.danoBal[getAtributo(ST)];
                std::size_t encontrado = dano.find("D");
                int dados;
                int bonus;

                if (encontrado != std::string::npos)
                {
                    std::string sdados = dano.substr(0, encontrado);
                    std::string sbonus = dano.substr(encontrado + 1);
                    dados = stoi(sdados);
                    bonus = stoi(sbonus);
                }
                int valordano = 0;
                for (int i = 0; i < dados; i++)
                {
                    valordano += engine.random(1, 6);
                }
                valordano += bonus;
                if (valordano <= 0)
                {
                    valordano = 1;
                }*/
                int dano;
                if (arma)
                {
                    dano = engine.random(arma->dano, getAtributo("Forca") + arma->dano);
                }
                else
                {
                    dano = engine.random(0, getAtributo("Forca"));
                }
                if(dano <= 0)
                {
                    dano = 1;
                }
                dano = alvo->tomarDano(dano);
                engine.gui->mensagem(TCOD_white, "{} ataca {} causando {} dano", nome, alvo->nome, std::to_string(dano));
                /// MENSAGEM
            }//DANO
        }//ACERTO
        
        else
        {
            engine.gui->mensagem(TCOD_white, "{} erra o golpe contra {}!", nome, alvo->nome);
        }
    }
}


void Entidade::atacarRanged(Entidade* alvo)
{
    auto arma = container->arma;
    if (alvo && !alvo->morreu() && arma && arma->eRanged)
    {
        int acerto = 50 + (alvo->getAtributo("Defesa a Distancia") - getAtributo("Destreza"));
        int to_hit = engine.random(0, 100, 0);
        if (acerto > to_hit)
        {
            int dano = dano = engine.random(arma->dano, getAtributo("Forca") + arma->dano);
            if (dano > 0)
            {
                dano = alvo->tomarDano(dano);
                engine.gui->mensagem(TCOD_white, "{} dispara contra {} e acerta, causando {} dano!", nome, alvo->nome, std::to_string(dano));
            }
        }
        else
        {

            engine.gui->mensagem(TCOD_white, "{} dispara contra {}, mas nao acerta!", nome, alvo->nome, alvo->nome);
            return;
        }
    }
    else if (arma == NULL)
    {
        engine.gui->mensagem(TCOD_white, "{} nao esta portando uma arma de disparo!", nome);
    }
    else if (!arma->eRanged)
    {
        engine.gui->mensagem(TCOD_white, "{} nao pode ser usada para atacar a distancia!", arma->nome);
    }

}


/*
Mobilia::Mobilia(int x, int y, int simbolo, int simboloAberto, std::string nome, const TCODColor cor)
{
    this->x = x;
    this->y = y; 
    this->simbolo = simbolo;
    this->nome = nome;
    this->cor = cor;
    
    this->ai = NULL;
    this->container = new Container(5);
    this->atacador = NULL;
    this->destrutivel = new Destrutivel(this, 1, 1, 0, this->nome + " quebrado");
    this->item = NULL;
}

bool Mobilia::abrir()
{

}

bool Mobilia::fechar()
{

}*/