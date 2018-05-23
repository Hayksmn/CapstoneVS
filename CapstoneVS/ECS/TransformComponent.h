#pragma once
#include "Components.h"
#include "vec2.h"

#include <string>
#include <iostream>

// add other transformations here upon necessity 
class TransformComponent : public Component {

public:

	vec2<float> position;
	float speed;
	float rot;
	float xScale;
	float yScale;
	float rad;


	TransformComponent();
	TransformComponent(float x, float y, float r);

	void speedTo(float x);
	void speedBy(float x);

	void moveTo(float x, float y);
	void moveBy(float x, float y);

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void rotateTo(float x);
	void rotateBy(float x);

	void setScale(float x);
	void setScale(float x, float y);




};

TransformComponent::TransformComponent() {
	position.x = 0.0f;
	position.y = 0.0f;
	speed = 5.0f;
}

TransformComponent::TransformComponent(float x, float y, float r) {
	position.x = x;
	position.y = y;
	rad = r;
	speed = 5.0f;
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