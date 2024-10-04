#include "gtest/gtest.h"
#include "../include/five.h"

// Тесты для класса Five
TEST(FiveTest, DefaultConstructor) {
    Five five; // Создаем объект Five по умолчанию
    EXPECT_EQ(five, Five("0")); // Ожидаем, что объект равен "0"
}

TEST(FiveTest, ConstructorWithSize) {
    Five five(5, 2); // Создаем объект Five с размером 5 и инициализацией 2
    EXPECT_EQ(five, Five("22222")); // Ожидаем, что объект равен "22222"
}

TEST(FiveTest, ConstructorFromString) {
    Five five("120"); // Создаем объект Five из строки
    EXPECT_EQ(five, Five("120")); // Ожидаем, что объект равен "120"
}

TEST(FiveTest, CopyConstructor) {
    Five five1("123"); // Создаем первый объект Five
    Five five2(five1); // Создаем копию
    EXPECT_EQ(five1, five2); // Ожидаем, что они равны
}

TEST(FiveTest, MoveConstructor) {
    Five five1("123"); // Создаем первый объект Five
    Five five2(std::move(five1)); // Перемещаем
    EXPECT_EQ(five2, Five("123")); // Ожидаем, что перемещенный объект равен "123"
}

TEST(FiveTest, AdditionOperator) {
    Five five1("12");
    Five five2("23");
    Five result = five1 + five2; // Складываем
    EXPECT_EQ(result, Five("40")); // Ожидаем, что результат равен "40" (в пятиричной системе)
}

TEST(FiveTest, SubtractionOperator) {
    Five five1("444");
    Five five2("41");
    Five result = five1 - five2;
    EXPECT_EQ(result, Five("403"));
}
TEST(FiveTest, ComparisonOperators) {
    Five five1("12");
    Five five2("23");
    EXPECT_TRUE(five1 < five2); // Ожидаем, что five1 меньше five2
    EXPECT_FALSE(five1 > five2); // Ожидаем, что five1 не больше five2
    EXPECT_TRUE(five1 != five2); // Ожидаем, что они не равны
    EXPECT_FALSE(five1 == five2); // Ожидаем, что они не равны
}
