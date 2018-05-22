#pragma once
#include "Components.h"
#include "vec2.h"

// add other transformations here upon necessity 
class TransformComponent : public Component {

	
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

private:
	vec2<float> position;
	float speed;
	float rot;
	float xScale;
	float yScale;


	TransformComponent() {
		position.x = 0.0f;
		position.y = 0.0f;
		speed = 5.0f;
	}

	TransformComponent(float x, float y) {
		position.x = x;
		position.y = y;
	}
};
