#include "SpriteComponent.h"
#include "Components.h"

SpriteComponent::SpriteComponent() = default;
SpriteComponent::SpriteComponent(string imagePath, string t) {
	texture = new Texture(imagePath);
	tag = t;
};

Texture SpriteComponent::getTextureParams()
{
	return *texture;
}

void SpriteComponent::init() {
	if (!entity->hasComponent<TransformComponent>()) {
		&entity->addComponent<TransformComponent>();
	}
	transform = &entity->getComponent<TransformComponent>();

	transform->setScale(transform->width / (float)texture->getWidth(), transform->height / (float)texture->getHeight());
}

void SpriteComponent::update() {

}

void SpriteComponent::draw() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture->getId());
	glLoadIdentity();

	//translations -> rotations -> scaling
	glTranslatef(transform->position.x, transform->position.y, 0);
	glRotatef(0, 0, 0, 1);
	glScalef(transform->xScale, transform->yScale, 1);

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