#include "Rectangle.h"

const Rectangle Rectangle::nullRect{ 0.f, 0.f, 0.f, 0.f };

Rectangle::Rectangle(float xP, float yP, float widthP, float heightP)
	: x(xP), y(yP), width(widthP), height(heightP)
{}

Rectangle::~Rectangle() {};