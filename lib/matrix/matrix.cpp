#include "matrix.h"
#include <sstream>
#include <cmath>

void writeMatrix(const string& outputFile, const vector<wstring>& matrix){
    wstring output;
    for (const auto& ws : matrix){
        output += ws;
    }
    writeFile(outputFile, output);
}

void fillMatrix(size_t sizeOfMatrix, const wstring& content, vector<wstring>& matrix){
    for (size_t i = 0; i < sizeOfMatrix; i++){
        for (size_t j = 0; j < sizeOfMatrix; j++){
            size_t idx = i * sizeOfMatrix + j;
            if (idx < content.size())
                matrix[i][j] = content[idx];
        }
    }
}

void spiralMatrix(const string& inputFile, const string& outputFile) {
    wstring content = readFile(inputFile);
    size_t lenOfContent = content.length();
    size_t sizeOfMatrix = ceil(sqrt(lenOfContent));
    size_t centr = sizeOfMatrix / 2;

    size_t i = centr, j = centr, step = 0, cur = 0;
    vector<wstring> matrix(sizeOfMatrix, wstring(sizeOfMatrix, ' '));
    for (size_t k = 0, tree = 0; cur < lenOfContent; k++, tree++) {
        if (k % 2 == 0) step++;

        if (tree % 4 == 0) {
            for (size_t m = 0; m < step && cur < lenOfContent; m++) {
                matrix[i][j--] = content[cur++];
            }
        }   
        if (tree % 4 == 1) {
            for (size_t m = 0; m < step && cur < lenOfContent; m++) {
                matrix[i--][j] = content[cur++];
            }
        }
        if (tree % 4 == 2) {
            for (size_t m = 0; m < step && cur < lenOfContent; m++) {
                if (j >= sizeOfMatrix) break;
                matrix[i][j++] = content[cur++];
            }
        }
        if (tree % 4 == 3) {
            for (size_t m = 0; m < step && cur < lenOfContent; m++) {
                if (i >= sizeOfMatrix) break;
                matrix[i++][j] = content[cur++];
            }
        }
    }

    writeMatrix(outputFile, matrix);
}

void despiralMatrix(const string& inputFile, const string& outputFile){
    wstring content = readFile(inputFile);
    size_t lenOfContent = content.length();
    size_t sizeOfMatrix = ceil(sqrt(lenOfContent));
    size_t centr = sizeOfMatrix / 2;

    vector<wstring> encryptedMatrix(sizeOfMatrix, wstring(sizeOfMatrix, '\0'));
    fillMatrix(sizeOfMatrix, content, encryptedMatrix);

    wstring decryptedMatrix;
    size_t i = centr, j = centr, step = 0, cur = 0;
    for (int k = 0, tree = 0; cur < lenOfContent; k++, tree++) {
        if (k % 2 == 0) step++;

        if (tree % 4 == 0) {
            for (size_t m = 0; m < step; m++) {
                decryptedMatrix.push_back(encryptedMatrix[i][j--]);
                cur++;
            }
        }   
        if (tree % 4 == 1) {
            for (size_t m = 0; m < step; m++) {
                decryptedMatrix.push_back(encryptedMatrix[i--][j]);
                cur++;
            }
        }
        if (tree % 4 == 2) {
            for (size_t m = 0; m < step; m++) {
                if (j >= sizeOfMatrix) break;
                decryptedMatrix.push_back(encryptedMatrix[i][j++]);
                cur++;
            }
        }
        if (tree % 4 == 3) {
            for (size_t m = 0; m < step; m++) {
                if (i >= sizeOfMatrix) break;
                decryptedMatrix.push_back(encryptedMatrix[i++][j]);
                cur++;
            }
        }
    }

    writeFile(outputFile, decryptedMatrix);
}