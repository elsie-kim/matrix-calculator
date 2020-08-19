#include "Fraction.h"

Fraction::Fraction(int num)
{
	this->num = num;
	denom = 1;
	print = std::to_string(num);
}

Fraction::Fraction(int num, int denom) 
{
	this->num = num;
	if (num == 0)
		this->denom = 1;
	else
		this->denom = denom;
	std::cout << denom << std::endl;
		if (denom < 0)
			set_signs();
		
		simplify();

	set_print();
}

int Fraction::GCD(int a, int b)
{
	if (b == 0)
		return abs(a);
	return GCD(b, a%b);
}

void Fraction::set_print()
{
	print = std::to_string(num);
       
	if (denom != 1 && num != 0)
	{
		print +=  "/" + std::to_string(denom);
	}
}

void Fraction::set_signs()
{
	std::cout << "hi\n";
	if (num > 0)
	{
		num *= -1;
		denom = abs(denom);
	}
	else 
	{
		num *= -1;
		denom *= -1;
	}

	set_print();
}	

void Fraction::simplify()
{
	int gcd = GCD(num, denom);

	if (gcd != 1) 
	{
		this->num = int(num / float(gcd));
		this->denom = int(denom / float(gcd));
	}

	set_print();
}

void Fraction::multiply(Fraction that)
{
	this->num *= that.num;
	this->denom *= that.denom;
	
	simplify();
	set_print();
}

void Fraction::divide(Fraction that)
{
	if (that.denom != 0) 
	{
		this-> num *= that.denom;
		this->denom *= that.num;

		simplify();
		set_print();
	}
}

void Fraction::add(Fraction that)
{
	int gcd = GCD(this->denom, that.denom);
	
	this->num *= gcd;
	this->denom *= gcd;
	that.num *= gcd;
	that.denom *= gcd;

	this->num += that.num;
	this->denom += that.denom;

	simplify();
	set_print();
}

void Fraction::subtract(Fraction that)
{
	int gcd = GCD(this->denom, that.denom);
	
	this->num *= gcd;
	this->denom *= gcd;
	that.num *= gcd;
	that.denom *= gcd;

	this->num -= that.num;
	this->denom -= that.denom;

	simplify();
	set_print();

}

