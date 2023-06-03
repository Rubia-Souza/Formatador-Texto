#ifndef FORMATADOR_TEXTO_HPP
#define FORMATADOR_TEXTO_HPP

#include <string>

#include "Alinhamento.hpp"

class FormatadorTexto {
    private:
        static const char TOKEN_ESPACO = ' ';

        FormatadorTexto();

    public:
        ~FormatadorTexto();

        static std::string formatarTexto(const std::string& texto, const unsigned int maximoCaracteresPorLinha, const Alinhamento alinhamento);
    
    private:
        static std::string formatarJustificado(const std::string& texto, const unsigned int maximoCaracteresPorLinha);

        static void adicionarEspacosComBaseFormato(std::string& referencia, const unsigned int posicao, const unsigned int quantidadeEspacos, const Alinhamento alinhamento);
        static void adicionarEspacosFim(std::string& referencia, const unsigned int quantidade);
        static void adicionarEspacosPosicao(std::string& referencia, const unsigned int posicao, const unsigned int quantidadeEspacos);
};

#endif