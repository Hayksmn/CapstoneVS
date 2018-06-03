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
	glTexCoord2f(0, 0);
	glVertex2f(0, 0);

	glTexCoord2f(1, 0);
	glVertex2f(texture->getWidth(), 0);

	glTexCoord2f(1, 1);
	glVertex2f(texture->getWidth(), texture->getHeight());

	glTexCoord2f(0, 1);
	glVertex2f(0, texture->getHeight());

	glEnd();

	glDisable(GL_TEXTURE_2D);
}