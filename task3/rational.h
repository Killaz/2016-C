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
	rational operator-() const;
	rational operator* (rational r) const;
	rational operator/ (rational r) const;
	rational operator+ (rational r) const;
	rational operator- (rational r) const;
	void operator+= (rational r);
	void operator-= (rational r);
	void operator*= (rational r);
	void operator/= (rational r);
	double getValue() const;
	bool operator> (rational r) const;
	int getNum() const;
	int getDenom() const;
};

#endif
