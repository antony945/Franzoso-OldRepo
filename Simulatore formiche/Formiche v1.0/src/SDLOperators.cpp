#include "SDLclass.h"


Vettore& Vettore::operator+=(const Vettore& v) {
	x += v.x;
	y += v.y;
	return *this;
}

Vettore& Vettore::operator-=(const Vettore& v) {
	return *this += -v;
}

Vettore& Vettore::operator*=(long double scalar) {
	x = x*scalar;
	y = y*scalar;
	return *this;
}

Vettore& Vettore::operator/=(long double scalar) {
	x /= scalar;
	y /= scalar;
	return *this;
}

Vettore operator-(const Vettore& v) {
	return Vettore{ -v.x, -v.y };
}

Vettore operator+(const Vettore& a, const Vettore& b) {
	Vettore sum = a;
	sum += b;
	return sum;
}

Vettore operator-(const Vettore& a, const Vettore& b) {
	Vettore difference = a;
	difference -= b;
	return difference;
}

Vettore operator*(const Vettore& a, long double scalar) {
	Vettore product = a;
	product *= scalar;
	return product;
}

Vettore operator/(const Vettore& a, long double scalar) {
	Vettore quotient = a;
	quotient /= scalar;
	return quotient;
}

bool operator==(const Vettore& a, const Vettore& b) {
	return a.x == b.x && a.y == b.y;
}

bool operator!=(const Vettore& a, const Vettore& b) {
	return !(a == b);
}
