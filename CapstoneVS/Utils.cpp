#include "Utils.h"
#include <GLFW\glfw3.h>

float Utils::distance(const vec2<float>& point1, const vec2<float>& point2) {

	return sqrtf((point1.x - point2.x)*(point1.x - point2.x) +
		(point1.y - point2.y)*(point1.y - point2.y));
}

void Utils::drawLine(const vec2<float>& point1, const vec2<float>& point2) {

	glLoadIdentity();
	glLineWidth(5);
	glBegin(GL_LINE_STRIP);
	glVertex2f(point1.x, point1.y);
	glVertex2f(point2.x, point2.y);
	glEnd();
}