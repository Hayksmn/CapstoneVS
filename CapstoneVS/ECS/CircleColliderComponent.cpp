#include"CircleColliderComponent.h"
#include "Components.h"

CircleColliderComponent::CircleColliderComponent() = default;
CircleColliderComponent::CircleColliderComponent(std::string t) {
	tag = t;
}

void CircleColliderComponent::init() {
	if (!entity->hasComponent<TransformComponent>()) {
		&entity->addComponent<TransformComponent>();
	}
	transform = &entity->getComponent<TransformComponent>();

	Game::colliders.push_back(this);
}

void CircleColliderComponent::update() {
	center.x = transform->position.x + transform->width / 2;
	center.y = transform->position.y + transform->height / 2;
	rad = transform->width / 2;
}