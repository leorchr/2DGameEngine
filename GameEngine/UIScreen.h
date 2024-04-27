#pragma once
#include <string>
#include <functional>
#include <vector>
#include "Vector2.h"
#include "Color.h"
using std::string;
using std::vector;

enum class UIState
{
	Active, Closing
};
class UIScreen
{
public:
	UIScreen(Vector2 position);
	virtual ~UIScreen();
	UIState getState() const { return state; }
	void setTitle(const string& titleP, const Vector3& color = Vector3(255, 255, 255), int pointSize = 40);
	virtual void update(float deltaTime);
	virtual void draw();
	virtual void processInput(const class InputState& inputState);
	void close();
	void setOffsetPosition(const Vector2& offset);
	Vector2 getOffsetPosition() const { return offsetPosition; }

protected:
	void drawTexture(class Texture* texture, const Vector2& offset = Vector2::zero);
	class Font& font;
	class Texture* title;
	Vector2 titlePosition;
	Vector2 basePosition;
	Vector2 offsetPosition;
	UIState state;
};