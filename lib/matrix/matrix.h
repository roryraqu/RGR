#ifndef MATRIX_H
#define MATRIX_H

#include "../general/general.h"
#include <vector>

using namespace std;

extern "C" {
    void writeMatrix(const string& outputFile, const vector<wstring>& matrix);
    void fillMatrix(size_t sizeOfMatrix, const wstring& content, vector<wstring>& matrix);
    void spiralMatrix(const string& inputFile, const string& outputFile);
    void despiralMatrix(const string& inputFile, const string& outputFile);
}

#endif