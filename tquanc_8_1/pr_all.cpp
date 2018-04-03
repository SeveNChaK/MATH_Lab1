// ��������� ������������ �������������� ��� ������ QUANC8
// Microsoft Visual Studio 2005
// �����:

# include <stdio.h>
# include "quanc8.h"
# include <math.h>

// ������� ( ��� Quanc8 )
double B ( double s )
{   
	//return (exp(s-1)*pow(s,9.0));}
	//return exp(1.0*s)*sin(s);} ;
   //return 1/(pow((s-0.1),4.0)+0.000001);
   //return (tan(s))/s;
	return exp(s/2)-sin(s*3.14);
}

void main( void ){

	double ax, bx,			// ������� � ������ ������� ��������������
		abserr,				// ���������� �����������
		relerr,				// ������������� �����������
		result,				// ������������ �������� ���������
		errest,				// ������ �������� �������������� ������
		flag;				// ��������� ����������
	int nofun;			    // ����� �������� �������, �������������� ��� ���������� ���������    
	bx = 2.000000;
	ax = 0.0001;
	relerr =0.0;	
    abserr =1.0e-13;	

	quanc8( B, ax, bx, abserr, relerr, &result, &errest, &nofun, &flag );		
	// ����� �� ����� �������
    printf(" result   \n");
    printf("\result=%lf   flag=%lf errest=%lf ",result,flag,errest);
    printf("\nofun=%lf ",nofun);
	/*cout << endl << " TASK: " << endl; 
	cout << "\td^2y/dx^2=y^2-1" << endl;
	cout << "\ty(0)=0; y(1)=1" << endl;
	cout << "\t0<=x<=1" << endl;
	cout << "\ty'(0)=[1.2, " << result <<"]" << endl;*/
	getchar();

}




