#pragma once

#include"ECS/vec2.h"
#include<vector>
#include<iostream>

class Utils {

public:

	static float distance(const vec2<float>& point1, const vec2<float>& point2);

	static void drawLine(const vec2<float>& point1, const vec2<float>& point2);
};
