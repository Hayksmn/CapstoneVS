#pragma once

#include"ECS/vec2.h"
#include "Engine/Graphics/Texture.h"
#include<vector>
#include<iostream>

class Utils {

public:

	static float distance(const vec2<float>& point1, const vec2<float>& point2);

	static void drawLine(const vec2<float>& point1, const vec2<float>& point2, int width);

	static void drawCircle(Texture* textue, const vec2<float>& center, const float rad);
};
