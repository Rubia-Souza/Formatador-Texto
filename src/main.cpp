#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "Utils.hpp"
#include "FormatadorTexto.hpp"
#include "Alinhamento.hpp"

int main() {
    std::string texto = "";

    std::cout << "Digite o texto a ser justsificado: ";
    std::getline(std::cin, texto);

    // [DEBUG] TODO: Remover
    std::vector<std::string> textoSeparado = split(texto, ' ');
    for(std::string palavra : textoSeparado) {
        std::cout << palavra << std::endl;
    }
    std::cout << std::endl;

    std::ofstream teste("teste.txt"); // [DEBUG] TODO: Remover

    std::string saida = FormatadorTexto::formatarTexto(texto, 15, Alinhamento::DIREITA);
    std::cout << saida;
    teste << saida;

    teste.close();

    return 0;
}