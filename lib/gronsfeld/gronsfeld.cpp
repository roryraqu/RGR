#include "gronsfeld.h"
#include <cstdint>
#include <fstream>

wchar_t dynamicShift(wchar_t wc, int shift){
    if (wc >= L'a' && wc <= L'z'){
        if (wc + shift > L'z') return wc - 26 + shift;
        else if (wc + shift < L'a') return wc + 26 - shift;
    } else if (wc >= L'а' && wc <= L'я'){
        if (wc + shift > L'я') return wc - 32 + shift;
        else if (wc + shift < L'а') return wc + 32 - shift;
    } else if (wc >= L'A' && wc <= L'Z'){
        if (wc + shift > L'Z') return wc - 26 + shift;
        else if (wc + shift < L'A') return wc + 26 - shift;
    } else if (wc >= L'А' && wc <= L'Я'){
        if (wc + shift > L'Я') return wc - 32 + shift;
        else if (wc + shift < L'А') return wc + 32 - shift;
    }

    return wc + shift;
}

wchar_t binaryShift(wchar_t wc, int shift){
    return static_cast<wchar_t>((static_cast<uint32_t>(wc) + shift) % 65536);
}

vector<int> keyToVec(const string& key, bool isEncrypted){
    vector<int> shifts;
    int mul = isEncrypted ? -1 : 1;

    if (key.empty()){
        throw invalid_argument("Ключ не может быть пустым");
    }
    
    for (char c : key){
        if (c > '9' || c < '0'){
            throw invalid_argument("В ключе должны быть только числа");
        } else {
            int shift = mul * (c - '0');
            shifts.push_back(shift);
        }
    }

    return shifts;
}

void gronsfeldEncrypt(const string& inputFile, const string& outputFile, const string& key, bool isEncrypted = false){
    wstring content = readFile(inputFile);
    vector<int> shifts = keyToVec(key, isEncrypted);

    wstring result;
    size_t sizeOfKey = shifts.size();

    if (!isTextFile(inputFile)) {
        // Для бинарных файлов используем binaryShift
        for (size_t i = 0; i < content.length(); i++) {
            int shift = shifts[i % sizeOfKey];
            result += binaryShift(content[i], shift);
        }
    } else {
        // Для текстовых файлов используем dynamicShift
        for (size_t i = 0; i < content.length(); i++) {
            int shift = shifts[i % sizeOfKey];
            result += dynamicShift(content[i], shift);
        }
    }

    writeFile(outputFile, result);
}

void gronsfeldDecrypt(const string& inputFile, const string& outputFile, const string& key){
    gronsfeldEncrypt(inputFile, outputFile, key, true);
}