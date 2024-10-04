cmake_minimum_required(VERSION 3.27.8)
project(lab2)

set(CMAKE_CXX_STANDARD 20)

# Создаем библиотеку lab2_solution
add_library(lab2_solution src/five.cpp)

# Основной исполняемый файл
add_executable(lab2_main main.cpp)
target_link_libraries(lab2_main lab2_solution)

# Подключаем Google Test с помощью FetchContent
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# Указываем путь к заголовкам Google Test
include_directories(${gtest_SOURCE_DIR}/include)

# Исполняемый файл для тестов
add_executable(lab2_tests test/five_test.cpp)
target_link_libraries(lab2_tests lab2_solution GTest::gtest_main)

# Подключаем Google Test
include(GoogleTest)
gtest_discover_tests(lab2_tests)

# Включаем тестирование
enable_testing()
