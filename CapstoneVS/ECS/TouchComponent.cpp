#include "TouchComponent.h"

TouchComponent::TouchComponent() = default;

void TouchComponent::init() {
	if (!entity->hasComponent<TransformComponent>()) {
		&entity->addComponent<TransformComponent>();
	}
	if (!entity->hasComponent<CircleColliderComponent>()) {
		&entity->addComponent<CircleColliderComponent>();
	}
	transform = &entity->getComponent<TransformComponent>();
	collider = &entity->getComponent<CircleColliderComponent>();
}

void TouchComponent::update() {
	if (selected) {
		transform->moveTo((float)Mouse::getMouseX() - transform->width / 2, (float)Mouse::getMouseY() - transform->height / 2);
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

	if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_RIGHT)) {
		double x, y;
		x = Mouse::getMouseX();
		y = Mouse::getMouseY();
		if (transform->position.x <= x && (transform->position.x + transform->width) >= x &&
			transform->position.y <= y && (transform->position.y + transform->height) >= y) {
			fling = true;
			std::cout << "fliging start" << std::endl;
		}
	}
	

	if (Mouse::buttonUp(GLFW_MOUSE_BUTTON_RIGHT)) {
		if (fling) {
			float dst = Utils::distance(collider->center, vec2<float>(Mouse::getMouseX(), Mouse::getMouseY()));
			transform->velocity.x = (collider->center.x - Mouse::getMouseX())/10;
			transform->velocity.y = (collider->center.y - Mouse::getMouseY())/10;
			transform->speedTo(0.05f * dst);

			std::cout << "fliging!" << std::endl;
		}
		fling = false;
	}
}

void TouchComponent::draw() {
	if (fling) {
		Utils::drawLine(collider->center, vec2<float>((float)Mouse::getMouseX(), (float)Mouse::getMouseY()));
	}
}