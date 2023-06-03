#ifndef FORMATADOR_TEXTO_HPP
#define FORMATADOR_TEXTO_HPP

#include <string>

#include "Alinhamento.hpp"

class FormatadorTexto {
    private:
        FormatadorTexto();

    public:
        ~FormatadorTexto();

        static std::string formatarTexto(const std::string& texto, const unsigned int maximoCaracteresPorLinha, const Alinhamento alinhamento);
    
    private:
        static std::string formatarEsquerda(const std::string& texto, const unsigned int maximoCaracteresPorLinha);
        static std::string formatarDireita(const std::string& texto, const unsigned int maximoCaracteresPorLinha);
        static std::string formatarCentro(const std::string& texto, const unsigned int maximoCaracteresPorLinha);
        static std::string formatarJustificado(const std::string& texto, const unsigned int maximoCaracteresPorLinha);
};

#endif