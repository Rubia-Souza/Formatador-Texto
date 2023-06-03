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
    std::string resultado = "";

    switch(alinhamento) {
        case(Alinhamento::ESQUERDA): {
            resultado = formatarEsquerda(texto, maximoCaracteresPorLinha);
            break;
        }
        case(Alinhamento::DIREITA): {
            resultado = formatarDireita(texto, maximoCaracteresPorLinha);
            break;
        }
        case(Alinhamento::CENTRO): {
            resultado = formatarCentro(texto, maximoCaracteresPorLinha);
            break;
        }
        case(Alinhamento::JUSTIFICADO): {
            resultado = formatarJustificado(texto, maximoCaracteresPorLinha);
            break;
        }
    }

    return resultado;
}

std::string FormatadorTexto::formatarEsquerda(const std::string& texto, const unsigned int maximoCaracteresPorLinha) {
    std::string textoFormatado = "";
    std::vector<std::string> textoSeparado = split(texto, ' ');

    std::string palavraAnterior = "";
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

            adicionarEspacosFim(textoFormatado, maximoCaracteresPorLinha - contadorTamanhoLinha);
            textoFormatado.push_back('\n');
            
            contadorTamanhoLinha = palavra.size() + 1;
            textoFormatado += palavra + ' ';
        }

        palavraAnterior = palavra;
    }

    if(palavraAnterior.size() < maximoCaracteresPorLinha) {
        textoFormatado.pop_back();
        contadorTamanhoLinha--;
    }

    return textoFormatado;
}

void FormatadorTexto::adicionarEspacosFim(std::string& referencia, const unsigned int quantidadeEspacos) {
    for(unsigned int i = 0; i < quantidadeEspacos; i++) {
        referencia.push_back(TOKEN_ESPACO);
    }

    return;
}

std::string FormatadorTexto::formatarDireita(const std::string& texto, const unsigned int maximoCaracteresPorLinha) {
    std::string textoFormatado = "";
    std::vector<std::string> textoSeparado = split(texto, ' ');

    unsigned int contadorTamanhoLinha = 0;
    unsigned int indexEspacamento = 0;
    std::string palavraAnterior = "";
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

            adicionarEspacosPosicao(textoFormatado, indexEspacamento, maximoCaracteresPorLinha - contadorTamanhoLinha);
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

    adicionarEspacosPosicao(textoFormatado, indexEspacamento, maximoCaracteresPorLinha - contadorTamanhoLinha);

    return textoFormatado;
}

void FormatadorTexto::adicionarEspacosPosicao(std::string& referencia, const unsigned int posicao, const unsigned int quantidadeEspacos) {
    for(unsigned int i = 0; i < quantidadeEspacos; i++) {
        referencia.insert(referencia.begin() + posicao, TOKEN_ESPACO);
    }

    return;
}

std::string FormatadorTexto::formatarCentro(const std::string& texto, const unsigned int maximoCaracteresPorLinha) {
    std::string textoFormatado = "";
    std::vector<std::string> textoSeparado = split(texto, ' ');

    unsigned int indexEspacamento = 0;
    unsigned int contadorTamanhoLinha = 0;
    std::string palavraAnterior = "";
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

            unsigned int quantidadeEspacosEmCadaLado = std::round((maximoCaracteresPorLinha - contadorTamanhoLinha) / 2);
            adicionarEspacosPosicao(textoFormatado, indexEspacamento, quantidadeEspacosEmCadaLado);
            adicionarEspacosFim(textoFormatado, quantidadeEspacosEmCadaLado);

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

    unsigned int quantidadeEspacosEmCadaLado = std::round((maximoCaracteresPorLinha - contadorTamanhoLinha) / 2);
    adicionarEspacosPosicao(textoFormatado, indexEspacamento, quantidadeEspacosEmCadaLado);
    adicionarEspacosFim(textoFormatado, quantidadeEspacosEmCadaLado);

    return textoFormatado;
}

std::string FormatadorTexto::formatarJustificado(const std::string& texto, const unsigned int maximoCaracteresPorLinha) {
    return "";
}