#pragma once
#include "Color.h"
#include "Vector3.h"
#include <string>
#include <vector>

struct Fruit {
public:
	Fruit() : name("Cherry"), color(Color::cherry), radius(0), score(0) {}
	Fruit(std::string nameP, Vector3 colorP, int radiusP, float scoreP) : name(nameP),color(colorP), radius(radiusP), score(scoreP) {}
	Vector3 getColor() { return color; }
	int getRadius() { return radius; }
	int getScore() { return score; }
	std::string getName() { return name; }

	bool operator==(const Fruit& other) const {
		return color == other.color && radius == other.radius && score == other.score;
	}

private:
	Vector3 color;
	int radius;
	int score;
	std::string name;
};

namespace Fruits
{
	static const Fruit cherry("Cherry", Color::cherry, 15, 1);
	static const Fruit strawberry("Strawberry", Color::strawberry, 20, 3);
	static const Fruit grape("Grape", Color::grape, 40, 6);
	static const Fruit dekopon("Dekopon", Color::dekopon, 55, 10);
	static const Fruit orange("Orange", Color::orange, 65, 15);
	static const Fruit apple("Apple", Color::apple, 80, 21);
	static const Fruit pear("Pear", Color::pear, 90, 28);
	static const Fruit peach("Peach", Color::peach, 120, 36);
	static const Fruit pineapple("Pineapple", Color::pineapple, 130, 45);
	static const Fruit melon("Melon", Color::melon, 150, 55);
	static const Fruit watermelon("Watermelon", Color::watermelon, 170, 66);

	static vector <Fruit> fruitList = { cherry, strawberry, grape, dekopon, orange, apple, pear, peach, pineapple, melon, watermelon };
};