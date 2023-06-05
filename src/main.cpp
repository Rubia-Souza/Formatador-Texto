#include <iostream>
#include <string>
#include <fstream>

#include "FormatadorTexto.hpp"
#include "Alinhamento.hpp"

/**
 * @brief Ajusta o texto informado de todas as formas possíveis (Esquerda, Direita, Centro e Justificado)
 * 
 * @param texto É o texto que será ajustado
 * @param maximoCaracteresPorLinha É o máximo de caracteres que podem ter em uma linha do texto formatado
 */
void ExecutarCasoTeste(std::string& texto, const unsigned int maximoCaracteresPorLinha);

int main() {
    int opcao = 0;

    std::cout << "Escolha uma opcao abaixo:\n";
    do {
        std::cout << "\n[1] Executar caso teste personalizado"
                  << "\n[2] Executar caso teste padrao";

        std::cout << "\nOpcao: ";
        std::cin >> opcao;
    } while(opcao < 1 || opcao > 2);

    std::string texto = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Quisque in nisi blandit, cursus orci ut, mattis lacus. Quisque viverra eget augue quis eleifend. Vivamus ultrices tellus mauris, sit amet euismod nisi condimentum vitae. Duis sed ipsum orci. Sed elit magna, laoreet rutrum diam vel, convallis porta massa. Curabitur accumsan massa vitae blandit ornare. Maecenas nec suscipit nisi. Cras vestibulum orci enim, in fermentum turpis bibendum eget. Aenean convallis dui ac sapien fringilla, at congue ligula imperdiet. Morbi posuere risus sit amet metus bibendum dignissim. Morbi in nunc ut ante auctor consectetur. Nunc ac tristique felis, id ullamcorper justo. Pellentesque accumsan nulla dictum placerat tempus. Etiam nec sollicitudin dui. Nam scelerisque, est vitae interdum vulputate, nisi metus condimentum ex, ut faucibus lacus nisi id augue. Praesent pellentesque, nulla eu cursus fermentum, lectus augue cursus turpis, in auctor magna urna sit amet ex. Duis malesuada metus eleifend magna viverra ultrices. Quisque dapibus ligula id ipsum pharetra, eget dictum nisi suscipit. Nam eget neque sed erat gravida hendrerit sit amet non nunc. Quisque sapien velit, volutpat nec ante sed, semper pharetra lorem. Proin pellentesque libero lacinia, congue metus vitae, viverra libero. Fusce auctor nisl quam, a maximus elit dapibus non. Etiam quis molestie erat. Nam consequat ipsum magna, sed egestas sapien cursus vitae. Aliquam erat volutpat. Vivamus sed gravida augue. Donec congue metus non nulla fringilla, ac hendrerit velit maximus. Sed sit amet laoreet enim. Morbi vel sagittis sapien. Aliquam non venenatis enim. Donec dignissim tempus venenatis. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Duis purus lacus, sagittis placerat ipsum a, posuere tincidunt dolor. Mauris facilisis pretium magna vel tincidunt. Curabitur hendrerit, lectus et venenatis elementum, sapien felis molestie elit, in tincidunt ex lacus condimentum quam.";
    unsigned int maximoCaracteresPorLinha = 100;

    if(opcao == 1) {
        std::cout << "\nDigite, em uma unica linha, o texto que sera alinhado:\n";
        std::cin.ignore();
        std::getline(std::cin, texto);

        std::cout << "\nOBSERVACAO: A quantidade maxima deve ser maior ou igual a menor palavra contida no texto.\n";
        std::cout << "\nDigite a quantidade maxima de caracteres que podem haver em cada linha: ";
        std::cin >> maximoCaracteresPorLinha;
    }

    ExecutarCasoTeste(texto, maximoCaracteresPorLinha);
    return 0;
}

void ExecutarCasoTeste(std::string& texto, const unsigned int maximoCaracteresPorLinha) {
    std::ofstream teste("saida.txt");

    std::cout << "\n==== Alinhamento na Esquerda\n\n";
    teste << "==== Alinhamento na Esquerda\n\n";

    std::string saida = FormatadorTexto::formatarTexto(texto, maximoCaracteresPorLinha, Alinhamento::ESQUERDA);

    std::cout << saida;
    teste << saida;

    std::cout << "\n\n==== Alinhamento na Direita\n\n";
    teste << "\n\n==== Alinhamento na Direita\n\n";

    saida = FormatadorTexto::formatarTexto(texto, maximoCaracteresPorLinha, Alinhamento::DIREITA);

    std::cout << saida;
    teste << saida;

    std::cout << "\n\n==== Alinhamento no Centro\n\n";
    teste << "\n\n==== Alinhamento na Centro\n\n";

    saida = FormatadorTexto::formatarTexto(texto, maximoCaracteresPorLinha, Alinhamento::CENTRO);

    std::cout << saida;
    teste << saida;

    std::cout << "\n\n==== Justificado\n\n";
    teste << "\n\n==== Justificado\n\n";

    saida = FormatadorTexto::formatarTexto(texto, maximoCaracteresPorLinha, Alinhamento::JUSTIFICADO);

    std::cout << saida;
    teste << saida;

    teste.close();
    return;
}