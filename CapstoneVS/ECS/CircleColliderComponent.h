#pragma once

#include "vec2.h"
#include <string>
#include <iostream>
#include "Game.h"
#include "Components.h"

class CircleColliderComponent : public Component {

public:
	CircleColliderComponent();
	CircleColliderComponent(std::string t);

	CircleColliderComponent(std::string t, float r);

	vec2<float> center;
	float rad;
	float mass = 10.0f;
	std::string tag = "";

	

	void init() override;
	void update() override;
};