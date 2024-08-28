#include "UserManager.h"

using namespace std;

int main() {
    UserManager userManager("users.csv");
    userManager.run();
    return 0;
}
