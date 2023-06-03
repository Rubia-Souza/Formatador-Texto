#include <string>
#include <vector>
#include <fstream>
#include <cmath>

#include "FormatadorTexto.hpp"
#include "Alinhamento.hpp"
#include "Utils.hpp"

FormatadorTexto::FormatadorTexto() {}
FormatadorTexto::~FormatadorTexto() {}

std::string FormatadorTexto::formatarTexto(const std::string& texto, const unsigned int maximoCaracteresPorLinha, const Alinhamento alinhamento) {
    std::string textoFormatado = "";
    std::vector<std::string> textoSeparado = split(texto, ' ');

    std::string palavraAnterior = "";
    unsigned int indexEspacamento = 0;
    unsigned int contadorTamanhoLinha = 0;
    for(std::string palavra : textoSeparado) {
        if(contadorTamanhoLinha + palavra.size() < maximoCaracteresPorLinha) {
            contadorTamanhoLinha += palavra.size() + 1;
            textoFormatado += palavra + ' ';
        }
        else {
            if(palavraAnterior.size() < maximoCaracteresPorLinha) {
                textoFormatado.pop_back();
                contadorTamanhoLinha--;
            }

            adicionarEspacosComBaseFormato(textoFormatado, indexEspacamento, maximoCaracteresPorLinha - contadorTamanhoLinha, alinhamento);
            textoFormatado.push_back('\n');
            indexEspacamento = textoFormatado.size();
            
            contadorTamanhoLinha = palavra.size() + 1;
            textoFormatado += palavra + ' ';
        }

        palavraAnterior = palavra;
    }

    if(palavraAnterior.size() < maximoCaracteresPorLinha) {
        textoFormatado.pop_back();
        contadorTamanhoLinha--;
    }

    if(alinhamento == Alinhamento::DIREITA) {
        adicionarEspacosPosicao(textoFormatado, indexEspacamento, maximoCaracteresPorLinha - contadorTamanhoLinha);
    }
    else if(alinhamento == Alinhamento::CENTRO) {
        unsigned int quantidadeEspacosEmCadaLado = std::round((maximoCaracteresPorLinha - contadorTamanhoLinha) / 2);
        adicionarEspacosPosicao(textoFormatado, indexEspacamento, quantidadeEspacosEmCadaLado);
        adicionarEspacosFim(textoFormatado, quantidadeEspacosEmCadaLado);
    }

    return textoFormatado;
}

void FormatadorTexto::adicionarEspacosComBaseFormato(std::string& referencia, const unsigned int posicao, const unsigned int quantidadeEspacos, const Alinhamento alinhamento) {
    switch(alinhamento) {
        case(Alinhamento::ESQUERDA): {
            adicionarEspacosFim(referencia, quantidadeEspacos);

            break;
        }
        case(Alinhamento::DIREITA): {
            adicionarEspacosPosicao(referencia, posicao, quantidadeEspacos);

            break;
        }
        case(Alinhamento::CENTRO): {
            unsigned int quantidadeEspacosEmCadaLado = std::round((quantidadeEspacos) / 2);
            adicionarEspacosPosicao(referencia, posicao, quantidadeEspacosEmCadaLado);
            adicionarEspacosFim(referencia, quantidadeEspacosEmCadaLado);

            break;
        }
    }

    return;
}

void FormatadorTexto::adicionarEspacosFim(std::string& referencia, const unsigned int quantidadeEspacos) {
    for(unsigned int i = 0; i < quantidadeEspacos; i++) {
        referencia.push_back(TOKEN_ESPACO);
    }

    return;
}

void FormatadorTexto::adicionarEspacosPosicao(std::string& referencia, const unsigned int posicao, const unsigned int quantidadeEspacos) {
    for(unsigned int i = 0; i < quantidadeEspacos; i++) {
        referencia.insert(referencia.begin() + posicao, TOKEN_ESPACO);
    }

    return;
}

std::string FormatadorTexto::formatarJustificado(const std::string& texto, const unsigned int maximoCaracteresPorLinha) {
    return "";
}