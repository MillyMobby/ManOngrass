#include "Vec2f.h"


Vec2f::Vec2f()
{
	x = 0;
	y = 0;
}


Vec2f::Vec2f(vtype _x, vtype _y) :x(_x), y(_y) {}

Vec2f::~Vec2f() {}

//somma
Vec2f Vec2f::operator+(Vec2f& other) {
	return Vec2f(x = x + other.x, y = y + other.y);
}

Vec2f Vec2f::operator+(vtype other) {
	return Vec2f(x = x + other, y = y + other);
}

Vec2f operator+(vtype scalare, Vec2f& other) {
	return Vec2f(scalare + other.x, scalare + other.y);
}

Vec2f Vec2f:: operator+=(Vec2f& other) {
	return Vec2f(x = x + other.x, y = y + other.y);
}

Vec2f Vec2f:: operator+=(vtype other) {
	return Vec2f(x = x + other, y = y + other);
}
//sottrazione
Vec2f Vec2f::operator-(Vec2f& other) {
	return Vec2f(x = x - other.x, y = y - other.y);
}
Vec2f Vec2f::operator-(vtype other) {
	return Vec2f(x = x - other, y = y - other);
}
Vec2f operator-(vtype scalare, Vec2f& other) {
	return Vec2f(scalare - other.x, scalare - other.y);
}
//prodotto
Vec2f Vec2f::operator*(vtype other) {
	return Vec2f(x = x * other, y = y * other);
}

Vec2f Vec2f::operator*(Vec2f& other) {
	return Vec2f(x = x * other.x, y = y * other.y);
}
Vec2f operator*(vtype scalare, Vec2f& other) {
	return Vec2f(scalare * other.x, scalare * other.y);
}
//divisione
Vec2f Vec2f::operator/(vtype other) {
	return Vec2f(x = x / other, y = y / other);
}

Vec2f Vec2f::operator/(Vec2f& other) {
	return Vec2f(x = x / other.x, y = y / other.y);
}

Vec2f operator/(vtype scalare, Vec2f& other) {
	return Vec2f(other / scalare);
}
//stampa
std::ostream& operator<<(std::ostream& output, const Vec2f& a)
{
	output << " Vec( x,y: " << a.x << ", " << a.y << " )";
	return output;
}

float Vec2f::dot(Vec2f& other)
{
	return (x * other.x + y * other.y);
}
float Vec2f::dot()
{
	return (x * x + y * y);
}

vtype Vec2f::length()
{
	return(sqrt(x * x + y * y));
}
vtype Vec2f::length2()
{
	return (x * x + y * y);
}

Vec2f Vec2f::normalize()
{
	return Vec2f(x / length(), y / length());
}