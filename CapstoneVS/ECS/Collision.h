#pragma once
#include"vec2.h"
#include<vector>
#include<iostream>

class CircleColliderComponent;

class Collision {

public:

	//static std::vector<CircleColliderComponent*> colliders;

	static bool circle(const vec2<float>& center1, const float rad1, const vec2<float>& center2, const float rad2);

	static float centerDistance(const vec2<float>& center1, const vec2<float>& center2);

	static bool circle(const CircleColliderComponent& col1, const CircleColliderComponent& col2);
};