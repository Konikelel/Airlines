#include "StringHandler.h"

std::string toUpper(std::string& sentence) {
    for (char& symbol : sentence)
        symbol = std::toupper(symbol);
    return sentence;
}

std::string toLower(std::string& sentence) {
    for (char& symbol : sentence)
        symbol = std::tolower(symbol);
    return sentence;
}

std::string toTitle(std::string& sentence) {
    std::string restString = "";
    if (!sentence.empty())
        sentence[0] = std::toupper(sentence[0]);
    if (sentence.size() > 1)
        restString = toLower(restString = sentence.substr(1));

    return sentence + restString;
}