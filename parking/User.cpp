#include "User.h"

// Getter 및 Setter 함수 정의

string User::getUsername() const {
    return username;
}

void User::setUsername(const string& username) {
    this->username = username;
}

string User::getEmail() const {
    return email;
}

void User::setEmail(const string& email) {
    this->email = email;
}

string User::getPassword() const {
    return password;
}

void User::setPassword(const string& password) {
    this->password = password;
}

int User::getX() const {
    return x;
}

void User::setX(int x) {
    this->x = x;
}

int User::getY() const {
    return y;
}

void User::setY(int y) {
    this->y = y;
}
