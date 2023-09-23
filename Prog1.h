#ifndef OOPPROG1_PROG1_H
#define OOPPROG1_PROG1_H

#include <iostream>
#include <string>
#include <limits>
#include <cstring>

namespace Prog1 {
    // структура для задания матрицы
    struct Matrix {
        int m = 0; // количество строк
        int n = 0; // количество столбцов
        int nz = 0; // количество ненулевых элементов
        int *row = nullptr; // массив индексации строк
        int *columns = nullptr; // массив индексов столбцов
        int *values = nullptr; // массив значений
    };

    // шаблонная функция ввода одного числа
    template<class T>
    T getNum(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max()) {
        T a;
        while(true) {
            std::cin >> a;
            if(std::cin.eof()) // обнаружен конец файла
                throw std::runtime_error("Failed to read number: EOF");
            else if(std::cin.bad()) // обнаружена невосстановимая ошибка входного потока
                throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
            else if(std::cin.fail()) { // прочие ошибки (неправильный формат ввода)
                std::cin.clear(); // очищаем флаги состояния потока
                // игнорируем все символы до конца строки
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "You are wrong; repeat please!" << std::endl;
            }
            else if(a >= min && a <= max) // если число входит в заданный диапазон
                return a;
        }

    }

    // прототипы функций
    Matrix input(); // ввод матрицы
    int* resize(int *m, int x); // изменение размера массива
    void output_m(const char *msg, const Matrix &matrix); // вывод матрицы
    void output_v(const char *msg, double* res, int m); // вывод вектора
    double* vector(Matrix &matrix); // нахождение необходимого вектора (инд задание)
    void erase(Matrix &matrix); // освобождение занятой памяти
}

#endif