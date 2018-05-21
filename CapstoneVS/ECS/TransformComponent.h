#pragma once
#include "Components.h"
#include "vec2.h"

// add other transformations here upon necessity 
class TransformComponent : public Component {

public:
	vec2<float> position;

	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}
};
