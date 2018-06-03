#pragma once
#include <vector>
class CircleColliderComponent;
class LineComponent;

class Game {
public:
	static std::vector<CircleColliderComponent*> colliders;

	static std::vector<LineComponent*> lines;
};