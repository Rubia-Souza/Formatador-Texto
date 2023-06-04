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
    std::string linhaAtual = "";
    std::string textoFormatado = "";
    std::vector<std::string> textoSeparado = split(texto, ' ');
    
    unsigned int j = 0;
    unsigned int contadorTamanhoLinha = 0;
    for(unsigned int i = 0; i < textoSeparado.size(); i = j) {
        std::string palavraInicial = textoSeparado[i];
        contadorTamanhoLinha += palavraInicial.size();

        j = i + 1;
        unsigned int quantidadeMinimaEspacos = j - i - 1; // quantidadeIntervalosEntrePalavras
        unsigned int tamanhoLinhaComProximaPalavra = contadorTamanhoLinha + textoSeparado[j].size() + quantidadeMinimaEspacos;

        while(j < textoSeparado.size() && tamanhoLinhaComProximaPalavra < maximoCaracteresPorLinha) {
            contadorTamanhoLinha += textoSeparado[j].size();            
            
            j++;
            quantidadeMinimaEspacos = j - i - 1;
            tamanhoLinhaComProximaPalavra = contadorTamanhoLinha + textoSeparado[j].size();
        }

        unsigned int quantidadeRestanteCaracters = maximoCaracteresPorLinha - contadorTamanhoLinha;
        unsigned int quantidadePalavras = j - i;

        if(quantidadePalavras == 1 || j >= textoSeparado.size()) {
            for(unsigned int k = i; k < j; k++) {
                linhaAtual += ' ' + textoSeparado[k];
            }

            unsigned int quantidadeEspacosDireita = quantidadeRestanteCaracters - quantidadeMinimaEspacos;
            for(unsigned int k = 0; k < quantidadeEspacosDireita; k++) {
                linhaAtual.push_back(' ');
            }

            linhaAtual.push_back('\n');
            textoFormatado += linhaAtual;
        }
        else {
            unsigned int quantidadeEspacos = std::round(quantidadeRestanteCaracters / quantidadeMinimaEspacos);
            int quantidadeExtraEspacos = quantidadeRestanteCaracters % quantidadeMinimaEspacos;

            for(unsigned int k = i; k < j; k++) {
                unsigned int quantidadeEspacosAdicionada = quantidadeEspacos;
                quantidadeExtraEspacos--;
                if(quantidadeExtraEspacos > 0) {
                    quantidadeEspacosAdicionada++;
                }

                for(unsigned int l = 0; l < quantidadeEspacosAdicionada; l++) {
                    linhaAtual.push_back(' ');
                }

                linhaAtual += textoSeparado[k];
            }

            linhaAtual.push_back('\n');
            textoFormatado += linhaAtual;
        }

        linhaAtual = "";
        contadorTamanhoLinha = 0;
    }

    return textoFormatado;
}

void FormatadorTexto::adicionarEspacosIgualmente(std::string& referencia, const unsigned int quantidade) {

}