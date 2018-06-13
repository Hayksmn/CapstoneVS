#include"Collision.h"
#include"CircleColliderComponent.h"

//std::vector<CircleColliderComponent*> Collision::colliders;

bool Collision::circle(const vec2<float>& center1, const float rad1, const vec2<float>& center2, const float rad2) {
	return fabs((center1.x - center2.x)*(center1.x - center2.x) +
		(center1.y - center2.y)*(center1.y - center2.y) <= (rad1 + rad2)*(rad1 + rad2));
}


bool Collision::circleRel(CircleColliderComponent& col1, CircleColliderComponent& col2) {

	float dst = centerDistance(col1.center, col2.center);
	float hypo = (dst * col1.rad / col2.rad) / (1 + col1.rad / col2.rad);
	float dst2 = sqrt(hypo*hypo - col1.rad*col1.rad);

	//vector from ball 1 to ball2
	vec2f col1vec = col2.center - col1.center;

	// simulating multiplication between col1vec and the rotation matrix we get the
	// vector that points from ball 1 to  clockwise side of ball 1 when looking from ball2 to ball 1
	vec2f vector2 = vec2f(col1vec.x*dst2 / hypo + col1vec.y*col1.rad / hypo,
		col1vec.x*-col1.rad / hypo + col1vec.y*dst2 / hypo);
	//simulating multiplication between col1vec and the rotation matrix we get the
	// vector that points from ball 1 to counter clockwise side of ball 1 when looking from ball2 to ball 1
	vec2f vector1 = vec2f(col1vec.x*dst2 / hypo + col1vec.y*-col1.rad / hypo,
		col1vec.x*col1.rad / hypo + col1vec.y*dst2 / hypo);

	vec2f temp = (col2.transform->velocity*-1);

	//relative velocity vector from ball 1 to ball 2
	vec2f relveloc = col1.transform->velocity + temp;
	bool check1 = false;
	bool check2 = false;


	float length = centerDistance(vec2f(0, 0), relveloc);

	if (length > dst)
		check1 = true;

	if (vec2f::cross(relveloc, vector1) > 0 && vec2f::cross(relveloc, vector2) < 0)
		check2 = true;
	
	//vec2f relvelocn = relveloc / sqrt((relveloc.x*relveloc.x) + (relveloc.y*relveloc.y));


	//cross product v1 x v2 >0 shows v1 needs to be rotated counter clockwise to reach v2
	//here we chec if relative velocity is in the range for collision
	return check1 && check2 ;
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

