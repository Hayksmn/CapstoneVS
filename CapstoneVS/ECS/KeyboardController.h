#pragma once

#include "Components.h"
#include "vec2.h"
#include "Engine\IO\Mouse.h"
#include <string>
#include <iostream>

// add other transformations here upon necessity 
class KeyboardController : public Component {

private:

public:
	TransformComponent * transform;

	KeyboardController() = default;

	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			&entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {
		if (Keyboard::keyDown(GLFW_KEY_W)) {
			transform->velocity.y = 1;
		}
		if (Keyboard::keyDown(GLFW_KEY_S)) {
			transform->velocity.y = -1;
		}
		if (Keyboard::keyDown(GLFW_KEY_A)) {
			transform->velocity.x = -1;
		}
		if (Keyboard::keyDown(GLFW_KEY_D)) {
			transform->velocity.x = 1;
		}


		if (Keyboard::keyUp(GLFW_KEY_W)) {
			transform->velocity.y = 0;
		}
		if (Keyboard::keyUp(GLFW_KEY_S)) {
			transform->velocity.y = 0;
		}
		if (Keyboard::keyUp(GLFW_KEY_A)) {
			transform->velocity.x = 0;
		}
		if (Keyboard::keyUp(GLFW_KEY_D)) {
			transform->velocity.x = 0;
		}
	}
};