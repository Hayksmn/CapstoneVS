#pragma once

#include "ECS.h"
#include <GLFW\glfw3.h>
#include "Engine/Graphics/Texture.h"
#include <iostream>
#include <string>

class TransformComponent;

class SpriteComponent : public Component {

private:
	//TransformComponent *transform;
	Texture *texture;

public:

	SpriteComponent();
	SpriteComponent(string imagePath, string t);

	Texture getTextureParams();

	std::string tag;

	void init() override;

	void update() override;

	void draw() override;
};
