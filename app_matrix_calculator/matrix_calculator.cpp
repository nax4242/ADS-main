// Copyright 2026 Danila Puzanov

#include <windows.h>
#include <iostream>
#include <stdexcept>
#include "../lib_matrix/triangle_matrix.h"

size_t read_size(const char* prompt) {
    size_t v;

    std::cout << prompt;
    if (!(std::cin >> v) || v <= 0) {
        throw std::invalid_argument("Нужно положительное целое число");
    }

    return v;
}

double read_number(const char* prompt) {
    double v;

    std::cout << prompt;
    if (!(std::cin >> v)) {
        throw std::invalid_argument("Нужно число");
    }

    return v;
}

Matrix<double>*& select(Matrix<double>*& a, Matrix<double>*& b,
    const char* prompt) {
    std::cout << prompt << " (A/B): ";

    char c;

    std::cin >> c;

    if (c == 'A' || c == 'a') return a;
    if (c == 'B' || c == 'b') return b;

    throw std::invalid_argument("Нужно ввести A или B");
}

void input_full(Matrix<double>*& target) {
    size_t r = read_size("Строк: ");
    size_t c = read_size("Столбцов: ");
    Matrix<double>* m = new Matrix<double>(r, c);

    std::cout << "Введите " << r * c << " элементов:\n";

    try {
        if (!(std::cin >> *m)) {
            throw std::invalid_argument("Ошибка ввода элементов");
        }
    } catch (...) {
        delete m;
        throw;
    }

    delete target;
    target = m;
}

void input_triangle(Matrix<double>*& target) {
    size_t n = read_size("Размер n: ");
    TriangleMatrix<double>* t = new TriangleMatrix<double>(n);

    std::cout << "Введите полную матрицу " << n << "x" << n
        << " (под диагональю только нули, " << n * n
        << " элементов):\n";

    try {
        if (!(std::cin >> *t)) {
            throw std::invalid_argument("Ошибка ввода элементов");
        }
    } catch (...) {
        delete t;
        throw;
    }

    delete target;
    target = t;
}

void print_menu() {
    std::cout << "\n=== Матричный калькулятор ===\n"
        << "1. Ввести матрицу (обычную)\n"
        << "2. Ввести верхнетреугольную матрицу\n"
        << "3. Показать A и B\n"
        << "4. A + B\n"
        << "5. A - B\n"
        << "6. A * B\n"
        << "7. Умножить матрицу на число\n"
        << "8. Транспонировать матрицу\n"
        << "0. Выход\n"
        << "Выбор: ";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Matrix<double>* A = new Matrix<double>();
    Matrix<double>* B = new Matrix<double>();

    while (true) {
        print_menu();

        int choice;
        if (!(std::cin >> choice)) {
            if (std::cin.eof()) break;
            std::cout << "Нужно ввести номер пункта.\n";
            continue;
        }
        if (choice == 0) break;

        try {
            switch (choice) {
            case 1:
                input_full(select(A, B, "Куда записать"));
                break;
            case 2:
                input_triangle(select(A, B, "Куда записать"));
                break;
            case 3:
                std::cout << "A =\n" << *A << "\nB =\n" << *B << '\n';
                break;
            case 4: {
                Matrix<double> r = *A + *B;
                std::cout << "A + B =\n" << r << '\n';
                break;
            }
            case 5: {
                Matrix<double> r = *A - *B;
                std::cout << "A - B =\n" << r << '\n';
                break;
            }
            case 6: {
                Matrix<double> r = *A * *B;
                std::cout << "A * B =\n" << r << '\n';
                break;
            }
            case 7: {
                Matrix<double>*& m = select(A, B, "Какую матрицу");
                double k = read_number("Число: ");
                Matrix<double> r = *m * k;
                std::cout << "Результат =\n" << r << '\n';
                break;
            }
            case 8: {
                Matrix<double>*& m = select(A, B, "Какую матрицу");
                std::cout << "Результат =\n" << m->transpose() << '\n';
                break;
            }
            default:
                std::cout << "Нет такого пункта.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Ошибка: " << e.what() << '\n';
        }
    }

    delete A;
    delete B;

    return 0;
}
