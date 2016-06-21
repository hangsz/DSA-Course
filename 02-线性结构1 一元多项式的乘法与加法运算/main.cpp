#include <iostream>

using namespace std;

struct term
{
	int coeff = 0;
	int exp = 0;
	term() = default;
	term(int Coeff, int Exp) :coeff(Coeff), exp(Exp){}
	term(const term& Term) :coeff(Term.coeff), exp(Term.exp){}
	term& operator=(const term& Term)
	{
		coeff = Term.coeff;
		exp = Term.exp;
		return *this;
	}
};

class polynomial
{
private:
	int num = 0;
	term* head = nullptr;

public:
	polynomial() = default;
	polynomial(const int);
	polynomial(const polynomial&);

	polynomial& operator=(const polynomial&);

	void setNum(int N){ num = N; }
	int getNum() const { return num; }
	term* getHead() const{ return head; }
	polynomial operator+(const polynomial&) const;
	polynomial operator*(const polynomial&) const;
	int insert(const term&);

	void print();

	~polynomial();
};


polynomial::polynomial(const int N)
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
	polynomial tempPoly = polynomial(tempN + num);
	term* head3 = tempPoly.getHead();

	int n = 0;
	int i = 0, j = 0;
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
			tempPoly.setNum(++n);
			++i, ++j;
		}
	}

	if (i == num){
		while (j != tempN)
		{
			head3[n] = head2[j++];
			tempPoly.setNum(++n);
		}
	}
	else{
		while (i != num)
		{
			head3[n] = head[i++];
			tempPoly.setNum(++n);
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
		for (int j = 0; j < tempN; ++j){
			temp.coeff = head[i].coeff*head2[j].coeff;
			temp.exp = head[i].exp + head2[j].exp;
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
	for (i = 0; i < num; ++i)
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
	for (i = 0; i < num; ++i)
	{
		if (head[i].coeff != 0)
		{
			cout << head[i].coeff << ' ' << head[i].exp;
			break;
		}
	}
	for (i++; i < num; ++i)
	{
		if (head[i].coeff != 0)
			cout << ' ' << head[i].coeff << ' ' << head[i].exp;

	}

}




int main()
{
	int n1, n2;

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

	polynomial poly3;


	poly3 = poly1 * poly2;
	poly3.print();

	cout << endl;

	poly3 = poly1 + poly2;
	poly3.print();
}