#include <iostream>
#include "Prog1.h"

namespace Prog1 {
    // функция ввода
    Matrix input() {

        Matrix matrix;

        try {
            // ввод количество строк
            std::cout << "Enter number of lines: --> ";
            matrix.m = getNum<int>(1);

            // ввод количество столбцов
            std::cout << "Enter number of columns: --> ";
            matrix.n = getNum<int>(1);

            matrix.row = new int[matrix.m+1];
            matrix.columns = new int[0];
            matrix.values = new int[0];

            int nz{0}; // количество ненулевых элементов
            matrix.nz = 0;

            matrix.row[0] = 0;


            for(int i = 0; i < matrix.m; i++) {

                // ввод элементов строки матрицы
                std::cout << "Enter items for matrix line #" << (i + 1) << ":" << std::endl;
                for(int j = 0; j < matrix.n; j++) {
                    int a = getNum<int>();

                    if (a != 0) {
                        matrix.columns = resize(matrix.columns, nz + 1);
                        matrix.columns[nz] = j;
                        matrix.values = resize(matrix.values, nz + 1);
                        matrix.values[nz] = a;
                        nz++;

                    }
                }

                matrix.row[i+1] = nz;

            }
            matrix.nz = nz;
        }
        catch(...) // в случае любого исключения
        {
            erase(matrix); // очищаем уже выделенную память
            throw; // перекидываем то же исключение дальше
        }
        return matrix;
    }

    int* resize(int *m, int x) {
        int* tmp = new int[x];
        std::copy(m, m+x-1, tmp);
        delete[] m;
        m = tmp;
        return m;
    }

    // функция вывода
    void output_m(const char *msg, const Matrix &matrix) {

        std::cout << msg << ":\n";

        int b{0};
        for(int i = 0; i < matrix.m; ++i) {
            for(int j = 0; j < matrix.n; ++j) {
                if (b < matrix.row[i+1]) {
                    if (matrix.columns[b] != j) {
                        std::cout << "0 ";
                    }
                    else {
                        std::cout << matrix.values[b] << " ";
                        b++;
                    }
                }
                else {
                    std::cout << "0 ";
                }
            }

            std::cout << std::endl;
        }
    }

    void output_v(const char *msg, double* res, int m) {
        std::cout << msg << ":\n";
        for(int i = 0; i < m; i++) {
            std::cout << res[i] << " ";
        }
        std::cout << std::endl;
    }

    double* vector(Matrix &matrix) {

        double* r = new double[matrix.m]; // вектор, в который будет записан результат

        int k{0};
        double C1{0};
        double C{0};
        double minC{0};
        double maxC{0};

        // нахождение C1
        for(int i = 0; i < matrix.row[1]; i++) {
            C1 += matrix.values[i];
        }

        minC = C1;
        maxC = C1;

        r[0] = C1;

        k = matrix.row[1];
        // нахождение minC и maxС
        for(int i = 2; i <= matrix.m; i++) {
            for(int j = 0 + k; j < matrix.row[i] - matrix.row[i-1] + k; j++) {
                C += matrix.values[j];
            }
            r[i-1] = C;
            if (minC > C) {
                minC = C;
            }
            if (maxC < C) {
                maxC = C;
            }
            C = 0;
            k += matrix.row[i] - matrix.row[i-1];
        }

        if (maxC == minC) throw std::runtime_error("Division by zero"); // 0 в знаменателе

        double* res = new double[matrix.m];

        for(int i = 0; i < matrix.m; i++) {

            res[i] = (r[i] - minC)/(maxC - minC);
        }

        delete[] r;

        return res;

    }

    // функция освобождения занятой памяти
    void erase(Matrix &matrix) {
        delete[] matrix.row;
        delete[] matrix.columns;
        delete[] matrix.values;
        matrix.row = nullptr;
        matrix.columns = nullptr;
        matrix.values = nullptr;

        matrix.m = 0;
        matrix.n = 0;
        matrix.nz = 0;
    }


}