#ifndef FORMATADOR_TEXTO_HPP
#define FORMATADOR_TEXTO_HPP

#include <string>
#include <vector>

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

        static void justificarCentralizado(std::string& referencia, std::vector<std::string>& palavras, const unsigned int posicaoInicial, const unsigned int posicaoFinal, const unsigned int quantidadeRestanteCaracteres);
        static void justificarParaEsquerda(std::string& referencia, std::vector<std::string>& palavras, const unsigned int posicaoInicial, const unsigned int posicaoFinal, const unsigned int quantidadeRestanteCaracteres);
};

#endif