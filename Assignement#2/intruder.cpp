#include <iostream>
#include <cstring>

int main() {
    char input[10];
    const char correct_password[] = "cbnu_r00t";  // Correct password hardcoded for demonstration

    std::cout << "password: ";
    std::cin >> input;

    // Compare the input with the correct password
    if (strcmp(input, correct_password) == 0) {
        std::cout << "hello owner" << std::endl;
    } else {
        std::cout << "you're intruder" << std::endl;
    }

    return 0;
}
