#include "UserManager.h"

#ifdef _WIN32
#include <windows.h>
#endif
// :filename 클래스의 변수 ( 매개 변수)
UserManager::UserManager(const string& filename) : filename(filename) {
    loadFromCSV();
}

// 텍스트 색상을 설정하는 함수 (Windows에서만 동작)
void UserManager::setColor(int color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#endif
}

// 테두리 출력 함수
void UserManager::printBorder() {
    cout << "+------------------------------------------+\n";
}

// 사용자 정보를 CSV 파일에 저장하는 함수
void UserManager::saveToCSV() {
    ofstream file(filename);

    if (file.is_open()) {
        for (const auto& user : users) {
            file << user.getUsername() << "," << user.getEmail() << "," << user.getPassword() << "," << user.getX() << "," << user.getY() << "\n";
        }
        file.close();
    }
    else {
        setColor(12); // Red
        cout << "Unable to open file for writing.\n";
        setColor(7);  // Reset to default
    }
}

// CSV 파일에서 사용자 정보를 불러오는 함수
void UserManager::loadFromCSV() {
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string username, email, password;
            int x, y;

            if (getline(ss, username, ',') && getline(ss, email, ',') && getline(ss, password, ',') && ss >> x && ss.ignore() && ss >> y) {
                User user;
                user.setUsername(username);
                user.setEmail(email);
                user.setPassword(password);
                user.setX(x);
                user.setY(y);

                users.push_back(user);
            }
        }
        file.close();
    }
    else {
        setColor(12); // Red
        cout << "Unable to open file for reading.\n";
        setColor(7);  // Reset to default
    }
}

// 사용자 등록 함수
void UserManager::registerUser() {
    User newUser;

    printBorder();
    setColor(11); // Cyan
    cout << "|             User Registration            |\n";
    printBorder();

    setColor(7); // Reset to default
    string username, email, password;
    int x, y;

    cout << "Enter username: ";
    cin >> username;
    newUser.setUsername(username);

    cout << "Enter email: ";
    cin >> email;
    newUser.setEmail(email);

    cout << "Enter password: ";
    cin >> password;
    newUser.setPassword(password);

    cout << "Enter x value: ";
    cin >> x;
    newUser.setX(x);

    cout << "Enter y value: ";
    cin >> y;
    newUser.setY(y);

    users.push_back(newUser);
    saveToCSV();

    setColor(10); // Green
    cout << "User registered successfully!\n";
    setColor(7);  // Reset to default
}

// 사용자 로그인 함수
bool UserManager::loginUser() {
    string username, password;

    printBorder();
    setColor(11); // Cyan
    cout << "|                 User Login               |\n";
    printBorder();

    setColor(7); // Reset to default
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (const auto& user : users) {
        if (user.getUsername() == username && user.getPassword() == password) {
            setColor(10); // Green
            cout << "Login successful! Welcome, " << user.getUsername() << ".\n";
            setColor(7);  // Reset to default
            return true;
        }
    }

    setColor(12); // Red
    cout << "Login failed. Please check your username and password.\n";
    setColor(7);  // Reset to default
    return false;
}

// 메인 메뉴 실행 함수
void UserManager::run() {
    int choice;
    while (true) {
        printBorder();
        setColor(11); // Cyan
        cout << "|                Main Menu                 |\n";
        printBorder();

        setColor(7); // Reset to default
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            registerUser();
        }
        else if (choice == 2) {
            loginUser();
        }
        else if (choice == 3) {
            setColor(10); // Green
            cout << "Exiting the program.\n";
            setColor(7);  // Reset to default
            break;
        }
        else {
            setColor(12); // Red
            cout << "Invalid option. Please choose again.\n";
            setColor(7);  // Reset to default
        }
    }
}
