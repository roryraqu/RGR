#include "general.h"
#include "passwd.h"
#include <codecvt>
#include <sstream>
#include <limits>

using namespace std;

enum UserAction {
    CHANGE_PASSWORD,
    ENCRYPT_TEXT,
    DECRYPT_TEXT,
    ENCRYPT_FILE,
    DECRYPT_FILE,
    EXIT
};

int main() {
    setlocale(LC_ALL, "");

    try {
        login();
    } catch (const exception& e) {
        cerr << e.what() << endl;
        return 1;
    }

    while (true) {
        try {
            cout << "Смена пароля (0)" << endl;
            cout << "Шифрование текста (1)" << endl;
            cout << "Дешиврование текста (2)" << endl;
            cout << "Шифрование файла (3)" << endl;
            cout << "Дешифрование файла (4)" << endl;
            cout << "Выход (5)" << endl;
            cout << "\nВаш выбор: ";

            int userCode = 0;
            if (!(cin >> userCode)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Неверный ввод. Введите число от 0 до 5." << endl;
                continue;
            }

            switch (static_cast<UserAction>(userCode)) {
                case CHANGE_PASSWORD: { // Смена пароля
                    try {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        changePasswd();
                    } catch (const exception& e) {
                        cerr << e.what() << endl;
                    }
                    break;
                }
                case ENCRYPT_TEXT: // Шифрование текста
                case DECRYPT_TEXT: { // Дешифрование текста
                    cout << "\033[2J\033[1;1H";
                    cout << "Назад в меню (0)" << endl;
                    cout << "Матричная шифровка (1)" << endl;
                    cout << "Шифр Гронсфельда (2)" << endl;
                    cout << "Шифр Полибия (3)" << endl;

                    cout << "\nВаш выбор: ";
                    int algo = 0;
                    if (!(cin >> algo)) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cerr << "Неверный ввод. Введите число от 0 до 3." << endl;
                        cout << "\033[2J\033[1;1H";
                        continue;
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if (algo == 0) {
                        cout << "\033[2J\033[1;1H";
                        continue;
                    }
                    string inputText, key, tempIn = "/tmp/cipherIN", tempOut = "/tmp/cipherOUT";
                    if (userCode == 1)
                        cout << "Введите текст для шифрования (закончите ввод пустой строкой):" << endl;
                    else
                        cout << "Введите текст для дешифрования (закончите ввод пустой строкой):" << endl;

                    string line;
                    string inputStream;
                    while (getline(cin, line)) {
                        if (line.empty()) break;
                        inputStream += line + '\n';
                    }
                    wstring_convert<codecvt_utf8<wchar_t>> converter;
                    if (!inputStream.empty() && inputStream.back() == '\n') {
                        inputStream.pop_back();
                    }
                    writeFile(tempIn, converter.from_bytes(inputStream));

                    if (algo == 1) {
                        auto matrixHandle = loadLibrary("/usr/local/lib/libmatrix.so");
                        if (userCode == 1) {
                            auto spiralMatrix = loadFunction<void(*)(const string&, const string&)>(matrixHandle, "spiralMatrix");
                            spiralMatrix(tempIn, tempOut);
                        } else {
                            auto despiralMatrix = loadFunction<void(*)(const string&, const string&)>(matrixHandle, "despiralMatrix");
                            despiralMatrix(tempIn, tempOut);
                        }
                    } else if (algo == 2) {
                        auto gronsfeldHandle = loadLibrary("/usr/local/lib/libgronsfeld.so");
                        if (userCode == 1) {
                            auto gronsfeldEncrypt = loadFunction<void(*)(const string&, const string&, const string&, bool)>(gronsfeldHandle, "gronsfeldEncrypt");
                            cout << "Введите ключ шифрования: ";
                            getline(cin, key);
                            gronsfeldEncrypt(tempIn, tempOut, key, false);
                        } else {
                            auto gronsfeldDecrypt = loadFunction<void(*)(const string&, const string&, const string&)>(gronsfeldHandle, "gronsfeldDecrypt");
                            cout << "Введите ключ шифрования: ";
                            getline(cin, key);
                            gronsfeldDecrypt(tempIn, tempOut, key);
                        }
                    } else if (algo == 3) {
                        auto polibiusHandle = loadLibrary("/usr/local/lib/libpolibius.so");
                        if (userCode == 1) {
                            auto polibiusEncrypt = loadFunction<void(*)(const string&, const string&)>(polibiusHandle, "polibiusEncrypt");
                            polibiusEncrypt(tempIn, tempOut);
                        } else {
                            auto polibiusDecrypt = loadFunction<void(*)(const string&, const string&)>(polibiusHandle, "polibiusDecrypt");
                            polibiusDecrypt(tempIn, tempOut);
                        }
                    } else {
                        cerr << "Нет такого алгоритма" << endl;
                        break;
                    }
            
                    wstring result = readFile(tempOut);
                    cout << "\033[2J\033[1;1H" << "Результат: " << converter.to_bytes(result) << endl;
                    break;
                }
                case ENCRYPT_FILE: // Шифрование файла
                case DECRYPT_FILE: { // Дешифрование файла
                    cout << "\033[2J\033[1;1H";
                    cout << "Назад в меню (0)" << endl;
                    cout << "Матричная шифровка (1)" << endl;
                    cout << "Шифр Гронсфельда (2)" << endl;
                    cout << "Шифр Полибия (3)" << endl;
                    
                    cout << "\nВаш выбор: ";
                    int algo = 0;
                    if (!(cin >> algo)) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cerr << "Неверный ввод. Введите число от 0 до 3." << endl;
                        cout << "\033[2J\033[1;1H";
                        continue;
                    }
                    if (algo == 0) continue;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    string inputFile, outputFile, key;
                    cout << "Введите имя входного файла: ";
                    getline(cin, inputFile);
                    cout << "Введите имя выходного файла: ";
                    getline(cin, outputFile);

                    if (algo == 1) {
                        auto matrixHandle = loadLibrary("/usr/local/lib/libmatrix.so");
                        if (userCode == 3) {
                            auto spiralMatrix = loadFunction<void(*)(const string&, const string&)>(matrixHandle, "spiralMatrix");
                            spiralMatrix(inputFile, outputFile);
                        } else {
                            auto despiralMatrix = loadFunction<void(*)(const string&, const string&)>(matrixHandle, "despiralMatrix");
                            despiralMatrix(inputFile, outputFile);
                        }
                    } else if (algo == 2) {
                        auto gronsfeldHandle = loadLibrary("/usr/local/lib/libgronsfeld.so");
                        if (userCode == 3) {
                            auto gronsfeldEncrypt = loadFunction<void(*)(const string&, const string&, const string&, bool)>(gronsfeldHandle, "gronsfeldEncrypt");
                            cout << "Введите ключ шифрования: ";
                            getline(cin, key);
                            gronsfeldEncrypt(inputFile, outputFile, key, false);
                        } else {
                            auto gronsfeldDecrypt = loadFunction<void(*)(const string&, const string&, const string&)>(gronsfeldHandle, "gronsfeldDecrypt");
                            cout << "Введите ключ шифрования: ";
                            getline(cin, key);
                            gronsfeldDecrypt(inputFile, outputFile, key);
                        }
                    } else if (algo == 3) {
                        auto polibiusHandle = loadLibrary("/usr/local/lib/libpolibius.so");
                        if (userCode == 3) {
                            auto polibiusEncrypt = loadFunction<void(*)(const string&, const string&)>(polibiusHandle, "polibiusEncrypt");
                            polibiusEncrypt(inputFile, outputFile);
                        } else {
                            auto polibiusDecrypt = loadFunction<void(*)(const string&, const string&)>(polibiusHandle, "polibiusDecrypt");
                            polibiusDecrypt(inputFile, outputFile);
                        }
                    } else {
                        cerr << "Нет такого алгоритма" << endl;
                        break;
                    }
                    cout << "\033[2J\033[1;1H" << "Готово!" << endl;
                    break;
                }
                case EXIT: {
                    return 0;
                }
                default: {
                    cerr << "Такой опции нет" << endl;
                    break;
                }
            }
        } catch (const exception& e) {
            cerr << e.what() << endl;
        }
    }
}