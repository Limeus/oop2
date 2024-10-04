#ifndef FIVE_H
#define FIVE_H

#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>

class Five {
private:
    unsigned char* digits;  // Массив для хранения цифр пятиричного числа
    size_t size;            // Размер числа

    // Метод для очистки памяти
    void clear();

public:
    // Конструктор по умолчанию
    Five();

    // Конструктор с заданным размером и инициализацией
    Five(const size_t& n, unsigned char t = '0');

    // Конструктор из строки
    Five(const std::string& str);

    // Конструктор копирования
    Five(const Five& other);

    // Конструктор перемещения
    Five(Five&& other) noexcept;

    // Деструктор
    ~Five();

    // Оператор присваивания копированием
    Five& operator=(const Five& other);

    // Оператор присваивания перемещением
    Five& operator=(Five&& other) noexcept;

    // Арифметические операторы
    Five& operator+=(const Five& other);
    Five& operator-=(const Five& other);
    Five operator+(const Five& other) const;
    Five operator-(const Five& other) const;

    // Операторы сравнения
    bool operator==(const Five& other) const;
    bool operator!=(const Five& other) const;
    bool operator<(const Five& other) const;
    bool operator>(const Five& other) const;

    // Оператор вывода
    friend std::ostream& operator<<(std::ostream& os, const Five& obj);
};

#endif // FIVE_H
