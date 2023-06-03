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

    unsigned int contadorTamanhoLinha = 0;
    for(unsigned int i = 0; i < textoSeparado.size(); i++) {
        if(contadorTamanhoLinha + textoSeparado[i].size() < maximoCaracteresPorLinha) {
            contadorTamanhoLinha += textoSeparado[i].size() + 1;
            textoFormatado += textoSeparado[i] + ' ';
        }
        else {
            for(unsigned int j = contadorTamanhoLinha; j < maximoCaracteresPorLinha; j++) {
                textoFormatado.push_back(' ');
            }
            textoFormatado.push_back('\n');
            
            contadorTamanhoLinha = textoSeparado[i].size() + 1;
            textoFormatado += textoSeparado[i] + ' ';
        }
    }

    return textoFormatado;
}

std::string FormatadorTexto::formatarDireita(const std::string& texto, const unsigned int maximoCaracteresPorLinha) {
    std::string textoFormatado = "";
    std::vector<std::string> textoSeparado = split(texto, ' ');

    unsigned int contadorTamanhoLinha = 0;
    unsigned int indexEspacamento = 0;
    for(unsigned int i = 0; i < textoSeparado.size(); i++) {
        if(contadorTamanhoLinha + textoSeparado[i].size() < maximoCaracteresPorLinha) {
            contadorTamanhoLinha += textoSeparado[i].size() + 1;
            textoFormatado += textoSeparado[i] + ' ';
        }
        else {
            for(unsigned int j = contadorTamanhoLinha; j < maximoCaracteresPorLinha; j++) {
                textoFormatado.insert(textoFormatado.begin() + indexEspacamento, ' ');
            }
            textoFormatado.push_back('\n');
            indexEspacamento = textoFormatado.size();
            
            contadorTamanhoLinha = textoSeparado[i].size() + 1;
            textoFormatado += textoSeparado[i] + ' ';
        }
    }

    for(unsigned int j = contadorTamanhoLinha; j < maximoCaracteresPorLinha; j++) {
        textoFormatado.insert(textoFormatado.begin() + indexEspacamento, ' ');
    }    

    return textoFormatado;
}

std::string FormatadorTexto::formatarCentro(const std::string& texto, const unsigned int maximoCaracteresPorLinha) {
    std::string textoFormatado = "";
    std::vector<std::string> textoSeparado = split(texto, ' ');

    unsigned int indexEspacamento = 0;
    unsigned int contadorTamanhoLinha = 0;
    for(unsigned int i = 0; i < textoSeparado.size(); i++) {
        if(contadorTamanhoLinha + textoSeparado[i].size() < maximoCaracteresPorLinha) {
            contadorTamanhoLinha += textoSeparado[i].size() + 1;
            textoFormatado += textoSeparado[i] + ' ';
        }
        else {
            unsigned int quantidadeEspacos = maximoCaracteresPorLinha - contadorTamanhoLinha;
            unsigned int quantidadeEspacosParte = std::round(quantidadeEspacos / 2);

            for(unsigned int j = 0; j < quantidadeEspacosParte; j++) {
                textoFormatado.insert(textoFormatado.begin() + indexEspacamento, ' ');
            }

            for(unsigned int j = 0; j < quantidadeEspacosParte; j++) {
                textoFormatado.push_back(' ');
            }

            textoFormatado.push_back('\n');
            indexEspacamento = textoFormatado.size();
            
            contadorTamanhoLinha = textoSeparado[i].size() + 1;
            textoFormatado += textoSeparado[i] + ' ';
        }
    }

    unsigned int quantidadeEspacos = maximoCaracteresPorLinha - contadorTamanhoLinha;
    unsigned int quantidadeEspacosParte = std::round(quantidadeEspacos / 2);
    
    for(unsigned int j = 0; j < quantidadeEspacosParte; j++) {
        textoFormatado.insert(textoFormatado.begin() + indexEspacamento, ' ');
    }

    for(unsigned int j = 0; j < quantidadeEspacosParte; j++) {
        textoFormatado.push_back(' ');
    }

    return textoFormatado;
}

std::string FormatadorTexto::formatarJustificado(const std::string& texto, const unsigned int maximoCaracteresPorLinha) {
    return "";
}