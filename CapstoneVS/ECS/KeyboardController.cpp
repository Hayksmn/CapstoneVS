#include "KeyboardController.h"

KeyboardController::KeyboardController() = default;

void KeyboardController::init() {
	
}

void KeyboardController::update() {

	TransformComponent* transform = &entity->getComponent<TransformComponent>();



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