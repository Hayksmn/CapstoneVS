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

	TransformComponent();

	TransformComponent(float x, float y);

	TransformComponent(float x, float y, float w, float h);

	void init() override;

	void update() override;

	void speedTo(float x);

	void speedBy(float x);

	void moveTo(float x, float y);

	void moveBy(float x, float y);

	void moveLeft();

	void  moveRight();

	void  moveUp();

	void  moveDown();

	void  rotateTo(float x);

	void rotateBy(float x);

	void setScale(float x);

	void setScale(float x, float y);

	void setWidth(float w);

	void setHeight(float h);
};

