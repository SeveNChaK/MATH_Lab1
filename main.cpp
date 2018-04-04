#include <stdio.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "tquanc_8_1/quanc8.cpp"
#include "tspline_3/SPLINES.CPP"

using namespace std;

//ЗАДАНАЯ ФУНКЦИЯ
double formula(double x) {
    return 1 - exp(-1 * x);
}

//ПОЛИНОМ ЛАГРАНЖА
double largange(double x, int current) {
    double lagr = 1;
    for (int i = 0; i < 11; i++) {
        if (current != i)
            lagr *= x - 0.3 * i;
    }
    return lagr;
}

double lagrangeInPoint(double x) {
    double Q = 0;
    for (int i = 0; i < 11; i++) {
        Q += largange(x, i) / largange(0.3 * i, i) * formula(0.3 * i);
    }
    return Q;
}

//СПЛАЙН-ФУНКЦИЯ В ТОЧКЕ
double splineInPoint(double n) {
    //построение сплайна
    double x[12], y[12], b[12], c[12], d[12];
    for (int i = 0; i < 11; i++) {
        x[i + 1] = 0.3 * i;
        y[i + 1] = formula(0.3 * i);
    }
    spline(11, x, y, b, c, d);

    return seval(11, &n, x, y, b, c, d);
}


int main(int argc, char *argv[]) {

    int AMOUNT = 11; //Количество узлов
    double xk[AMOUNT]; //Значения аргументов
    double f[AMOUNT]; //Значения функции
    double lagr[AMOUNT]; //Значения полинома Лагранжа
    double spl[AMOUNT]; //Значения сплайн-функции


    //ВЫЧИСЛЕНИЯ ЗНАЧЕНИЙ
    for (int i = 0; i < AMOUNT; i++) {

        //Подсчет аргументов функции и ее значений
        xk[i] = 0.3 * i;
        f[i] = formula(xk[i]);

        //Подсчет значений полинома Лагранжа
        lagr[i] = lagrangeInPoint(xk[i]);

        //Подсчет значений сплайн-функции
        spl[i] = splineInPoint(xk[i]);
    }

    //ВЫЧИСЛЕНИЯ ЗНАЧЕНИЙ ИНТЕГРАЛОВ
    double A = 0, B = 3.0; //Нижний и верхний пределы интегрирования
    double ABSERR = 1.0e-6, RELERR = 1.0e-6; //Абсолютная и относительная погрешности
    double errest, flag = 0;
    int nofun;
    double resF, resL, resS;

    quanc8(formula, A, B, ABSERR, RELERR, &resF, &errest, &nofun, &flag);
    quanc8(lagrangeInPoint, A, B, ABSERR, RELERR, &resL, &errest, &nofun, &flag);
    quanc8(splineInPoint, A, B, ABSERR, RELERR, &resS, &errest, &nofun, &flag);

    //РАСЧЕТ ПОГРЕШНОСТИ ВЫЧИСЛЕННЫХ ИНТЕГРАЛОВ
    double errL = abs(resF - resL);
    double errS = abs(resF - resS);

    //ВЫВОД РЕЗУЛЬТАТОВ
    printf(" Xk \t    f(Xk) \t    L(Xk) \t    S(Xk) \n");
    for (int i = 0; i < AMOUNT; ++i) {
        printf("%.2f\t%.10f\t%.10f\t%.10f\n", xk[i], f[i], lagr[i], spl[i]);
    }
    printf("F = %.15f\n", resF);
    printf("L = %.15f  err = %.15f\n", resL, errL);
    printf("S = %.15f  err = %.15f", resS, errS);

    return 0;
}