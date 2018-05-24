#pragma once
#include "Components.h"
#include "vec2.h"

#include <string>
#include <iostream>

// add other transformations here upon necessity 
class TransformComponent : public Component {

public:

	vec2<float> position;
	vec2<float> velocity;

	// default values
	float width = 32;
	float height = 32;

	float speed = 5;
	float rot = 0;
	float xScale = 1;
	float yScale = 1;

	TransformComponent();
	TransformComponent(float x, float y);

	void init() override {
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override {
		position.x += velocity.x*speed;
		position.y += velocity.y*speed;
	}

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

	void setWidth(float w);
	void setHeight(float h);

};

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