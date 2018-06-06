#include "TransformComponent.h"

TransformComponent::TransformComponent() {
	position.x = 0.0f;
	position.y = 0.0f;
	speed = 3.0f;
}

TransformComponent::TransformComponent(float x, float y) {
	position.x = x;
	position.y = y;
	speed = 5.0f;
}

TransformComponent::TransformComponent(float x, float y, float w, float h) {
	position.x = x;
	position.y = y;
	width = w;
	height = h;
	speed = 5.0f;
}

void TransformComponent::init() {
	velocity.x = 0;
	velocity.y = 0;
}

void TransformComponent::update() {



	if (selected) {

		auto mx = (float)Mouse::getMouseX();
		auto my = (float)Mouse::getMouseY();

		velocity.x = mx - (position.x + (width) / 2);
		velocity.y = my - (position.y + (height) / 2);
		
	}

	if (drag) {

		auto mx = (float)Mouse::getMouseX();
		auto my = (float)Mouse::getMouseY();

		moveTo(mx - (width) / 2, position.y);

		
		//velocity.x = mx - (position.x );
		//velocity.y = my - (position.y );

	}

	if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_MIDDLE)) {
		double x, y;
		x = Mouse::getMouseX();
		y = Mouse::getMouseY();
		if (position.x <= x && (position.x + width) >= x &&
			position.y <= y && (position.y + height) >= y)
		{
			drag = true;
			std::cout << "selected" << std::endl;
		}
	}

	if (Mouse::buttonUp(GLFW_MOUSE_BUTTON_MIDDLE)) {
		drag = false;

	}

	if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT)) {
		double x, y;
		x = Mouse::getMouseX();
		y = Mouse::getMouseY();
		if (position.x <= x && (position.x + width) >= x &&
			position.y <= y && (position.y + height) >= y)
		{
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
		if (position.x <= x && (position.x + width) >= x &&
			position.y <= y && (position.y + height) >= y) {
			fling = true;
			std::cout << "fliging start" << std::endl;
		}
	}


	if (Mouse::buttonUp(GLFW_MOUSE_BUTTON_RIGHT)) {
		if (fling) {
			float dst = Utils::distance(vec2<float>((position.x + (width) / 2), (position.y + (height) / 2)), vec2<float>(Mouse::getMouseX(), Mouse::getMouseY()));
			velocity.x = ((position.x + (width) / 2) - Mouse::getMouseX()) / 10;
			velocity.y = ((position.y + (height) / 2) - Mouse::getMouseY()) / 10;
			speedTo(0.05f * dst);

			std::cout << "fliging!" << std::endl;
		}
		fling = false;
	}


	position.x += velocity.x;
	position.y += velocity.y;
	velocity *= friction;
	if (fabs(velocity.x*velocity.x + velocity.y*velocity.y) < 0.001f)
	{
		velocity.x = 0;
		velocity.y = 0;
	}

}

void TransformComponent::speedTo(float x) {
	speed = x;
}

void TransformComponent::speedBy(float x) {
	speed += x;
}

void TransformComponent::moveTo(float x, float y) {
	position.x = x;
	position.y = y;
}

void TransformComponent::moveBy(float x, float y) {
	position.x += x;
	position.y += y;
}

void TransformComponent::moveLeft() {
	position.x -= speed;
}

void TransformComponent::moveRight() {
	position.x += speed;
	speed += speed;
}

void TransformComponent::moveUp() {
	position.y += speed;
}

void TransformComponent::moveDown() {
	position.y -= speed;
}

void TransformComponent::rotateTo(float x) {
	rot = x;
}

void TransformComponent::rotateBy(float x) {
	rot += x;
}

void TransformComponent::setScale(float x) {
	xScale = x;
	yScale = x;
}

void TransformComponent::setScale(float x, float y) {
	xScale = x;
	yScale = y;
}

void TransformComponent::setWidth(float w) {
	width = w;
}

void TransformComponent::setHeight(float h) {
	height = h;
}

void TransformComponent::draw() {
	if (fling) {
		Utils::drawLine(vec2f((position.x + (width)/2), (position.y + (height) / 2)), vec2<float>((float)Mouse::getMouseX(), (float)Mouse::getMouseY()));
	}
}