#include "Engine\Engine.h"
#include <iostream>

#include "ECS/Components.h"
#include "ECS/Collision.h"
#include "ECS/vec2.h"

#include "Utils.h"

using namespace std;

Manager manager;
//auto& ball1(manager.addEntity());


int main(void) {
	cout << "Hello!" << endl;

	Engine engine;
	engine.initialize((char*)"Capstone"); //TODO have to look into why i have to typecast const char* to char* for this to work



	//Sprite sprite = Sprite("Assets/Art/Biplane.png", 0, 0);
	//sprite.setScale(0.25f);

	//ball1.addComponent<TransformComponent>(100, 100);
	//ball1.addComponent<SpriteComponent>("Assets/Art/circle.png");
	//ball1.addComponent<TouchComponent>();
	//ball1.addComponent<CircleColliderComponent>("initial ball");
	//ball1.addComponent<KeyboardController>(); 
	//auto tex = newSprite.getComponent<SpriteComponent>().getTextureParams();

	//todo: see why this gives a delay
	//newSprite.getComponent<TransformComponent>().setScale(30/(float)tex.getWidth());

	//cout << (ball1.hasComponent<TransformComponent>() ? "Yes!" : "NO") << endl;

	for (int i = 0; i < 10; i++) {
		auto& ball(manager.addEntity());
		//TODO: setting width and height is buggy 
		ball.addComponent<TransformComponent>(50 * i, 50 * i);
		ball.addComponent<KeyboardController>();
		ball.addComponent<CircleColliderComponent>();
		ball.addComponent<SpriteComponent>("Assets/Art/circle.png", "ball" + i + 1);
		//ball.addComponent<TouchComponent>();
	}

	bool running = true;
	while (!glfwWindowShouldClose(Engine::window)) {

		engine.update();

		manager.update();

		vector<pair<CircleColliderComponent*, CircleColliderComponent*>> currentCollisions;

		for (int i = 0; i <= Game::colliders.size() - 1; i++)
		{
			CircleColliderComponent *srcCol = Game::colliders[i];

			//temporary
			if (srcCol->center.x < 0) srcCol->transform->position.x += Engine::SCREEN_WIDTH;
			if (srcCol->center.x >= Engine::SCREEN_WIDTH) srcCol->transform->position.x -= Engine::SCREEN_WIDTH;
			if (srcCol->center.y < 0) srcCol->transform->position.y += Engine::SCREEN_HEIGHT;
			if (srcCol->center.y >= Engine::SCREEN_HEIGHT) srcCol->transform->position.y -= Engine::SCREEN_HEIGHT;


			for (int j = i + 1; j < Game::colliders.size(); j++)
			{
				CircleColliderComponent *targetCol = Game::colliders[j];
				//TODO: find a better way to check if it's the same ball (maybe tag is not set)
				//if (srcCol->tag != targetCol->tag) {
				if (Collision::circle(*srcCol, *targetCol)) {


					float overlap = 0;

					float msx = 0;
					float msy = 0;

					float mtx = 0;
					float mty = 0;

					//cout <<"" << 

					float dst = Collision::centerDistance(srcCol->center, targetCol->center);

					overlap = 0.5f*(dst - srcCol->rad - targetCol->rad);


					if (dst != 0.0f)
					{
						msx = -overlap * (srcCol->center.x - targetCol->center.x) / dst;
						msy = -overlap * (srcCol->center.y - targetCol->center.y) / dst;
						mtx = overlap * (srcCol->center.x - targetCol->center.x) / dst;
						mty = overlap * (srcCol->center.y - targetCol->center.y) / dst;
					}
					else
					{
						msx = -1;
						msy = -1;
						mtx = 1;
						mty = 1;
					}

					srcCol->transform->moveBy(msx, msy);
					srcCol->center.x += msx;
					srcCol->center.y += msy;

					targetCol->transform->moveBy(mtx, mty);
					targetCol->center.x += mtx;
					targetCol->center.y += mty;


					//srcCol->transform->velocity.x += -overlap * (srcCol->center.x - targetCol->center.x) / dst;

					//srcCol->transform->velocity.y += -overlap * (srcCol->center.y - targetCol->center.y) / dst;

					//targetCol->transform->velocity.x += overlap * (srcCol->center.x - targetCol->center.x) / dst;
					//targetCol->transform->velocity.y += overlap * (srcCol->center.y - targetCol->center.y) / dst;

					currentCollisions.push_back({ srcCol, targetCol });
				}
				//}
			}
		}

		if (Keyboard::keyDown(GLFW_KEY_R))
		{
			int i = 0;

			auto& ball(manager.getEntities());

			for (auto& c : ball)
			{
				TransformComponent* b = &c->getComponent<TransformComponent>();
				b->position = vec2f(50 * i, 50 * i);
				b->velocity = vec2f(0, 0);
				b->friction = 0.99f;

				i++;
			}

			cout << "reset";
		}

		if (Keyboard::keyDown(GLFW_KEY_DOWN))
		{
			auto& ball(manager.getEntities());
			for (auto& c : ball)
			{
				TransformComponent* b = &c->getComponent<TransformComponent>();
				b->friction -= 0.04f;
			}

			float fr = ball[0]->getComponent<TransformComponent>().friction;

			cout << "Friction" << fr;
		}
		if (Keyboard::keyDown(GLFW_KEY_UP))
		{
			auto& ball(manager.getEntities());
			for (auto& c : ball)
			{
				TransformComponent* b = &c->getComponent<TransformComponent>();
				b->friction += 0.04f;
			}

			float fr = ball[0]->getComponent<TransformComponent>().friction;

			cout << "Friction " << fr;
		}



		//newSprite.getComponent<TransformComponent>().moveTo((float)Mouse::getMouseX(), (float)Mouse::getMouseY());

		engine.beginRender();

		manager.draw();
		for (auto& c : currentCollisions) {
			Utils::drawLine(c.first->center, c.second->center);

			CircleColliderComponent *b1 = c.first;
			CircleColliderComponent *b2 = c.second;

			// Distance between balls
			float fDistance = Utils::distance(b1->center, b2->center);

			// Normal
			float nx = (b2->center.x - b1->center.x) / fDistance;
			float ny = (b2->center.y - b1->center.y) / fDistance;
			vec2<float> normal(nx, ny);

			// Tangent
			vec2<float> tangent(-ny, nx);

			// Dot Product Tangent

			float dpTan1 = vec2<float>::dot(b1->transform->velocity, tangent);
			float dpTan2 = vec2<float>::dot(b2->transform->velocity, tangent);

			// Dot Product Normal
			float dpNorm1 = vec2<float>::dot(b1->transform->velocity, normal);
			float dpNorm2 = vec2<float>::dot(b2->transform->velocity, normal);

			// Conservation of momentum in 1D
			float m1 = (dpNorm1 * (b1->mass - b2->mass) + 2.0f * b2->mass * dpNorm2) / (b1->mass + b2->mass);
			float m2 = (dpNorm2 * (b2->mass - b1->mass) + 2.0f * b1->mass * dpNorm1) / (b1->mass + b2->mass);

			// Update ball velocities
			vec2<float> dv11 = tangent * dpTan1;
			vec2<float> dv12 = normal * m1;
			b1->transform->velocity = dv11 + dv12;
			vec2<float> dv21 = tangent * dpTan2;
			vec2<float> dv22 = normal * m2;
			b2->transform->velocity = dv21 + dv22;

			// Wikipedia Version - Maths is smarter but same
			//float kx = (b1->vx - b2->vx);
			//float ky = (b1->vy - b2->vy);
			//float p = 2.0 * (nx * kx + ny * ky) / (b1->mass + b2->mass);
			//b1->vx = b1->vx - p * b2->mass * nx;
			//b1->vy = b1->vy - p * b2->mass * ny;
			//b2->vx = b2->vx + p * b1->mass * nx;
			//b2->vy = b2->vy + p * b1->mass * ny;
		}

		engine.endRender();

		Keyboard::reset();
		Mouse::reset();
	}
}