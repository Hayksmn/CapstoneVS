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
				}

                engine.endRender();

				Keyboard::reset();
				Mouse::reset();
        }
}