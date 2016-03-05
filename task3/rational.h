#ifndef _RATIONAL_H
#define _RATIONAL_H

typedef long long lld;


class rational {
	private:
	int q, v;     // r = q / v ;   v = 0 => +-inf ;   v < 0 => invalid
	static int gcd(int a, int b);
	static int lcm(int a, int b);
	static int sign(int a);
	static rational unsafeCreate(int q, int v);

	public:
	rational(int i);
	rational(int q, int v);
	rational();
	rational rollV() const;
	void roll();
	rational operator-(void) const;
	rational operator* (const rational &r) const;
//	rational rational::operator* (const rational &r) const {
	rational operator/ (const rational &r) const;
	rational operator+ (const rational &r) const;
//	rational rational::operator+ (const rational &r) const {
	rational operator- (const rational &r) const;
	void operator+= (const rational &r);
	void operator-= (const rational &r);
	void operator*= (const rational &r);
	void operator/= (const rational &r);
	double getValue() const;
	bool operator> (const rational &r) const;
	int getNum() const;
	int getDenom() const;
};

#endif
