#include "LOGGER.h"
#include <main.h>

LOGGER::LOGGER()
{
    debug.open("log/debug.txt");
    log.open("log/log.txt");

    //ctor
}

LOGGER::~LOGGER()
{
    debug.close();
    log.close();
    //dtor
}

void LOGGER::debugLog(std::string texto, ...)
{
    va_list ap;//declara a lista de variáveis variádicas(os "...")
    va_start(ap, texto);//define a lista de variáveis variádicas(ap) e após qual variável se iniciam as variáveis variádicas(texto)
    std::string busca = "{}";//A variável que vai ser substituída pelo texto no loop while abaixo
    while (texto.find(busca) != std::string::npos)
    {
        std::size_t ini = texto.find(busca);
        texto.erase(ini, busca.length());
        texto.insert(ini, va_arg(ap, std::string));
    }

    va_end(ap);//encerra a lista de variáveis variádicas
    debug << texto;
    debug << std::endl;
}

void LOGGER::msgLog(Mensagem mensagem)
{
    log << mensagem.texto;
    log << std::endl;
}
