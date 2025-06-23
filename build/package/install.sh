#!/bin/bash

# Проверка на root
if [ "$(id -u)" -ne 0 ]; then
    echo "Please run as root"
    exit 1
fi

# Каталоги установки
BIN_DIR="/usr/local/bin"
LIB_DIR="/usr/local/lib"

# Создание каталогов, если их нет
mkdir -p "$BIN_DIR"
mkdir -p "$LIB_DIR"

# Копирование файлов
cp bin/cipher "$BIN_DIR"
cp lib/*.so "$LIB_DIR"

# Установка прав
chmod 755 "$BIN_DIR/cipher"
chmod 644 "$LIB_DIR"/*.so

echo "Installation complete"