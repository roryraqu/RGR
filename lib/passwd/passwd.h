#ifndef PASSWD_H
#define PASSWD_H

#include <iostream>

using namespace std;

void login();
size_t countHash(const string& passwd);
void changePasswd();

#endif