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
	rational rollV();
	void roll();
	rational operator-();
	rational operator* (rational r);
	rational operator/ (rational r);
	rational operator+ (rational r);
	rational operator- (rational r);
	void operator+= (rational r);
	void operator-= (rational r);
	void operator*= (rational r);
	void operator/= (rational r);
	double getValue() const;
	bool operator> (rational r);
	int getNum() const;
	int getDenom() const;
};

#endif
