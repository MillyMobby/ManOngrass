#pragma once
#include <ostream>
#include <cmath>
typedef float vtype;

class Vec2f
{
public:

	vtype x, y;

	Vec2f();
	Vec2f(vtype a, vtype b);
	~Vec2f();

	Vec2f operator+(Vec2f& other);
	Vec2f operator+(vtype other);
	Vec2f operator+=(Vec2f& other);
	Vec2f operator+=(vtype other);


	Vec2f operator-(Vec2f& other);
	Vec2f operator-(vtype other);

	Vec2f operator*(vtype other);
	Vec2f operator*(Vec2f& other);

	Vec2f operator/(vtype other);
	Vec2f operator/(Vec2f& other);


	friend std::ostream& operator<<(std::ostream& output, const Vec2f& a);
	float dot(Vec2f& other);
	float dot();
	vtype length();
	vtype length2();
	Vec2f normalize();
};
Vec2f operator+(vtype scalar, Vec2f& other);
Vec2f operator-(vtype scalar, Vec2f& other);
Vec2f operator*(vtype scalar, Vec2f& other);
Vec2f operator/(vtype scalar, Vec2f& other);



