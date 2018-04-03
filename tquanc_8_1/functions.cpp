// functions.cpp

# include "functions.h"
# include "rkf45.h"
# include <math.h>
# include <iostream>
// C������ ��� ������� ������� ( ��� RKF45 )
void MyFunc ( float t, float *y, float *dy )
{
	dy[0]=y[1];
	dy[1]=pow(y[0],2)-1;

	return;
}
using namespace std;
// ���������� ���������( ��� Zeroin )
double f ( double x )
{
	double y;
	int Neqn = 2;			// ����� ������������� ���������
	int iwork[ 30 ];		// ������� ������
	float work[ 15 ];		// ������� ������
	float Y0[ ] = { 0, x };	// ������� � ����� �0=0
	float T0 = 0;			// ��������� �������� ����������� ����������
	float RE = 1E-6;		// ������� ������������� �����������
	float AE = 0;			// ������� ���������� �����������
	int iflag = 1;			// ��������� ������ ��������������
	float tout = 1;			// ����� ������ �� ����������� ����������
    
	// ������� ������ ����
	cout << "\t" << Y0[1];

	RKF45( MyFunc, Neqn, Y0, &T0, &tout, &RE, &AE, &iflag, work, iwork );
	
	cout.width(8);
	cout << "\t" << Y0[0];
	cout.width(8);
	cout << "\t" << Y0[1];
	cout.width(8);
	cout << "\t" << iflag << endl;


	// y=0 ��� ���������� �������� ������� Y0[0]=1
	y=Y0[0]-1;

	return y;
}

// ������� ( ��� Quanc8 )
double B ( double s )
{
	return sqrt( 3 - s ) * cos( s ) ;
}