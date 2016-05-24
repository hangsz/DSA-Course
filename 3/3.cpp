#include "3.h"
#include <iostream>

using namespace std;

polynomial::polynomial(const int N) :num(0)
{
	head = new term[N];
}

polynomial::polynomial(const polynomial& poly) 
{
	num = poly.getNum();
	head = new term[num];
	term* polyHead = poly.getHead();
	for (int i = 0; i < num; ++i)
		head[i] = polyHead[i];
}

polynomial& polynomial::operator=(const polynomial& poly)
{
	if (this == &poly) return *this;

	delete[] head;
	num = poly.getNum();
	head = new term[num];
	term* polyHead = poly.getHead();
	for (int i = 0; i < num; ++i)
		head[i] = polyHead[i];

	return *this;
}

polynomial::~polynomial()
{
	delete[] head;
}


polynomial polynomial::operator+(const polynomial& poly2)  const
{
	int tempN = poly2.getNum();
	term* head2 = poly2.getHead();
	polynomial tempPoly = polynomial(tempN+num);
	term* head3 = tempPoly.getHead();

	int n = 0;
	int i=0,j = 0;
	while (i != num && j != tempN) {
		if (head[i].exp > head2[j].exp){
			head3[n] = head[i++];
			tempPoly.setNum(++n);
		}
		else if (head[i].exp < head2[j].exp){
			head3[n] = head2[j++];
			tempPoly.setNum(++n);
		}
		else{
			head3[n] = term(head[i].coeff + head2[j].coeff, head[i].exp);
			tempPoly.setNum( ++n);
			++i, ++j;
		}
	}

	if (i == num){
		while (j != tempN)
		{
			head3[n] = head2[j++];
			tempPoly.setNum(++n);
		}
	}else{
		while (i != num)
		{
			head3[n] = head[i++];
			tempPoly.setNum( ++n);
		}

	}

	return tempPoly;
}

polynomial polynomial::operator*(const polynomial& poly2)  const
{

	//cout << "*" << endl;
	int tempN = poly2.getNum();
	term* head2 = poly2.getHead();
	polynomial tempPoly(num*tempN);
	term  temp;

	int n = 0;
	for (int i = 0; i < num; ++i){
		for (int j = 0; j<tempN; ++j){
				temp.coeff = head[i].coeff*head2[j].coeff;
				temp.exp = head[i].exp+head2[j].exp;
				if (tempPoly.insert(temp) == 1)
				{
					tempPoly.setNum(++n);
					//cout << "num" << tempPoly.getNum() << endl;
				}
			}	
	}
	return tempPoly;

}


int polynomial::insert(const term& temp)
{

	//cout << "insert" << endl;
	//cout << temp.coeff << '\t' << temp.exp << endl;
	if (num == 0)
	{
		head[0] = temp;
		//cout << "1"<<endl;
		return 1;
	}
	int i;
	for ( i = 0; i < num; ++i)
	{
		if (head[i].exp <= temp.exp)
		{
			if (head[i].exp == temp.exp)
			{
				head[i].coeff += temp.coeff;
				//cout << "0" << endl;
				return 0;
			}
			else
			{
				for (int j = num - 1; j >= i; --j)
					head[j + 1] = head[j];
				head[i] = temp;
				//cout << "1" << endl;
				return 1;
			}
		}
	}

	if (i == num)
	{
		head[i] = temp;
		//cout << "1" << endl;
		return 1;
	}

}


void polynomial::print()
{
	//cout << "print"<<endl;
	int i;
	for (i = 0; i < num; ++i)
	{
		if (head[i].coeff != 0) break;
	}
	if (i == num)
	{
		cout << "0 0";
		return;
	}
	 
	//int numTemp = num;
	//for (i = 0; i < num; ++i){
	//	if (head[i].coeff == 0)
	//		numTemp--;
	//}

	//cout << numTemp<<endl;
	for ( i = 0; i < num; ++i)
	{
		if (head[i].coeff != 0)
			cout <<' '<< head[i].coeff << ' ' << head[i].exp;
	}
	cout << endl;
}

