#ifndef GENERAL_H
#define GENERAL_H

#include <dlfcn.h>
#include <locale>

using namespace std;

wstring readFile(const string& inputFile);
void writeFile(const string& outputFile, const wstring& result);
void tryCreateFile(const string& filePath);
void* loadLibrary(const string& libraryPath);
bool isTextFile(const string& filePath);

template<typename Func>
Func loadFunction(void* libraryHandle, const string& functionName) {
    void* funcPtr = dlsym(libraryHandle, functionName.c_str());
    if (!funcPtr) {
        throw runtime_error(dlerror());
    }
    return reinterpret_cast<Func>(funcPtr);
}

#endif