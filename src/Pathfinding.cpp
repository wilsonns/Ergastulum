#include "Pathfinding.h"
#include "main.h"



Pathfinding::Pathfinding()
{
    nodos = new Nodo[engine.mapa->largura * engine.mapa->altura];//inicializa nodos como uma array de Nodo com tamanho de largura*altura do mapa
    for (int x = 0; x < engine.mapa->largura; x++)
    {
        for (int y = 0; y < engine.mapa->altura; y++)
        {
            nodos[x + y * engine.mapa->largura].x = x;
            nodos[x + y * engine.mapa->largura].y = y;
            nodos[x + y * engine.mapa->largura].pai = nullptr;
        }
    }//inicializa todos os nodos individuais
    for (int x = 0; x < engine.mapa->largura; x++)
    {
        for (int y = 0; y < engine.mapa->altura;y++)
        {
            if (y > 0)
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x + 0) + (y - 1) * engine.mapa->largura]);
            }
            if (y < engine.mapa->altura - 1)
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x + 0) + (y + 1) * engine.mapa->largura]);
            }
            if (x > 0)
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x - 1) + (y + 0) * engine.mapa->largura]);
            }

            if (y < engine.mapa->largura - 1)
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x + 1) + (y + 0) * engine.mapa->largura]);
            }
            if (y > 0 && x > 0)
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x - 1) + (y - 1) * engine.mapa->largura]);
            }
            if (y < engine.mapa->altura - 1 && x > 0)
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x - 1) + (y + 1) * engine.mapa->largura]);
            }
            if (y > 0 && x < engine.mapa->largura - 1)
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x + 1) + (y - 1) * engine.mapa->largura]);
            }

            if (y < engine.mapa->altura - 1 && x < engine.mapa->largura - 1)
            {
                nodos[x + y * engine.mapa->largura].vizinhos.push_back(&nodos[(x + 1) + (y + 1) * engine.mapa->largura]);
            }
        }
    }//incializa os 8 vizinhos de cada nodo
    //CTOR
}

Pathfinding::~Pathfinding()
{
    delete[] nodos;
    //DTOR
}

