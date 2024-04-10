#pragma once
#include "Vector3.h"
#include "Color.h"

struct Fruit {
public:
	Fruit() : color(Color::cherry), radius(10.0f) {}
	Fruit(Vector3 colorP, float radiusP) : color(colorP), radius(radiusP) {}
	Vector3 getColor() { return color; }
	float getRadius() { return radius; }
private:
	Vector3 color;
	float radius;
};

namespace Fruits
{
	static const Fruit cherry(Color::cherry, 10.0f);
	static const Fruit strawberrry(Color::strawberrry, 10.0f);
	static const Fruit grape(Color::grape, 10.0f);
	static const Fruit dekopon(Color::dekopon, 10.0f);
	static const Fruit orange(Color::orange, 10.0f);
	static const Fruit apple(Color::apple, 10.0f);
	static const Fruit pear(Color::pear, 10.0f);
	static const Fruit peach(Color::peach, 10.0f);
	static const Fruit pineapple(Color::pineapple, 10.0f);
	static const Fruit melon(Color::melon, 10.0f);
	static const Fruit watermelon(Color::watermelon, 10.0f);
};