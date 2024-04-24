#pragma once
#include "Color.h"
#include "Vector3.h"
#include <string>
#include <vector>

struct Fruit {
public:
	Fruit() : name("Cherry"), color(Color::cherry), radius(0.0f) {}
	Fruit(std::string nameP, Vector3 colorP, float radiusP) : name(nameP),color(colorP), radius(radiusP) {}
	Vector3 getColor() { return color; }
	float getRadius() { return radius; }
	std::string getName() { return name; }

	bool operator==(const Fruit& other) const {
		return color == other.color && radius == other.radius;
	}

private:
	Vector3 color;
	float radius;
	std::string name;
};

namespace Fruits
{
	static const Fruit cherry("Cherry", Color::cherry, 15.0f);
	static const Fruit strawberry("Strawberry", Color::strawberry, 20.0f);
	static const Fruit grape("Grape", Color::grape, 40.0f);
	static const Fruit dekopon("Dekopon", Color::dekopon, 55.0f);
	static const Fruit orange("Orange", Color::orange, 65.0f);
	static const Fruit apple("Apple", Color::apple, 80.0f);
	static const Fruit pear("Pear", Color::pear, 90.0f);
	static const Fruit peach("Peach", Color::peach, 120.0f);
	static const Fruit pineapple("Pineapple", Color::pineapple, 130.0f);
	static const Fruit melon("Melon", Color::melon, 150.0f);
	static const Fruit watermelon("Watermelon", Color::watermelon, 170.0f);

	static vector <Fruit> fruitList = { cherry, strawberry, grape, dekopon, orange, apple, pear, peach, pineapple, melon, watermelon };
};