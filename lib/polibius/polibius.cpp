#include "polibius.h"
#include <iostream>
#include <sstream>

tuple<int, int, int> polibiusCode(wchar_t wc){
    if (wc >= L'a' && wc <= L'z'){
        int distance = wc - L'a';
        return {
            distance / 5 + 1, // строка
            distance % 5 + 1, // колонка
            LOWER_EN // вид литерала
        };
    } else if (wc >= L'A' && wc <= L'Z'){
        int distance = wc - L'A';
        return {
            distance / 5 + 1,
            distance % 5 + 1,
            UPPER_EN
        };
    } else if (wc >= L'а' && wc <= L'я'){
        int distance = wc - L'а';
        return {
            distance / 6 + 1,
            distance % 6 + 1,
            LOWER_RU
        };
    } else if (wc >= L'А' && wc <= L'Я'){
        int distance = wc - L'А';
        return {
            distance / 6 + 1,
            distance % 6 + 1,
            UPPER_RU
        };
    }

    return {static_cast<int>(wc), UNKNOWN, UNKNOWN};
}

wchar_t polibiusCharacter(int position){
    int row = position / 100; // строка
    int col = (position % 100) / 10; // столбец
    int typeOfLit = position % 10; // вид литерала

    switch (typeOfLit){
        case LOWER_EN: return L'a' + (row - 1) * 5 + (col - 1);
        case UPPER_EN: return L'A' + (row - 1) * 5 + (col - 1);
        case LOWER_RU: return L'а' + (row - 1) * 6 + (col - 1);
        case UPPER_RU: return L'А' + (row - 1) * 6 + (col - 1);
        default: return static_cast<wchar_t>(row);
    }
}

void polibiusEncrypt(const string& inputFile, const string& outputFile){
    wstring content = readFile(inputFile);
    wstringstream result;

    for (auto wc : content){
        auto position = polibiusCode(wc);
        result << get<0>(position) << get<1>(position) << get<2>(position) << " ";
    }

    writeFile(outputFile, result.str());
}

void polibiusDecrypt(const string& inputFile, const string& outputFile){
    wstringstream content(readFile(inputFile));
    wstringstream result;
    int position = 0;

    while (content >> position){
        result << polibiusCharacter(position);
    }
    
    writeFile(outputFile, result.str());
}