#include "general.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <codecvt>
#include <vector>

using namespace std;
using namespace std::filesystem;

bool isTextFile(const string& filePath) {
    ifstream file(filePath, ios::binary);
    if (!file) return false;
    char c = 0;
    int count = 0;
    while (file.get(c) && count < 512) {
        if ((unsigned char)c == 0) return false; // null-байт — бинарный файл
        if ((unsigned char)c < 32 && (c != 9 && c != 10 && c != 13 && c != 12)) return false;
        count++;
    }
    return true;
}

void tryCreateFile(const string& filePath){
    cout << filePath << " не существует. Хотите создать? (y/n): ";
    char choice = 0;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 'y') {
        try {   
            string dirs = path(filePath).parent_path().string();
            if (!dirs.empty()) create_directories(dirs);
            ofstream(filePath).close();
        } catch (const filesystem_error& ferror){
            cerr << ferror.what() << endl;
        }
        cout << "Файл " << filePath << " создан" << endl;
    } else {
        throw invalid_argument("Невозможно записать в несуществующий файл: " + filePath);
    }
}

wstring readFile(const string& inputFile) {
    ifstream input(inputFile, ios::binary);
    if (!input) {
        try {
            tryCreateFile(inputFile);
            input.open(inputFile, ios::binary);
            if (!input) throw runtime_error("Не удалось создать файл: " + inputFile);
        } catch (const exception& e) {
            throw runtime_error(e.what());
        }
    }
    vector<char> buffer((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
    input.close();
    wstring result;
    size_t i = 0;
    while (i + 1 < buffer.size()) {
        wchar_t wc = (static_cast<unsigned char>(buffer[i+1]) << 8) | static_cast<unsigned char>(buffer[i]);
        result.push_back(wc);
        i += 2;
    }
    if (i < buffer.size()) {
        wchar_t wc = static_cast<unsigned char>(buffer[i]);
        result.push_back(wc);
    }
    return result;
}

void writeFile(const string& outputFile, const wstring& result) {
    ofstream output(outputFile, ios::binary);
    if (!output) {
        try {
            tryCreateFile(outputFile);
            output.open(outputFile, ios::binary);
            if (!output) throw runtime_error("Не удалось создать файл: " + outputFile);
        } catch (const exception& e) {
            throw runtime_error(e.what());
        }
    }
    for (wchar_t wc : result) {
        char low = wc & 0xFF;
        char high = (wc >> 8) & 0xFF;
        output.put(low);
        output.put(high);
    }
    output.close();
}

void* loadLibrary(const string& libraryPath) {
    void* handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
    if (!handle) {
        throw runtime_error(dlerror());
    }
    return handle;
}