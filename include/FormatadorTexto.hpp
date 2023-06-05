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

        /**
         * @brief Formata uma determinada string de acordo com o alinhamento informado
         * 
         * @param texto É a string que será formatada
         * @param maximoCaracteresPorLinha É a quantidade máxima de caracteres que poderá ter em uma determinada linha
         * @param alinhamento É o tipo de alinhamento que será utilizado para formatar a string
         * @return std::string É a string formatada
         */
        static std::string formatarTexto(const std::string& texto, const unsigned int maximoCaracteresPorLinha, const Alinhamento alinhamento);
    
    private:
        /**
         * @brief Adiciona espaços na string de referencia de acordo com o tipo de formatação
         * 
         * @param referencia É a string que será modificada
         * @param posicao É a posição em que os espaços podem ser inseridos
         * @param quantidadeEspacos É a quantidade de espaços que serão inseridos
         * @param alinhamento É o tipo de alinhamento que será bases para inserir os espaços
         */
        static void adicionarEspacosComBaseFormato(std::string& referencia, const unsigned int posicao, const unsigned int quantidadeEspacos, const Alinhamento alinhamento);

        /**
         * @brief Adiciona a quantidade de espaços especificada na string
         * 
         * @param referencia É a string que será modificada
         * @param quantidade É a quantidade de espaços que serão adicionados
         */
        static void adicionarEspacosFim(std::string& referencia, const unsigned int quantidade);

        /**
         * @brief Adiciona uma quantidade de espaços especificada na string
         * 
         * @param referencia É a string que será modificada
         * @param posicao É a posição que os espaços serão inseridos
         * @param quantidadeEspacos É a quantidade de espaços que serão adicionados
         */
        static void adicionarEspacosPosicao(std::string& referencia, const unsigned int posicao, const unsigned int quantidadeEspacos);

        /**
         * @brief Aplica a formatação justificada na string informada, tentando manter uma distribuição uniforme de espaços
         * 
         * @param texto É a string que será formatada
         * @param maximoCaracteresPorLinha É a quantidade máxima de caracteres que poderá ter em uma determinada linha
         * @return std::string É a string formatada
         */
        static std::string formatarJustificado(const std::string& texto, const unsigned int maximoCaracteresPorLinha);

        /**
         * @brief Ajusta linhas no texto que justificado que não são a ultima e possuem mais de uma palavra
         * 
         * @param referencia É a string de referencia que será modificada
         * @param palavras É o vetor de palavras que o texto possui
         * @param posicaoInicial É a posição da primeira palavra que será inserida na linha atual
         * @param posicaoFinal É a posição da palavra seguinte a ultima palavra incluida na linha atual
         * @param quantidadeRestanteCaracteres É a quantidade de caracteres que ainda podem ser inseridos na linha
         */
        static void justificarCentralizado(std::string& referencia, std::vector<std::string>& palavras, const unsigned int posicaoInicial, const unsigned int posicaoFinal, const unsigned int quantidadeRestanteCaracteres);

        /**
         * @brief Ajusta linhas no texto que justificado possuem apenas uma palavra ou que é a ultima do texto
         * 
         * @param referencia É a string de referencia que será modificada
         * @param palavras É o vetor de palavras que o texto possui
         * @param posicaoInicial É a posição da primeira palavra que será inserida na linha atual
         * @param posicaoFinal É a posição da palavra seguinte a ultima palavra incluida na linha atual
         * @param quantidadeRestanteCaracteres É a quantidade de caracteres que ainda podem ser inseridos na linha
         */
        static void justificarParaEsquerda(std::string& referencia, std::vector<std::string>& palavras, const unsigned int posicaoInicial, const unsigned int posicaoFinal, const unsigned int quantidadeRestanteCaracteres);
};

#endif