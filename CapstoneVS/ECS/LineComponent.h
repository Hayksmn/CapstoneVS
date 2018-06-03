#pragma once

#include "ECS.h"
#include <GLFW\glfw3.h>
#include "Engine/Graphics/Texture.h"
#include <iostream>
#include <string>
#include "vec2.h"

class LineComponent : public Component {

private:
	Texture * texture;

	bool startSelected = false;
	bool endSelected = false;

public:

	vec2<float> startPoint;
	vec2<float> endPoint;
	float radius;

	LineComponent();
	LineComponent(vec2<float> start, vec2<float> end, float rad);

	void init() override;

	void update() override;

	void draw() override;
};