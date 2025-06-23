#ifndef GRONSFELD_H
#define GRONSFELD_H

#include "../general/general.h"
#include <vector>

using namespace std;

extern "C" {
    wchar_t dynamicShift(wchar_t wc, int shift);
    vector<int> keyToVec(const string& key, bool isEncrypted);
    void gronsfeldEncrypt(const string& inputFile, const string& outputFile, const string& key, bool isEncrypted);
    void gronsfeldDecrypt(const string& inputFile, const string& outputFile, const string& key);
}

#endif