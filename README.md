# РГР — Консольное приложение для шифрования и дешифрования

## Описание
Данный проект представляет собой консольное приложение для шифрования и дешифрования текста и файлов с использованием различных алгоритмов:
- **Спиральная матрица**
- **Шифр Гронсфельда**
- **Шифр Полибия**

Также реализована система управления паролем для защиты доступа к функционалу программы.

## Возможности

- Шифрование и дешифрование текста и файлов
- Поддержка русского и английского алфавитов
- Выбор алгоритма шифрования
- Смена пароля пользователя

## Установка

1. Клонируйте репозиторий:
   ```
   git clone https://github.com/roryraqu/RGR
   ```
2. Перейдите в директорию проекта:
   ```
   cd РГР/build/package/
   ```
3. Установите зависимости и соберите проект:
   ```
   sudo chmod +x install.sh
   sudo ./install.sh
   ```

## Запуск

Для запуска приложения используйте команду:
```
cipher
```

## Структура проекта

```cpp
.
├── build
│   ├── Makefile
│   └── package
│       ├── bin
│       │   └── cipher
│       ├── install.sh
│       └── lib
│           ├── libgronsfeld.so
│           ├── libmatrix.so
│           └── libpolibius.so
├── lib
│   ├── general
│   │   ├── general.cpp <- general.h
│   │   └── general.h
│   ├── gronsfeld
│   │   ├── gronsfeld.cpp <- gronsfeld.h
│   │   └── gronsfeld.h
│   ├── matrix
│   │   ├── matrix.cpp <- matrix.h
│   │   └── matrix.h
│   ├── passwd
│   │   ├── passwd.cpp <- passwd.h
│   │   └── passwd.h
│   └── polibius
│       ├── polibius.cpp <- polibius.h
│       └── polibius.h
├── README.md
└── src
    └── main.cpp <- general.h, passwd.h

12 directories, 18 files
```