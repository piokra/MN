#include "Vector2.h"
#include <cmath>
#include <iostream>
float h = 0.1;

float f(float x, Vector2 y) {
	return -std::sin(y.x) - 0.5*y.y+0.9*std::cos(0.45*x);
}

Vector2 F(float x, const Vector2& y) {
	return Vector2(y.y, f(x,y));
}

Vector2 rkStep(float x, Vector2 y) {
	Vector2 f0 = F(x, y);
	Vector2 f1 = F(x + h / 2, y + h / 2 * f0);
	Vector2 f2 = F(x + h / 2, y + h / 2 * f1);
	Vector2 f3 = F(x + h, y + h*f2);
	return y + h / 6 * (f0 + 2*f1 + 2*f2 + f3);
}

int main() {
	float x = 0;
	Vector2 y{1.4f, 0};
	while (x <= 25) {
		std::cout << x << " " << y.x << " " << y.y << std::endl;
		y = rkStep(x, y);
		x += h;
	}
	Vector2 a;
}