std::vector<Nodo*> Pathfinding::acharCaminho(Entidade* self, Entidade* alvo)
{
    if (alvo == NULL)
    {
        std::vector<Nodo*>caminho;
        return caminho;
    }
    /// Loop do Pathfinding:
    /// 1. reseta todos os nodos, limpa as listas aberta e fechada
    /// 2. insere o nodo inicial na lista aberta e define ele como atual
    /// 3. Inicia o loop:processa o nodo atual , tirando-o da lista aberta e colocando na lista fechada. Todos os vizinhos do nodo inicial são inseridos na lista aberta
    /// 4.  Reorganize a lista aberta de forma crescente baseado na variavel F; O nodo com o menor F agora é o atual;
    /// 5. Repita o passo 3 até que a lista aberta fique vazia(significa que o caminho não foi encontrado) OU até que o nodo atual seja == ao nodo objetivo
    /// 6. Se o objetivo for encontrado, trace o caminho de volta através do nodo pai do objetivo, repetindo isso até formar o caminho do inicio ao objetivo
    /// 7. Retorne um vetor revertido com os nodos que compoem o caminho
    aberta.clear();//limpa a lista aberta
    fechada.clear();//limpa a lista fechada
    for (int x = 0; x < engine.mapa->largura; x++)
    {
        for (int y = 0; y < engine.mapa->altura; y++)
        {
            nodos[x + y * engine.mapa->largura].f = 0;
            nodos[x + y * engine.mapa->largura].g = 0;
            nodos[x + y * engine.mapa->largura].h = 0;
            nodos[x + y * engine.mapa->largura].pai = nullptr;
        }
    }//reseta todos os nodos do mapa

    Nodo* inicio = &nodos[self->x + self->y * engine.mapa->largura];//setta o Nodo incial baseado na posição do self que chamou a função
    Nodo* objetivo = &nodos[alvo->x + alvo->y * engine.mapa->largura];//setta o Nodo objetivo baseado no alvo
    Nodo* atual = nullptr;//declara nodo atual
    inicio->f = 0;
    inicio->g = 0;
    inicio->h = calcularH(inicio,objetivo);

    atual = inicio;
    aberta.push_back(atual);//insere o nodo atual na lista aberta

    while (!aberta.empty())
    {
        aberta.sort([](const Nodo* lhs, const Nodo* rhs) {return lhs->f < rhs->f; });
        //aberta = organizarPorF(aberta);
        atual = aberta.front();
        aberta.pop_front();
        fechada.push_back(atual);
        for (int i = 0; i < atual->vizinhos.size(); i++)
        {
            if (!engine.mapa->eParede(atual->vizinhos[i]->x, atual->vizinhos[i]->y)
                && !estaNaLista(aberta, atual->vizinhos[i]) && !estaNaLista(fechada, atual->vizinhos[i]))
            {
                atual->vizinhos[i]->pai = atual;
                atual->vizinhos[i]->g = calcularG(atual->vizinhos[i], inicio);
                atual->vizinhos[i]->h = calcularH(atual->vizinhos[i], objetivo);
                atual->vizinhos[i]->f = calcularF(atual->vizinhos[i]);
                aberta.push_back(atual->vizinhos[i]);
            }//Se o vizinho em questão não for uma parede, não estiver na lista aberta nem na fechada, sete o nodo atual como o pai dele,
                //defina as suas variaveis e o insira na lista aberta
            else if (!engine.mapa->eParede(atual->vizinhos[i]->x, atual->vizinhos[i]->y)
                && estaNaLista(aberta, atual->vizinhos[i]) && !estaNaLista(fechada, atual->vizinhos[i]))
            {
                if (atual->vizinhos[i]->pai->g > calcularG(atual, inicio))
                {
                    atual->vizinhos[i]->g = calcularG(atual->vizinhos[i], inicio);
                    atual->vizinhos[i]->f = calcularF(atual->vizinhos[i]);
                    atual->vizinhos[i]->pai = atual;
                }
            }//Se então o nodo não for uma parede, mas já estiver na lista aberta, recalcule o valor G e se esse for menor, sette o nodo atual como o pai dele
        }
        if(aberta.empty())
        {
            break;
        }
        if (engine.debug)
        {
            if (fechada.size() != 0)
            {
                for (auto& it: fechada)
                {

                    TCODConsole::root->setChar(it->x, it->y, 'x');
                    TCODConsole::root->setCharForeground(it->x, it->y,TCOD_light_red);
                    
                }
                
            }
            if (aberta.size() != 0)
            {
                for (auto& it : aberta)
                {
                    TCODConsole::root->setChar(it->x, it->y, 'o');
                    TCODConsole::root->setCharForeground(it->x, it->y,TCOD_light_green);
                    
                }
                
                
            }

            TCODConsole::root->flush();
        }
            if(atual == objetivo)
        {
            break;
        }


    }

    if(atual == objetivo)
    {
        std::vector<Nodo*> caminho;
        for (int i = 0; atual != inicio; i++)
        {
            caminho.push_back(atual);
            atual = atual->pai;
            if (engine.debug == true)
            {/*
                attron(COLOR_PAIR(3));
                mvprintw(caminho[i]->y, caminho[i]->x, "x");
                attroff(COLOR_PAIR(3));
                refresh();*/
            }
        }
        std::reverse(caminho.begin(), caminho.end());
        return caminho;
    }
    else
    {
        std::vector<Nodo*> caminho;
        return caminho;
    }
}

bool Pathfinding::estaNaLista(std::list<Nodo*>& lista, Nodo* nodo)
{
    bool encontrado = (std::find(lista.begin(), lista.end(), nodo) != lista.end());
    
    if (encontrado)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Pathfinding::compararF(Nodo l, Nodo r)
{
    if (l.f < r.f)
    {
        return true;
    }
    
    if (l.f > r.f)
    {
        return false;
    }
    return true;
}
/*
std::list<Nodo*> Pathfinding::organizarPorF(std::list<Nodo*> lista)
{
    std::list<Nodo*> copialista;
    unsigned int tam = lista.size();
    while (copialista.size() != tam)
    {
        int menorF = 999;
        Nodo* nodoMenorF;
        Nodo nodor;
        nodor.f = 999;
        nodoMenorF = &nodor;
        for (auto const& it : lista)
        {
            if (menorF > 1)
            {
                if (menorF > it->f)
                {
                    menorF = 0;
                    nodoMenorF = it;
                }
            }
            if (it->f < nodoMenorF->f)
            {
                nodoMenorF = it;
            }
            else if (it->f == nodoMenorF->f)
            {
                if (it->h < nodoMenorF->h)
                {
                    nodoMenorF = it;
                }
            }//Acha o nodo com meno0r valor F na lista. Se encontrar nodos com valor F igual, prioriza o com menor valor H
        }
        std::list<Nodo*>::iterator it1 = lista.begin();
        int index = 0;
        for (auto const &it : lista)
        {
            if (lista.size() != 0)
            {
                if (it->f == nodoMenorF->f && it->h == nodoMenorF->h)
                {

                   copialista.push_back(it);
                   lista.erase(it1);
                   break;
                }
            }
            else if (lista.size() == 0)
            {
                break;
            }
            if (lista.size() != 0)
            {
                std::advance(it1, 1);
            }
            else
            {
                break;
            }
            
        }
    
    }
    return copialista;
}*/