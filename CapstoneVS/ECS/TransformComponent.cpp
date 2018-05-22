#include "TransformComponent.h"

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
	position.x += y;
}

void TransformComponent::moveLeft() {
	position.x -= speed;
}

void TransformComponent::moveRight() {
	position.x += speed;
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
