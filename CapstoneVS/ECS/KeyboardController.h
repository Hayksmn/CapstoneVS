#pragma once

#include "Components.h"
#include "vec2.h"
#include "Engine\IO\Keyboard.h"
#include <string>
#include <iostream>

// add other transformations here upon necessity 
class KeyboardController : public Component {

private:

public:
	

	KeyboardController();

	void init() override;

	void update() override;
};