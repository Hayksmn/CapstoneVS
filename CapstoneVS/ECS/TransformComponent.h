#pragma once
#include "Components.h"
#include "vec2.h"

// add other transformations here upon necessity 
class TransformComponent : public Component {

public:

	TransformComponent();
	TransformComponent(float x, float y);

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


	vec2<float> position;
	float speed;
	float rot;
	float xScale;
	float yScale;
};
