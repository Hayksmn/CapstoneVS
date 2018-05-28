#include "KeyboardController.h"

KeyboardController::KeyboardController() = default;

void KeyboardController::init() {
	if (!entity->hasComponent<TransformComponent>()) {
		&entity->addComponent<TransformComponent>();
	}
	transform = &entity->getComponent<TransformComponent>();
}

void KeyboardController::update() {
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