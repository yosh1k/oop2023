#include <iostream>
#include "Prog1.h"

using namespace Prog1;

// основная функция
int main() {
    Matrix matrix; // исходная матрица
    double* res = nullptr; // полученный результат
    try {
        matrix = input(); // ввод матрицы
        res = new double[matrix.m];
        res = vector(matrix); // вычисление требуемого результата
        output_m("Sourced matrix", matrix); // вывод матрицы
        output_v("Received vector", res, matrix.m);
        erase(matrix); // освобождение памяти
        delete[] res;
        res = nullptr;
    }
    catch(const std::bad_alloc &ba) { // в случае ошибок выделения памяти
        std::cerr << "Not enough memory" << std::endl;
        delete[] res;
        res = nullptr;
        erase(matrix);
        return 1;
    }
    catch(const std::exception &e) { // в случае прочих исключений
        std::cerr << e.what() << std::endl;
        delete[] res;
        res = nullptr;
        erase(matrix);
        return 1;
    }
    return 0;
}