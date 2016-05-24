#ifndef h3_H	
#define h3_H


struct term
{
	int coeff=0;
	int exp=0;
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
	int num=0;
	term* head=nullptr;

public:
	polynomial() = default;
	polynomial(const int );
	polynomial(const polynomial& );

	polynomial& operator=(const polynomial& );

	void setNum(int N){ num = N; }
	int getNum() const { return num; }
	term* getHead() const{ return head; }
	polynomial operator+(const polynomial& ) const;
	polynomial operator*(const polynomial& ) const;
	int insert(const term&);

	void print();

	~polynomial();
};

#endif




