#include "Fraction.h"

// for integers
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
		// if the negative sign is in the denominator
		if (denom < 0)
			set_signs();
		
		simplify();

	set_print();
}

// greatest common denominator (recursive algorithm)
int Fraction::GCD(int a, int b)
{
	if (b == 0)
		return abs(a);
	return GCD(b, a%b);
}

// sets the printable string that represents the fraction
void Fraction::set_print()
{
	if (num == 0 && denom != 1)
	{
		denom = 1;
		print = "0";
	} else 
	{
		print = std::to_string(num);
		
		if (denom != 1)
			print += "/" + std::to_string(denom);	
	}
}

// handles signs in the denominator
void Fraction::set_signs()
{
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

// simplifies fractions
void Fraction::simplify()
{
	int gcd = GCD(num, denom);

	if (gcd != 1) 
	{
		this->num = int(num / float(gcd));
		this->denom = int(denom / float(gcd));
	}

	// case when denominator is negative
	if (denom < 0)
	{
		num *= -1;
		denom *= -1;
	}	

	set_print();
}

// multiples "this" fraction by the value of "that" fraction
void Fraction::multiply(Fraction that)
{
	this->num *= that.num;
	this->denom *= that.denom;
	
	simplify();
	set_print();
}

// divides "this" fraction by the value of "that" fraction
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

// adds the value of "that" fraction to "this" fraction
void Fraction::add(Fraction that)
{
	if (this->denom == 1 && that.denom == 1)
	{
		this->num += that.num;
	} else if (this-> num == 0)
	{
		this->num = that.num;
		this->denom = that.denom;
	} else
	{
		this->num *= that.denom;
		that.num *= this->denom;
		this->num += that.num;
		this->denom *= that.denom;

	}

	simplify();
	set_print();
}

// subtracts the value of "that" fraction from "this" fraction
void Fraction::subtract(Fraction that)
{
	if (this->denom == 1 && that.denom == 1)
	{
		this->num -= that.num;

	} else if (this-> num == 0)
	{
		this->num = -1 * that.num;
		this->denom = that.denom;

	} else
	{
		this->num *= that.denom;
		that.num *= this->denom;
		this->num -= that.num;

		this->denom *= that.denom;

	}

	simplify();
	set_print();


}

// multiplies the value of "this" fraction by the value of "that" fraction, and returns the product
// as a new fraction (so that the value of "this" fraction remains unchanged)
Fraction Fraction::multiply_val(Fraction that)
{
	int new_num = this->num;
	int new_denom = this->denom;

	new_num *= that.num;
	new_denom *= that.denom;

	Fraction new_fraction(new_num, new_denom);

	return new_fraction;
	
}

void Fraction::multiply_by_val(int val)
{
	this->num *= val;

	simplify();
	set_print();
}

