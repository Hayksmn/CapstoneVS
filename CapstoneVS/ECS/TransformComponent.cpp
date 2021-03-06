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

	position.x += velocity.x;
	position.y += velocity.y;
	velocity *= friction;


	//CircleColliderComponent* ccc = &entity->getComponent<CircleColliderComponent>();

	//ccc->center.x = position.x + width / 2;
	//ccc->center.y = position.y + height / 2;
	//ccc->rad = width / 2;


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
		Utils::drawLine(vec2f((position.x + (width)/2), (position.y + (height) / 2)), vec2<float>((float)Mouse::getMouseX(), (float)Mouse::getMouseY()), 5);
	}
}