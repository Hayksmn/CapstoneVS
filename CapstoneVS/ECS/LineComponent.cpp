#include"LineComponent.h"
#include "Engine/IO/Mouse.h"
#include "Utils.h"
#include "Game.h"

LineComponent::LineComponent() {
	startPoint = vec2<float>(100, 30);
	endPoint = vec2<float>(200, 30);
	radius = 15;
}

LineComponent::LineComponent(vec2<float> start, vec2<float> end, float rad) {
	startPoint = start;
	endPoint = end;
	radius = rad;
}

void LineComponent::init() {
	

	Game::lines.push_back(this);
}

void LineComponent::update() {
	if (startSelected) {
		vec2<float> mousePos(Mouse::getMouseX(), Mouse::getMouseY());
		startPoint = mousePos;
	} else 	if (endSelected) {
		vec2<float> mousePos(Mouse::getMouseX(), Mouse::getMouseY());
		endPoint = mousePos;
	}

	if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT)) {
		vec2<float> mousePos(Mouse::getMouseX(), Mouse::getMouseY());
		if (Utils::distance(startPoint, mousePos) <= radius) {
			startSelected = true;
			std::cout << "start selected" << std::endl;
		}
		else if (Utils::distance(endPoint, mousePos) <= radius) {
			endSelected = true;
			std::cout << "end selected" << std::endl;
		}
	}

	if (Mouse::buttonUp(GLFW_MOUSE_BUTTON_LEFT)) {
		startSelected = false;
		endSelected = false;
	}
}

void LineComponent::draw() {

	Texture* texture = new Texture("Assets/Art/circle.png");

	Utils::drawCircle(texture, startPoint, radius);
	Utils::drawCircle(texture, endPoint, radius);

	vec2<float> normal(-(endPoint.y - startPoint.y), endPoint.x - startPoint.x);
	normal.normalize();
	normal *= radius;

	Utils::drawLine(startPoint + normal, endPoint + normal);
	Utils::drawLine(startPoint - normal, endPoint - normal);
}