#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
private:
    string username;
    string email;
    string password;
    int x;
    int y;

public:
    // 기본 생성자
    User() : x(0), y(0) {}

    // 매개변수가 있는 생성자
    User(const string& username, const string& email, const string& password, int x, int y)
        : username(username), email(email), password(password), x(x), y(y) {}

    // Getter 및 Setter 함수들
    string getUsername() const;
    void setUsername(const string& username);

    string getEmail() const;
    void setEmail(const string& email);

    string getPassword() const;
    void setPassword(const string& password);

    int getX() const;
    void setX(int x);

    int getY() const;
    void setY(int y);
};

#endif // USER_H
