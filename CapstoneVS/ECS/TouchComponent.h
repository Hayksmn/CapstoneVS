#pragma once

#include "Components.h"
#include "vec2.h"
#include "Engine\IO\Mouse.h"
#include <string>
#include <iostream>

// add other transformations here upon necessity 
class TouchComponent : public Component {

private:
	TransformComponent * transform;
	bool selected = false;

public:

	TouchComponent() = default;

	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			&entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {
		if (selected) {
			transform->moveTo((float)Mouse::getMouseX() - transform->width/2, (float)Mouse::getMouseY() - transform->height/2);
		}

		if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT)) {
			double x, y;
			x = Mouse::getMouseX();
			y = Mouse::getMouseY();
			if (transform->position.x <= x && (transform->position.x + transform->width) >= x &&
				transform->position.y <= y && (transform->position.y + transform->height) >= y) {
				selected = true;
				std::cout << "selected" << std::endl;
			}
		}

		if (Mouse::buttonUp(GLFW_MOUSE_BUTTON_LEFT)) {
			selected = false;
		}
	}
};