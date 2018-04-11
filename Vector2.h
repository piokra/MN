#pragma once


class Vector2
{
public:
	Vector2(float x, float y) : x(x), y(y) {
	}
	Vector2();
	~Vector2();

	Vector2 operator*(float alpha) const {
		return Vector2(alpha*x, alpha*y);
	};

	Vector2 operator+(const Vector2& other) const {
		return Vector2(x + other.x, y + other.y);
	};

	Vector2 operator-(const Vector2& other) const {
		return other*(-1) + *this;
	};



	float x, y;
};

inline Vector2 operator* (float alpha, const Vector2& other) {
	return other * alpha;
}
