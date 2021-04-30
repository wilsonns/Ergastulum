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
    va_list ap;//declara a lista de vari�veis vari�dicas(os "...")
    va_start(ap, texto);//define a lista de vari�veis vari�dicas(ap) e ap�s qual vari�vel se iniciam as vari�veis vari�dicas(texto)
    std::string busca = "{}";//A vari�vel que vai ser substitu�da pelo texto no loop while abaixo
    while (texto.find(busca) != std::string::npos)
    {
        std::size_t ini = texto.find(busca);
        texto.erase(ini, busca.length());
        texto.insert(ini, va_arg(ap, std::string));
    }

    va_end(ap);//encerra a lista de vari�veis vari�dicas
    debug << texto;
    debug << std::endl;
}

void LOGGER::msgLog(Mensagem mensagem)
{
    log << mensagem.texto;
    log << std::endl;
}
