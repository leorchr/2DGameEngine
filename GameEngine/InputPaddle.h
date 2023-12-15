#pragma once
#include "InputComponent.h"

class InputPaddle : public InputComponent
{
public:
	InputPaddle(Actor* ownerP);
	InputPaddle() = delete;
	InputPaddle(const InputPaddle&) = delete;
	InputPaddle& operator=(const InputPaddle&) = delete;

	void processInput(const Uint8* keyState) override;
};

