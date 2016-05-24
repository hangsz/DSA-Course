#include <iostream>

#include "3.h"
using namespace std;



int main()
{
	int n1,n2;

	cin >> n1;
	polynomial poly1(n1);
	poly1.setNum(n1);
	term* polyHead = poly1.getHead();
	

	for (int i = 0; i < n1; ++i)
	{
		cin >> polyHead[i].coeff >> polyHead[i].exp;
		//cout << endl;
		//cout << polyHead[i].coeff << '\t' << polyHead[i].exp << endl;
	}

	//system("pause");

	

	cin >> n2;

	polynomial poly2(n2);
	poly2.setNum(n2);

	polyHead = poly2.getHead();

	for (int i = 0; i < n2; ++i)
	{
		cin >> polyHead[i].coeff >> polyHead[i].exp;
	//	cout << endl;
		//cout << polyHead[i].coeff << '\t' << polyHead[i].exp << endl;
	}

	//system("pause");

	//poly1.print();
	//poly2.print();

	//system("pause");




	polynomial poly3 ;


	poly3 = poly1 * poly2;
	poly3.print();

	cout << endl;

    poly3 = poly1 + poly2;
	poly3.print();
}