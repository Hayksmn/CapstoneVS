#include "TouchComponent.h"

TouchComponent::TouchComponent() = default;

void TouchComponent::init() {
	//&entity->addComponent<TransformComponent>();
}

void TouchComponent::update() {
	TransformComponent* transform = &entity->getComponent<TransformComponent>();

	//if (selected) {

	//	auto mx = (float)Mouse::getMouseX();
	//	auto my = (float)Mouse::getMouseY();

	//	transform->velocity.x = mx - (transform->position.x + (transform->width) / 2);
	//	transform->velocity.y = my - (transform->position.y + (transform->height) / 2);

	//}

	//if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT)) {
	//	double x, y;
	//	x = Mouse::getMouseX();
	//	y = Mouse::getMouseY();
	//	if (transform->position.x <= x && (transform->position.x + transform->width) >= x &&
	//		transform->position.y <= y && (transform->position.y + transform->height) >= y)
	//	{
	//		selected = true;
	//		std::cout << "selected" << std::endl;
	//	}
	//}

	//if (Mouse::buttonUp(GLFW_MOUSE_BUTTON_LEFT)) {
	//	selected = false;
	//}

	if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT)) {
		double x, y;
		x = Mouse::getMouseX();
		y = Mouse::getMouseY();
		cout << "x = " << x << " : y = " << y << endl;
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
			float dst = Utils::distance(vec2<float>((transform->position.x + (transform->width) / 2), (transform->position.y + (transform->height) / 2)), vec2<float>(Mouse::getMouseX(), Mouse::getMouseY()));
			transform->velocity.x = ((transform->position.x + (transform->width) / 2) - Mouse::getMouseX()) / 10;
			transform->velocity.y = ((transform->position.y + (transform->height) / 2) - Mouse::getMouseY()) / 10;
			transform->speedTo(0.05f * dst);

			std::cout << "fliging!" << std::endl;
		}
		fling = false;
	}
}

void TouchComponent::draw() {
	TransformComponent* transform = &entity->getComponent<TransformComponent>();

	if (fling) {
		Utils::drawLine(vec2f((transform->position.x + (transform->width) / 2), (transform->position.y + (transform->height) / 2)), vec2<float>((float)Mouse::getMouseX(), (float)Mouse::getMouseY()), 5);
	}
}