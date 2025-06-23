#ifndef POLIBIUS_H
#define POLIBIUS_H

#include "../general/general.h"

enum { LOWER_EN, UPPER_EN, LOWER_RU, UPPER_RU, UNKNOWN };

extern "C" {
    wchar_t polibiusCharacter(int position);
    tuple<int, int, int> polibiusCode(wchar_t wc);
    void polibiusEncrypt(const std::string& inputFile, const std::string& outputFile);
    void polibiusDecrypt(const std::string& inputFile, const std::string& outputFile);
}

#endif