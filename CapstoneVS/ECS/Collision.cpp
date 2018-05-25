#include"Collision.h"
#include"CircleColliderComponent.h"

//std::vector<CircleColliderComponent*> Collision::colliders;

bool Collision::circle(const vec2<float>& center1, const float rad1, const vec2<float>& center2, const float rad2) {
	return fabs((center1.x - center2.x)*(center1.x - center2.x) + 
		(center1.y - center2.y)*(center1.y - center2.y) <= (rad1+rad2)*(rad1+rad2));
}

float Collision::centerDistance(const vec2<float>& center1, const vec2<float>& center2) {
	return sqrtf((center1.x - center2.x)*(center1.x - center2.x) +
		(center1.y - center2.y)*(center1.y - center2.y));
}

bool Collision::circle(const CircleColliderComponent& col1, const CircleColliderComponent& col2) {
	if (circle(col1.center, col1.rad, col2.center, col2.rad)) {
		std::cout << col1.tag << " hit " << col2.tag << std::endl;
		return true;
	}
	else {
		return false;
	}
}