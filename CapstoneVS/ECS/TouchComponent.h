#pragma once

#include "Components.h"
#include "vec2.h"
#include "Engine\IO\Mouse.h"
#include <string>
#include <iostream>
#include "Utils.h"

// add other transformations here upon necessity 
class TouchComponent : public Component {

private:
	bool selected = false;
	bool fling = false;

public:

	TouchComponent();

	void init() override;
	void update() override;
	void draw() override;
};