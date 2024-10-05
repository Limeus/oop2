#include "include/five.h"
#include <iostream>
#include <Windows.h>


int main() {
    SetConsoleOutputCP(CP_UTF8);
    try {
        Five num1("4321"); // Пятиричное число
        Five num2("4231"); // Пятиричное число

        // Пример использования арифметических операций
        Five result = num1 + num2;

        std::cout << "Result of sum: ";
        std::cout << result << std::endl; // Печать результата

        std::cout << std::endl;
        if (num1 > num2) {
            std::cout << "num1 is greater than num2" << std::endl;
        } else if (num1 < num2) {
            std::cout << "num1 is less than num2" << std::endl;
        } else {
            std::cout << "num1 is equal to num2" << std::endl;
        }

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
