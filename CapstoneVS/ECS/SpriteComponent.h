#pragma once

#include <GLFW\glfw3.h>

#include "ECS/TransformComponent.h"
#include "Engine/Graphics/Texture.h"

#include <iostream>
#include <string>

class TransformComponent;

class SpriteComponent : public Component {

private:
	TransformComponent *transform;
	Texture *texture;

public:

	SpriteComponent();
	SpriteComponent(string imagePath);

	Texture getTextureParams();

	void init() override;

	void update() override;

	void draw() override;
};
