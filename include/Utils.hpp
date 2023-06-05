#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>

/**
 * @brief Divide uma string em várias outras com base no token informado
 * 
 * @param referencia É a string que será dividida
 * @param token É o token que indica o ponto que ocorrerá a divisão
 * @return std::vector<std::string> É o vetor com as partes separadas da string
 */
std::vector<std::string> split(const std::string& referencia, const char token);

#endif