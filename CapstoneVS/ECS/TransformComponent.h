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
	float width = 64;
	float height = 64;

	float speed = 5;
	float rot = 0;
	float xScale = 1;
	float yScale = 1;

	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
		speed = 3.0f;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
		speed = 5.0f;
	}

	TransformComponent(float x, float y, float w, float h) {
		position.x = x;
		position.y = y;
		width = w;
		height = h;
		speed = 5.0f;
	}

	void init() override {
		velocity.x = 0;
		velocity.y = 0;
	}

	void update() override {
		position.x += velocity.x*speed;
		position.y += velocity.y*speed;
	}

	void speedTo(float x) {
		speed = x;
	}

	void speedBy(float x) {
		speed += x;
	}

	void moveTo(float x, float y) {
		position.x = x;
		position.y = y;
	}

	void moveBy(float x, float y) {
		position.x += x;
		position.y += y;
	}

	void moveLeft() {
		position.x -= speed;
	}

	void  moveRight() {
		position.x += speed;
		speed += speed;
	}

	void  moveUp() {
		position.y += speed;
	}

	void  moveDown() {
		position.y -= speed;
	}

	void  rotateTo(float x) {
		rot = x;
	}

	void rotateBy(float x) {
		rot += x;
	}

	void setScale(float x) {
		xScale = x;
		yScale = x;
	}

	void setScale(float x, float y) {
		xScale = x;
		yScale = y;
	}

	void setWidth(float w) {
		width = w;
	}

	void setHeight(float h) {
		height = h;
	}
};

