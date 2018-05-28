#pragma once

#include "Components.h"
#include "vec2.h"
#include <string>
#include <iostream>
#include "Game.h"

class CircleColliderComponent : public Component {

public:

	TransformComponent * transform;

	vec2<float> center;
	float rad;
	string tag = "";

	CircleColliderComponent() = default;
	CircleColliderComponent(string t) {
		tag = t;
	}

	void init() override {
		if (!entity->hasComponent<TransformComponent>()) {
			&entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();

		Game::colliders.push_back(this);
	}

	void update() override {
		center.x = transform->position.x + transform->width / 2;
		center.y = transform->position.y + transform->height / 2;
		rad = transform->width / 2;
	}
};