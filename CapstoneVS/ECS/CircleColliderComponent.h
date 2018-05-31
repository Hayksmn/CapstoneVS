#pragma once

#include "vec2.h"
#include <string>
#include <iostream>
#include "Game.h"
#include "Components.h"

class CircleColliderComponent : public Component {

public:

	TransformComponent * transform;

	vec2<float> center;
	float rad;
	std::string tag = "";

	CircleColliderComponent();
	CircleColliderComponent(std::string t);

	void init() override;
	void update() override;
};