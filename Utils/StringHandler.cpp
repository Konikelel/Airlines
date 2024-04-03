#include "StringHandler.h"

std::string toUpper(const std::string& sentence) {
    std::string newSentence = sentence;

    for (char& symbol : newSentence)
        symbol = std::toupper(symbol);
    return sentence;
}

std::string toLower(const std::string& sentence) {
    std::string newSentence = sentence;

    for (char& symbol : newSentence)
        symbol = std::tolower(symbol);
    return sentence;
}

std::string toTitle(const std::string& sentence) {
    std::string newSentence = "";

    if (!sentence.empty())
        newSentence = std::toupper(sentence[0]);
    if (sentence.size() > 1)
        newSentence += toLower(sentence.substr(1));

    return newSentence;
}