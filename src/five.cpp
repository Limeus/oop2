#include "../include/five.h"
#include <stdexcept>
#include <algorithm>

// Метод для очистки памяти
void Five::clear() {
    delete[] digits;
}

// Конструктор по умолчанию
Five::Five() : digits(new unsigned char[1]{0}), size(1) {}

// Конструктор с заданным размером и инициализацией
Five::Five(const size_t& n, unsigned char t) {
    if (t < 0 || t > 4) throw std::invalid_argument("Число должно быть в диапазоне от 0 до 4");
    size = (n > 0) ? n : 1;
    digits = new unsigned char[size];
    std::fill(digits, digits + size, t);
}

// Конструктор из строки
Five::Five(const std::string& str) {
    size_t leadingZeros = 0;
    bool countZeros = true;

    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] < '0' || str[i] > '4') throw std::invalid_argument("Некорректное пятиричное число");
        if (countZeros && str[i] == '0') {
            leadingZeros++;
        } else {
            countZeros = false;
        }
    }

    size = str.size() - leadingZeros;
    if (size == 0) {
        digits = new unsigned char[1]{0};
        size = 1;
    } else {
        digits = new unsigned char[size];
        for (size_t i = 0; i < size; i++) {
            digits[i] = str[str.size() - 1 - i] - '0'; // Сохраняем цифры в реверсивном порядке
        }
    }
}

// Конструктор копирования
Five::Five(const Five& other) : size(other.size), digits(new unsigned char[other.size]) {
    std::copy(other.digits, other.digits + other.size, digits);
}

// Конструктор перемещения
Five::Five(Five&& other) noexcept : size(other.size), digits(other.digits) {
    other.size = 0;
    other.digits = nullptr;
}

// Деструктор
Five::~Five() {
    clear();
}

// Оператор присваивания копированием
Five& Five::operator=(const Five& other) {
    if (this != &other) {
        clear();
        size = other.size;
        digits = new unsigned char[size];
        std::copy(other.digits, other.digits + size, digits);
    }
    return *this;
}

// Оператор присваивания перемещением
Five& Five::operator=(Five&& other) noexcept {
    if (this != &other) {
        clear();
        size = other.size;
        digits = other.digits;
        other.size = 0;
        other.digits = nullptr;
    }
    return *this;
}

// Арифметические операторы
Five& Five::operator+=(const Five& other) {
    size_t maxSize = std::max(size, other.size);
    unsigned char* result = new unsigned char[maxSize + 1]{0};
    unsigned char carry = 0;

    for (size_t i = 0; i < maxSize; i++) {
        unsigned char digit1 = (i < size) ? digits[i] : 0;
        unsigned char digit2 = (i < other.size) ? other.digits[i] : 0;
        unsigned char sum = digit1 + digit2 + carry;

        result[i] = sum % 5;
        carry = sum / 5;
    }

    if (carry) {
        result[maxSize] = carry;
        maxSize++;
    }

    delete[] digits;
    digits = result;
    size = maxSize;

    return *this;
}

Five Five::operator+(const Five& other) const {
    Five result;
    size_t max_size = std::max(size, other.size);
    result.size = max_size + 1; // Размер результата (может быть больше на 1 разряд)
    result.digits = new unsigned char[result.size]{0};

    unsigned char carry = 0;

    for (size_t i = 0; i < max_size; ++i) {
        unsigned char digit1 = (i < size) ? digits[i] : 0;
        unsigned char digit2 = (i < other.size) ? other.digits[i] : 0;

        unsigned char sum = digit1 + digit2 + carry;
        result.digits[i] = sum % 5; // остаток от деления на 5
        carry = sum / 5; // так как число пятиричное, делим на 5
    }

    if (carry > 0) {
        result.digits[max_size] = carry;
        result.size = max_size + 1; // Увеличиваем размер, если есть перенос
    } else {
        result.size = max_size; // Если переноса нет, уменьшаем размер
    }

    return result;
}

Five Five::operator-(const Five& other) const {
    if (*this < other) {
        throw std::invalid_argument("Результат вычитания не может быть отрицательным");
    }

    Five result;
    result.size = size; // Размер результата равен размеру текущего объекта
    result.digits = new unsigned char[result.size]{0};

    unsigned char borrow = 0; // Заимствование

    for (size_t i = 0; i < size; ++i) {
        unsigned char digit1 = digits[i];
        unsigned char digit2 = (i < other.size) ? other.digits[i] : 0;

        if (digit1 < digit2 + borrow) {
            digit1 += 5; // Заимствуем
            result.digits[i] = (digit1 - digit2 - borrow) % 5; // Вычисляем результат
            borrow = 1; // Устанавливаем заимствование
        } else {
            result.digits[i] = digit1 - digit2 - borrow; // Вычисляем результат
            borrow = 0; // Сбрасываем заимствование
        }
    }

    // Удаляем начальные нули, если они есть
    while (result.size > 1 && result.digits[result.size - 1] == 0) {
        result.size--;
    }

    return result;
}

Five& Five::operator-=(const Five& other) {
    if (*this < other) {
        throw std::invalid_argument("Результат вычитания не может быть отрицательным");
    }

    unsigned char borrow = 0; // Заимствование

    for (size_t i = 0; i < size; ++i) {
        unsigned char digit1 = digits[i];
        unsigned char digit2 = (i < other.size) ? other.digits[i] : 0;

        if (digit1 < digit2 + borrow) {
            digit1 += 5; // Заимствуем
            digits[i] = (digit1 - digit2 - borrow) % 5; // Вычисляем результат
            borrow = 1; // Устанавливаем заимствование
        } else {
            digits[i] = digit1 - digit2 - borrow; // Вычисляем результат
            borrow = 0; // Сбрасываем заимствование
        }
    }

    // Удаляем начальные нули, если они есть
    while (size > 1 && digits[size - 1] == 0) {
        size--;
    }

    return *this;
}


// Операторы сравнения
bool Five::operator==(const Five& other) const {
    if (size != other.size) return false;
    for (size_t i = 0; i < size; i++) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

bool Five::operator!=(const Five& other) const {
    return !(*this == other);
}

bool Five::operator<(const Five& other) const {
    if (size != other.size) return size < other.size;
    for (size_t i = size; i > 0; i--) {
        if (digits[i - 1] != other.digits[i - 1]) {
            return digits[i - 1] < other.digits[i - 1];
        }
    }
    return false;
}

bool Five::operator>(const Five& other) const {
    return other < *this;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Five& obj) {
    for (size_t i = obj.size; i > 0; i--) {
        os << (char)(obj.digits[i - 1] + '0'); // Конвертация цифр обратно в символы
    }
    return os;
}

