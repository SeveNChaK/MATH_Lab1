#include <stdio.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "Tlagrange_2/lagrange.cpp"
#include "tquanc_8_1/quanc8.cpp"
#include "tspline_3/SPLINES.CPP"

using namespace std;

//Заданная функция
double formula(double x) {
    return 1 - exp(-1 * x);
}


int main(int argc, char *argv[]) {
    //GENERAL FIELDS
//    int i; //counter
//    const int COEFF = 50; //coefficient to reserve space

    //FIELDS FOR INTERPOLATION TASK
    int SIZE = 10; //Степень полинома
    int AMOUNT = 11; //Количество узлов
//    const int WIDTH = 15; //width of output data

//    double x[SIZE] = { -1, -0.96, -0.86, -0.79, 0.22, 0.5, 0.93 }; //values of x
//    double f[SIZE] = { -1, -0.151, 0.894, 0.986, 0.895, 0.5, -0.306 }; //values f(x)

//    double etalon[AMOUNT]; //Эталонные зачения функции
    double xk[AMOUNT]; //Значения аргументов
    double f[AMOUNT]; //Значения функции
    double lagr[AMOUNT]; //Значения полинома Лагранжа
    double spl[AMOUNT]; //Значения сплайн-функции
    double splX[SIZE + 1]; //values of x in spline
    double splF[SIZE + 1]; //values f(x) in spline
    double b[AMOUNT], c[AMOUNT], d[AMOUNT]; //Значения сплайн коэффициентов
    double f_lagr[AMOUNT]; //Погрешность полинома Лагранжа
    double f_spl[AMOUNT]; //Погрешность сплайн-функции

//    //FIELDS FOR INTEGRATION TASK
//    const double INV_STEP = 0.00001; //step to investigate quanc8 abilities
//
//    double errest; //real error
//    double flag; //indicator of validness
//    int nofun; //amount of inner call of function
//
//    double q[AMOUNT]; //Значения интегралов
//    double expl; //exploration point
//    double leftValue, rightValue; //left and right values of integral


    //ВЫЧИСЛЕНИЯ ЗНАЧЕНИЙ
    //Подсчет аргументов функции и ее значений
    for (int i = 0; i < AMOUNT; i++) {
        xk[i] = 0.3 * i;
        f[i] = formula(xk[i]);
    }

    //evaluate splX and splF
    for (int i = 1; i <= AMOUNT; i++) {
        splF[i] = f[i-1];
        splX[i] = xk[i-1];
    }

    //Вычисление коэффициентов
    spline(AMOUNT, splX, splF, b, c, d);

    for (int i = 0; i < AMOUNT; i++) {
        //Подсчет значений полинома Лагранжа
        lagr[i] = lagrange(SIZE, xk, f, xk[i]);

        //Подсчет значений сплайн-функции
        spl[i] = seval(AMOUNT, &xk[i], xk, f, b, c, d);
    }


    //ВЫЧИСЛЕНИЯ ПОГРЕШНОСТЕЙ
    for (int i = 0; i < AMOUNT; i++) {
        //Погрешность полинома Лагранжа
        f_lagr[i] = f[i] - lagr[i];

        //Погрешность сплайн-функции
        f_spl[i] = f[i] - spl[i];
    }

    //ВЫЧИСЛЕНИЯ ЗНАЧЕНИЙ ИНТЕГРАЛОВ

    double A = 0, B = 3.0; //Нижний и верхний пределы интегрирования
    double ABSERR = 1.0e-6, RELERR = 1.0e-6; //Абсолютная и относительная погрешности
    double res, errest, flag = 0;
    int nofun;

    //ВЫВОД РЕЗУЛЬТАТОВ
    printf(" Xk \t    f(Xk) \t    L(Xk) \t    S(Xk) \n");
    for (int i = 0; i < AMOUNT; ++i) {
        quanc8(formula, A, B, ABSERR, RELERR, &res, &errest, &nofun, &flag);
        printf("%.2f\t%.10f\t%.10f\t%.10f\t%.10f\t%.10f\t%.10f\n", xk[i], f[i], lagr[i], spl[i], f_lagr[i], f_spl[i], res);
    }
    return 0;
}