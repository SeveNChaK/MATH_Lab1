// functions.cpp

# include "functions.h"
# include "rkf45.h"
# include <math.h>
# include <iostream>
// Cистема —ƒ” первого пор€дка ( дл€ RKF45 )
void MyFunc ( float t, float *y, float *dy )
{
	dy[0]=y[1];
	dy[1]=pow(y[0],2)-1;

	return;
}
using namespace std;
// Ќелинейное уравнение( дл€ Zeroin )
double f ( double x )
{
	double y;
	int Neqn = 2;			// число интегрируемых уравнений
	int iwork[ 30 ];		// рабочий массив
	float work[ 15 ];		// рабочий массив
	float Y0[ ] = { 0, x };	// решение в точке “0=0
	float T0 = 0;			// начальное значение независимой переменной
	float RE = 1E-6;		// граница относительной погрешности
	float AE = 0;			// граница абсолютной погрешности
	int iflag = 1;			// указатель режима интегрировани€
	float tout = 1;			// точка выхода по независимой переменной
    
	// –ешение задачи  оши
	cout << "\t" << Y0[1];

	RKF45( MyFunc, Neqn, Y0, &T0, &tout, &RE, &AE, &iflag, work, iwork );
	
	cout.width(8);
	cout << "\t" << Y0[0];
	cout.width(8);
	cout << "\t" << Y0[1];
	cout.width(8);
	cout << "\t" << iflag << endl;


	// y=0 при выполнении краевого услови€ Y0[0]=1
	y=Y0[0]-1;

	return y;
}

// ‘ункци€ ( дл€ Quanc8 )
double B ( double s )
{
	return sqrt( 3 - s ) * cos( s ) ;
}