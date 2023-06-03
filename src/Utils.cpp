#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "Utils.hpp"

std::vector<std::string> split(const std::string& referencia, const char token) {
    std::vector<std::string> resultado;

    std::string palavra = "";
    std::istringstream stream(referencia);
    while(std::getline(stream, palavra, token)) {
        resultado.push_back(palavra);
    }
    
    return resultado;
}