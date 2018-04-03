//Пример: считаем  в точках 0.1+0.2*к при пом. QUANC8,затем при пом.п. Лагранжа
#include <stdio.h>
#include "quanc8.h"
#include "lagrange.h"
#include <math.h>
#include <iostream>

double x=0;
double t;

// Функция (для Quanc8)
double Function (double t)
{
	return exp(x*t)/(1+x);
}

using namespace std;
void main( void )
{
	double a=0, b=1, abserr=1.0e-12, relerr=0, errest, flag;
	int nofun;

	// считаем в точках 0.1+0.2*к при пом. QUANC8
	x=0.1;
	double Results1[11];
	for (int i=0; i<11; i++)
	{
		quanc8(Function, a, b, abserr, relerr, &Results1[i], &errest, &nofun, &flag);	
		x+=0.2;
	}
	x=0;

	// вычисл.Х[i],Y[i] для полинома Лагранжа
	double lagrangeX[11], lagrangeY[11];
	double Results2[30];	
	double j=0;
	
	for (int i=0; i<=10; i++)
	{
		lagrangeX[i]=j;
		j+=0.2;
	}
	for (int i=0; i<=10; i++)
	{
		quanc8(Function, a, b, abserr, relerr, &lagrangeY[i], &errest, &nofun, &flag);
		x+=0.2;
	}
	//считаем в точках 0.1+0.2*к при пом.п. Лагранжа
	double tr=0.1;
	for (int i=0; i<11; i++)
	{
		Results2[i]=lagrange(10, lagrangeX, lagrangeY, tr);
		tr+=0.2;
	}
//вывод 
	cout<<"      QUANC8    Lagrange    Spline"<<endl;
	double n=0.1;
	for (int i=0; i<=10; i++)
	{
		cout<<n<<"  "<<Results1[i]<<"  "<<Results2[i]<<"  "<<Results2[i]<<endl;;
		n += 0.2;
	}
}
