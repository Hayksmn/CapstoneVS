#include "Engine\Engine.h"
#include <iostream>

#include "ECS/Components.h"
#include "ECS/Collision.h"

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
			ball.addComponent<TransformComponent>(50*i, 50*i);
			ball.addComponent<SpriteComponent>("Assets/Art/circle.png");
			ball.addComponent<KeyboardController>();
			ball.addComponent<TouchComponent>();
			//ball.addComponent<CircleColliderComponent>("ball" + std::to_string(i));
		}

        bool running = true;
        while (!glfwWindowShouldClose(Engine::window)) {
                engine.update();

				manager.update();

				vector<pair<CircleColliderComponent*, CircleColliderComponent*>> currentCollisions;
				
				for (int i = 0; i < Game::colliders.size() - 1; i++)
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
								float dst = Collision::centerDistance(srcCol->center, targetCol->center);

								float overlap = 0.5f*(dst - srcCol->rad - targetCol->rad);

								srcCol->transform->moveBy(-overlap * (srcCol->center.x - targetCol->center.x) / dst,
									-overlap * (srcCol->center.y - targetCol->center.y) / dst);
								targetCol->transform->moveBy(overlap * (srcCol->center.x - targetCol->center.x) / dst,
									overlap * (srcCol->center.y - targetCol->center.y) / dst);

								currentCollisions.push_back({ srcCol, targetCol });
							}
						//}
					}
				}

                //newSprite.getComponent<TransformComponent>().moveTo((float)Mouse::getMouseX(), (float)Mouse::getMouseY());

				engine.beginRender();
				manager.draw();

				for (auto c : currentCollisions) {
					Utils::drawLine(c.first->center, c.second->center);

					CircleColliderComponent *b1 = c.first;
					CircleColliderComponent *b2 = c.second;

					// Distance between balls
					float fDistance = Utils::distance(b1->center, b2->center);

					// Normal
					float nx = (b2->transform->position.x - b1->transform->position.x) / fDistance;
					float ny = (b2->transform->position.y - b1->transform->position.y) / fDistance;
					vec2<float> normal(nx, ny);

					// Tangent
					vec2<float> tangent(-ny, nx);

					// Dot Product Tangent
					
					float dpTan1 = tangent.dot(b1->transform->velocity, tangent);
					float dpTan2 = tangent.dot(b2->transform->velocity, tangent);

					// Dot Product Normal
					float dpNorm1 = tangent.dot(b1->transform->velocity, normal);
					float dpNorm2 = tangent.dot(b2->transform->velocity, normal);

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