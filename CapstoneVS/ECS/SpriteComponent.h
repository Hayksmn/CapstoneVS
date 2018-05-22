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

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		 
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
		glScalef(0.25, 0.25, 1);

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
