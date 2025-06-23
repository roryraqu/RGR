#include "passwd.h"
#include <fstream>
#include <unistd.h>

using namespace std;

void login(){
    string userInput = getpass("Введите пароль: ");
    ifstream ifs("/etc/ciphers");
    size_t curHash = 0;
    if (!ifs || !(ifs >> curHash)) {
        throw runtime_error("Не удалось прочитать хэш пароля");
    }
    ifs.close();
    if (curHash != countHash(userInput)) {
        throw invalid_argument("Неверный пароль");
    }
}

size_t countHash(const string& passwd) {
    size_t hashValue = 0;
    const size_t p = 41;
    const size_t mod = 1e9 + 7;
    
    for (char c : passwd) {
        hashValue = (hashValue * p + c) % mod;
    }
    return hashValue;
}

void changePasswd(){
    ifstream ifs("/etc/ciphers");
    size_t curHash = 0;
    if (!ifs || !(ifs >> curHash)) {
        throw runtime_error("Не удалось прочитать хэш пароля");
    }
    ifs.close();

    string userInput = getpass("Введите пароль: ");

    if (curHash == countHash(userInput)){
        userInput = getpass("Введите новый пароль: ");

        ofstream ofs("/etc/ciphers", std::ios::trunc);
        if (!ofs){
            throw runtime_error("Не удалось записать новый пароль. Попробуйте 'sudo cipher'");
        }
        ofs << countHash(userInput);
        ofs.close();

        cout << "Пароль изменен успешно" << endl;
    } else {
        throw invalid_argument("Неправильный пароль");
    }
}