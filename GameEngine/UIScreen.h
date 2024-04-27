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
	UIScreen();
	virtual ~UIScreen();
	UIState getState() const { return state; }
	void setTitle(const string& titleP, const Vector3& color = Vector3(255, 255, 255), int pointSize = 40);
	virtual void update(float deltaTime);
	virtual void draw();
	virtual void processInput(const class InputState& inputState);
	void close();
protected:
	void drawTexture(class Texture* texture, const Vector2& offset = Vector2::zero);
	class Font& font;
	class Texture* title;
	Vector2 titlePosition;
	UIState state;
};