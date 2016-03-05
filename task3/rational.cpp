#include "rational.h"

//class rational {
	int rational::gcd(int a, int b) {
		int sgn = 1;
		if (a < 0)
			sgn = -1, a = -a;
		if (b < 0)
			sgn = -sgn, b = -b;
		while (a != 0 && b != 0)
			if (a > b)
				a %= b;
			else
				b %= a;
		return (a + b) * sgn;
	}
	int rational::lcm(int a, int b) {
		return (int) ((lld) a * b / gcd(a, b));
	}
	int rational::sign(int a) {
		return (a > 0) ? 1 : ((a == 0) ? 0 : -1);
	}
	rational rational::unsafeCreate(int q, int v) {
		rational ans;
		ans.q = q, ans.v = v;
		return ans;
	}
	rational::rational(int i) {
		this->q = i;
		this->v = 1;
	}
	rational::rational(int q, int v) {
		int gcdV = gcd(q, v);
		this->q = q / gcdV;
		if (v < 0) {
			this->v = -v / gcdV;
			this->q = -this->q;
		} else
			this->v = v / gcdV;
	}
	rational::rational() {
		this->q = this->v = 0;
	}
	rational rational::rollV() {
		return rational(this->v, this->q);
	}
	void rational::roll() {
		*this = this->rollV();
	}
	rational rational::operator-() const {
		return rational(-this->q, this->v);
	}
	rational rational::operator* (const rational &r) const {
		rational ans;
		if (this->v < 0 || r.v < 0)
			return unsafeCreate(1, -1);
		if ((this->v == 0 && r.q == 0) || (this->q == 0 && r.v == 0))
			return unsafeCreate(1, -1);
		if (this->v == 0 || r.v == 0)
			return unsafeCreate(sign(this->q) * sign(r.q), 0);
		int gcd1 = gcd(this->q, r.v), gcd2 = gcd(r.q, this->v);
		ans.q = (this->q / gcd1) * (r.q / gcd2);
		ans.v = (r.v / gcd1) * (this->v / gcd2);
		return ans;
	}
	rational rational::operator/ (const rational &r) const {
		return *this * r.rollV();
	}
	rational rational::operator+ (const rational &r) const {
		if (this->v < 0 || r.v < 0)
			return unsafeCreate(1, -1);
		if ((this->v == 0) ^ (r.v == 0))
			return unsafeCreate(sign((this->v == 0) ? this->q : r.q), 0);
		if (this->v == 0 && r.v == 0) {
			if (sign(this->v) == sign(r.v))
				return unsafeCreate(sign(this->v), 0);
			else
				return unsafeCreate(1, -1);
		}
		lld gcdV = gcd(this->v, r.v);
		lld q = (lld) this->q * r.v / gcdV + (lld) r.q * this->v / gcdV;
		lld v = (lld) this->v * r.v / gcdV;
		gcdV = gcd(q, v);
		return rational(q / gcdV, v / gcdV);
	}
	rational rational::operator- (const rational &r) const {
		r = -r;
		return *this + r;
	}
	void rational::operator+= (const rational &r) {
		*this = *this + r;
	}
	void rational::operator-= (const rational &r) {
		*this = *this - r;
	}
	void rational::operator*= (const rational &r) {
		*this = *this * r;
	}
	void rational::operator/= (const rational &r) {
		*this = *this / r;
	}
	double rational::getValue() const {
		return (double) this->q / this->v;
	}
	bool rational::operator> (const rational &r) const {
		return this->getValue() > r.getValue();
	}
	int rational::getNum() const {
		return this->q;
	}
	int rational::getDenom() const {
		return this->v;
	}
//};
