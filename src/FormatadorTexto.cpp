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
    std::string textoFormatado = "";
    std::vector<std::string> textoSeparado = split(texto, ' ');

    unsigned int j = 0;
    for(unsigned int i = 0; i < textoSeparado.size(); i = j) {
        j = i + 1;
        unsigned int contadorTamanhoLinha = textoSeparado[i].size();

        while(j < textoSeparado.size() && (contadorTamanhoLinha + textoSeparado[j].size() + (j - i - 1)) < maximoCaracteresPorLinha){
            contadorTamanhoLinha += textoSeparado[j].size();
            j++;
        }
        
        unsigned int quantidadeRestantesCaracters = maximoCaracteresPorLinha - contadorTamanhoLinha;
        unsigned int quantidadePalavras = j - i;

        if(quantidadePalavras == 1 || j >= textoSeparado.size()) {
            std::string linhaAtual = "";
            justificarParaEsquerda(linhaAtual, textoSeparado, i, j, quantidadeRestantesCaracters);

            textoFormatado += linhaAtual;
        }
        else {
            std::string linhaAtual = "";
            justificarCentralizado(linhaAtual, textoSeparado, i, j, quantidadeRestantesCaracters);

            textoFormatado += linhaAtual;
        }

        i = j;
    }
    
    return textoFormatado;
}

void FormatadorTexto::justificarCentralizado(std::string& referencia, std::vector<std::string>& palavras, const unsigned int posicaoInicial, const unsigned int posicaoFinal, const unsigned int quantidadeRestanteCaracteres) {
    unsigned int quantidadeMinimaEspacos = (posicaoFinal - posicaoInicial - 1);
    unsigned int quantidadeMinimaEspacosPorIntervalo = std::round(quantidadeRestanteCaracteres / quantidadeMinimaEspacos);
    int quantidadeExtrasEspacos = quantidadeRestanteCaracteres % quantidadeMinimaEspacos;

    referencia = palavras[posicaoInicial];
    for(unsigned int i = posicaoInicial + 1; i < posicaoFinal; i++) {
        unsigned int quantidadeEspacosAplicados = quantidadeMinimaEspacosPorIntervalo;
        quantidadeExtrasEspacos--;
        if(quantidadeExtrasEspacos > 0) {
            quantidadeEspacosAplicados++;
        }

        for(unsigned int j = 0; j < quantidadeEspacosAplicados; j++) {
            referencia.push_back(' ');
        }

        referencia += palavras[i];
    }

    referencia.push_back('\n');
    return;
}

void FormatadorTexto::justificarParaEsquerda(std::string& referencia, std::vector<std::string>& palavras, const unsigned int posicaoInicial, const unsigned int posicaoFinal, const unsigned int quantidadeRestanteCaracteres) {
    unsigned int quantidadeEspacosDireita = quantidadeRestanteCaracteres - (posicaoFinal - posicaoInicial - 1);

    referencia = palavras[posicaoInicial];
    for(unsigned int i = posicaoInicial + 1; i < posicaoFinal; i++) {
        referencia += ' ' + palavras[i];
    }

    for(unsigned int i = 0; i < quantidadeEspacosDireita; i++) {
        referencia.push_back(' ');
    }

    referencia.push_back('\n');
    return;
}