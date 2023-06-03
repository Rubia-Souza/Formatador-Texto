#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>

#include "FormatadorTexto.hpp"
#include "Alinhamento.hpp"
#include "Utils.hpp"

#define INFINITO 0x3f3f3f3f

FormatadorTexto::FormatadorTexto() {}
FormatadorTexto::~FormatadorTexto() {}

std::string FormatadorTexto::formatarTexto(const std::string& texto, const unsigned int maximoCaracteresPorLinha, const Alinhamento alinhamento) {
    if(alinhamento == Alinhamento::JUSTIFICADO) {
        return formatarJustificado(texto, maximoCaracteresPorLinha);
    }

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
    if(alinhamento == Alinhamento::ESQUERDA) {
        adicionarEspacosFim(referencia, quantidadeEspacos);
    }
    else if(alinhamento == Alinhamento::DIREITA) {
        adicionarEspacosPosicao(referencia, posicao, quantidadeEspacos);
    }
    else if(alinhamento == Alinhamento::CENTRO) {
        unsigned int quantidadeEspacosEmCadaLado = std::round((quantidadeEspacos) / 2);
        adicionarEspacosPosicao(referencia, posicao, quantidadeEspacosEmCadaLado);
        adicionarEspacosFim(referencia, quantidadeEspacosEmCadaLado);
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
    std::vector<std::string> textoSeparado = split(texto, ' ');
    unsigned int pesos[textoSeparado.size()][textoSeparado.size()];

    for(unsigned int i = 0; i < textoSeparado.size(); i++) {
        std::string palavra1 = textoSeparado[i];

        unsigned int somaTamanhoPalavras = 0;
        for(unsigned int j = i; j < textoSeparado.size(); j++) {
            std::string palavra2 = textoSeparado[j];

            if(j > 0 && pesos[i][j-1] == INFINITO) {
                pesos[i][j] = INFINITO;
                continue;
            }

            if(i == j) {
                pesos[i][j] = pow(maximoCaracteresPorLinha - palavra1.size(), 2);
                continue;
            }

            unsigned int tamanhoTotalPalavras = palavra1.size() + palavra2.size() + 1;
            somaTamanhoPalavras += tamanhoTotalPalavras;
            if(somaTamanhoPalavras > maximoCaracteresPorLinha) {
                pesos[i][j] = INFINITO;
                continue;
            }

            pesos[i][j] = pow(maximoCaracteresPorLinha - somaTamanhoPalavras, 2);
        }
    }

    for(unsigned int i = 0; i < textoSeparado.size(); i++) {
        for(unsigned int j = 0; j < textoSeparado.size(); j++) {
            if(j == textoSeparado.size() - 1) {
                std::cout << pesos[i][j] << "\n";
            }
            else {
                std::cout << pesos[i][j] << "\t";
            }
        }
    }

    return "";
}