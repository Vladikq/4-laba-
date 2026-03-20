#include <iostream> 
#include <math.h> 
#include <iomanip> 

using namespace std;

// Метод Ньютона

// функция уравнения
double f(double x) {
    return 2*x + tan(x); // исходное уравнение
}

// производная функции
double fsh(double x) {
    return 2 + 1/(cos(x)*cos(x)); // производная 2x + tg(x)
}

// реализация метода Ньютона
double newton(double x0, double eps) {
    double x1 = x0 - f(x0) / fsh(x0); // вычисление следующего приближения
    int iternum = 1; // номер итерации

    while (fabs(x1 - x0) > eps) { // пока разница больше заданной точности
        cout << iternum << setw(15) << x0 << setw(15) << x1 << setw(15) << x1 - x0 << endl;
        x0 = x1; // обновляем текущее значение
        x1 = x0 - f(x0) / fsh(x0); // новое приближение
        iternum++; // увеличиваем номер итерации
    }

    return x0; // найденный корень
}


// Метод простых итераций

// итерационная функция
double phi(double x) {
    return x - f(x) / fsh(x);
}

// реализация метода простых итераций
double SimpleIterations(double x0, double eps) {
    double x1 = phi(x0); // первое приближение
    int iternum = 1;

    while (fabs(x1 - x0) > eps) { // условие остановки
        cout << iternum << setw(15) << x0 << setw(15) << x1 << setw(15) << x1 - x0 << endl;
        x0 = x1;
        x1 = phi(x0);
        iternum++;
    }

    return x0;
}


// Метод половинного деления (бисекции)
double bisection(double a, double b, double eps) {

    double c = 0.0; // середина интервала
    int iternum = 1;

    while (fabs(b - a) > eps) { // пока длина интервала больше точности

        cout << iternum << setw(15) << a << setw(15) << b << setw(15) << b - a << endl;

        c = (a + b) / 2; // середина интервала

        if (f(c) == 0.0) { // если найден точный корень
            break;
        } 
        else if (f(c) * f(a) < 0){ // корень находится в левой части
            b = c;
        } 
        else { // корень находится в правой части
            a = c;
        }

        iternum++;
    }

    return c; // приближенное значение корня
}


int main() {

    setlocale(LC_ALL, "Rus"); // русская локализация
    srand(time(0));

    // Метод Ньютона
    cout << "Метод Ньютона:" << endl 
         << "N" << setw(15) << "xn" << setw(15) << "xn+1" << setw(15) << "xn+1 - xn" << endl;

    double x0 = 1.5; // начальное приближение
    double eps = 0.0001; // требуемая точность

    double x = newton(x0, eps); // вызов метода Ньютона

    cout << "Корень: " << x << endl << endl;


    // Метод простых итераций
    cout << "Метод простых итераций:" << endl 
         << "N" << setw(15) << "xn" << setw(15) << "xn+1" << setw(15) << "xn+1 - xn" << endl;

    x0 = 1.5;
    eps = 0.0001;

    x = SimpleIterations(x0, eps); // поиск корня

    cout << "Корень: " << x << endl << endl;


    // Метод половинного деления
    cout << "Метод половинного деления:" << endl 
         << "N" << setw(15) << "an" << setw(15) << "bn" << setw(15) << "bn - an" << endl;

    double a = -10.0; // левая граница интервала
    double b = 5.0; // правая граница интервала

    eps = 0.0001;

    x = bisection(a, b, eps); // поиск корня методом бисекции

    cout << "Корень: " << x << endl << endl;

    return 0; 
}
