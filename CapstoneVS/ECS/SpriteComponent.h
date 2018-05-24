#pragma once

#include "Components.h"
#include <GLFW\glfw3.h>

#include "ECS/TransformComponent.h"
#include "Engine/Graphics/Texture.h"

#include <iostream>
#include <string>

class SpriteComponent : public Component {

private:
	TransformComponent *transform;
	Texture *texture;

public:

	SpriteComponent() = default;
	SpriteComponent(string imagePath) {
		texture = new Texture(imagePath);
	};

	Texture getTextureParams()
	{
		return *texture;
	}

	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			&entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		transform->setScale(transform->width / (float)texture->getWidth(), transform->height / (float)texture->getHeight());
	}

	void update() override {
		
	}

	void draw() override {
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
};
