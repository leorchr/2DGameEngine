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
	static const Fruit cherry(Color::cherry, 15.0f);
	static const Fruit strawberrry(Color::strawberrry, 20.0f);
	static const Fruit grape(Color::grape, 40.0f);
	static const Fruit dekopon(Color::dekopon, 55.0f);
	static const Fruit orange(Color::orange, 65.0f);
	static const Fruit apple(Color::apple, 80.0f);
	static const Fruit pear(Color::pear, 90.0f);
	static const Fruit peach(Color::peach, 120.0f);
	static const Fruit pineapple(Color::pineapple, 130.0f);
	static const Fruit melon(Color::melon, 150.0f);
	static const Fruit watermelon(Color::watermelon, 170.0f);
};