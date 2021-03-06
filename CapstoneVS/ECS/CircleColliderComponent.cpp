#include"CircleColliderComponent.h"
#include "Components.h"

CircleColliderComponent::CircleColliderComponent()
{
	//rad = 32;
}

CircleColliderComponent::CircleColliderComponent(std::string t) {
	tag = t;

	//rad = 32;
}

CircleColliderComponent::CircleColliderComponent(std::string t, float r) {
	tag = t;
	rad = r;
}

void CircleColliderComponent::init() {
	//Game::colliders.push_back(this);
}

void CircleColliderComponent::update() {

	TransformComponent* transform = &entity->getComponent<TransformComponent>();

	center.x = transform->position.x + transform->width / 2;
	center.y = transform->position.y + transform->height / 2;
	rad = transform->width / 2;
}