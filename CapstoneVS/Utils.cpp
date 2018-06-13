#include "Utils.h"
#include <GLFW\glfw3.h>

float Utils::distance(const vec2<float>& point1, const vec2<float>& point2) {

	return sqrtf((point1.x - point2.x)*(point1.x - point2.x) +
		(point1.y - point2.y)*(point1.y - point2.y));
}

void Utils::drawLine(const vec2<float>& point1, const vec2<float>& point2, int width) {

	glLoadIdentity();
	glLineWidth(width);
	glBegin(GL_LINE_STRIP);
	glVertex2f(point1.x, point1.y);
	glVertex2f(point2.x, point2.y);
	glEnd();
}

void Utils::drawCircle(Texture* texture, const vec2<float>& center, const float rad) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->getId());
	glLoadIdentity();

	//translations -> rotations -> scaling
	glTranslatef(center.x - rad, center.y - rad, 0);
	glRotatef(0, 0, 0, 1);
	float scale = 2 * rad / texture->getWidth();
	glScalef(scale, scale, 1);

	//Rendering
	glColor4f(1, 1, 1, 1);
	glBegin(GL_QUADS);
	//WARNING for images 0, 0 is bottom left
	glTexCoord3f(0, 0, 10);
	glVertex3f(0, 0, 10);

	glTexCoord3f(1, 0, 10);
	glVertex3f(texture->getWidth(), 0, 10);

	glTexCoord3f(1, 1, 10);
	glVertex3f(texture->getWidth(), texture->getHeight(), 10);

	glTexCoord3f(0, 1, 10);
	glVertex3f(0, texture->getHeight(), 10);

	glEnd();

	glDisable(GL_TEXTURE_2D);
}