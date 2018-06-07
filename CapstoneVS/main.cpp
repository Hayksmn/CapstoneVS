#include "Engine\Engine.h"
#include <iostream>
#include <cmath>

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
	//ball1.addComponent<KeyboardController>(); 
	//ball1.addComponent<CircleColliderComponent>("initial ball");
	//ball1.addComponent<SpriteComponent>("Assets/Art/circle.png", "ball1");
	//auto tex = newSprite.getComponent<SpriteComponent>().getTextureParams();

	//todo: see why this gives a delay
	//newSprite.getComponent<TransformComponent>().setScale(30/(float)tex.getWidth());

	//cout << (ball1.hasComponent<TransformComponent>() ? "Yes!" : "NO") << endl;

	auto& line(manager.addEntity());
	line.addComponent<LineComponent>();
	line.addComponent<LineComponent>(vec2<float>(500, 50), vec2<float>(700, 50), 15);
	line.addComponent<LineComponent>(vec2<float>(300, 30), vec2<float>(600, 30), 15);
	line.addComponent<LineComponent>(vec2<float>(300, 100), vec2<float>(600, 100), 15);

	line.init();

	for (int i = 0; i < 10; i++) {
		auto& ball(manager.addEntity());
		//TODO: setting width and height is buggy


		ball.addComponent<TransformComponent>(50 * i, 50 * i, 50, 50);
		ball.addComponent<CircleColliderComponent>("ball" + std::to_string(i));
		ball.addComponent<KeyboardController>();
		ball.addComponent<SpriteComponent>("Assets/Art/circle.png", "ball" + i + 1);
		ball.init();
		//ball.addComponent<TouchComponent>();
	}

	bool running = true;
	while (!glfwWindowShouldClose(Engine::window)) {

		engine.update();

		manager.update();

		vector<pair<CircleColliderComponent*, CircleColliderComponent*>> currentCollisions;
		vector<CircleColliderComponent*> fakeBalls;

		for (int i = 0; i <= Game::colliders.size() - 1; i++)
		{
			CircleColliderComponent *srcCol = Game::colliders[i];

			TransformComponent* transform = &srcCol->entity->getComponent<TransformComponent>();

			//temporary
			if (srcCol->center.x < 0) 
				transform->position.x += Engine::SCREEN_WIDTH;
			if (srcCol->center.x >= Engine::SCREEN_WIDTH)
				transform->position.x -= Engine::SCREEN_WIDTH;
			if (srcCol->center.y < 0)
				transform->position.y += Engine::SCREEN_HEIGHT;
			if (srcCol->center.y >= Engine::SCREEN_HEIGHT)
				transform->position.y -= Engine::SCREEN_HEIGHT;

			for (auto &edge : Game::lines) {

				// Check that line formed by velocity vector, intersects with line segment
				vec2<float> line1 = edge->endPoint - edge->startPoint;

				vec2<float> line2 = srcCol->center - edge->startPoint;

				vec2f normalLine1 = vec2f(line1);
				normalLine1.normalize();

				float fEdgeLength = line1.length();

				// This is nifty - It uses the DP of the line segment vs the line to the object, to work out
				// how much of the segment is in the "shadow" of the object vector. The min and max clamp
				// this to lie between 0 and the line segment length, which is then normalised. We can
				// use this to calculate the closest point on the line segment
				float dotp = vec2<float>::dot(line2, normalLine1);

				float t = max(0.0f, min(fEdgeLength, vec2<float>::dot(line2, normalLine1))) / fEdgeLength;

				// Which we do here
				vec2<float> actualLine = line1 * t;
				vec2<float> closestPoint = edge->startPoint + actualLine;

				// And once we know the closest point, we can check if the ball has collided with the segment in the
				// same way we check if two balls have collided
				float fDistance = Utils::distance(srcCol->center, closestPoint);

				if (fDistance <= (srcCol->rad + edge->radius))
				{



					cout << "t = " << t << std::endl;
					// Collision has occurred - treat collision point as a ball that cannot move. To make this
					// compatible with the dynamic resolution code below, we add a fake ball with an infinite mass
					// so it behaves like a solid object when the momentum calculations are performed
					//auto& fake(manager.addEntity());
					//fake.addComponent<CircleColliderComponent>("fake");
					CircleColliderComponent *fakeball = new CircleColliderComponent("fake");// &fake.getComponent<CircleColliderComponent>();
					fakeball->entity->addComponent<TransformComponent>(closestPoint.x - edge->radius, closestPoint.y - edge->radius, 2*edge->radius, 2 * edge->radius);
					fakeball->rad = edge->radius;
					fakeball->mass = srcCol->mass * 0.8f;
					fakeball->center = closestPoint;
					
					fakeball->entity->getComponent<TransformComponent>().velocity = srcCol->entity->getComponent<TransformComponent>().velocity * (-1);	// We will use these later to allow the lines to impart energy into ball
																						// if the lines are moving, i.e. like pinball flippers

					// Store Fake Ball
					fakeBalls.push_back(fakeball);

					// Add collision to vector of collisions for dynamic resolution
					currentCollisions.push_back({ srcCol, fakeball });

					// Calculate displacement required
					float fOverlap = -(fDistance - srcCol->rad - fakeball->rad);

					// Displace Current Ball away from collision
					srcCol->entity->getComponent<TransformComponent>().moveBy(fOverlap * (srcCol->center.x - fakeball->center.x) / fDistance, fOverlap * (srcCol->center.y - fakeball->center.y) / fDistance);
				}
			}

			for (int j = i + 1; j < Game::colliders.size(); j++)
			{
				CircleColliderComponent *targetCol = Game::colliders[j];
				//TODO: find a better way to check if it's the same ball (maybe tag is not set)
				//if (srcCol->tag != targetCol->tag) {
				if (Collision::circle(*srcCol, *targetCol)) {


					//cout <<"" << 

					TransformComponent* t1=&srcCol->entity->getComponent<TransformComponent>();
					
					TransformComponent* t2=&targetCol->entity->getComponent<TransformComponent>();



					float dst = Collision::centerDistance(srcCol->center, targetCol->center);

					float overlap = 0.5f*(dst - srcCol->rad - targetCol->rad);

					t1->moveBy(-overlap * (srcCol->center.x - targetCol->center.x) / dst,
						-overlap * (srcCol->center.y - targetCol->center.y) / dst);
					t2->moveBy(overlap * (srcCol->center.x - targetCol->center.x) / dst,
						overlap * (srcCol->center.y - targetCol->center.y) / dst);

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

			float fr=ball[0]->getComponent<TransformComponent>().friction;

			cout << "Friction"<<fr;
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

			cout << "Friction "<< fr;
		}



		//newSprite.getComponent<TransformComponent>().moveTo((float)Mouse::getMouseX(), (float)Mouse::getMouseY());

		for (auto& c : currentCollisions) {
			Utils::drawLine(c.first->center, c.second->center);

			CircleColliderComponent *b1 = c.first;
			CircleColliderComponent *b2 = c.second;

			TransformComponent* t1 = &b1->entity->getComponent<TransformComponent>();
			TransformComponent* t2 = &b2->entity->getComponent<TransformComponent>();

			// Distance between balls
			float fDistance = Utils::distance(b1->center, b2->center);

			// Normal
			float nx = (b2->center.x - b1->center.x) / fDistance;
			float ny = (b2->center.y - b1->center.y) / fDistance;
			vec2<float> normal(nx, ny);

			// Tangent
			vec2<float> tangent(-ny, nx);

			// Dot Product Tangent

			float dpTan1 = vec2<float>::dot(t1->velocity, tangent);
			float dpTan2 = vec2<float>::dot(t2->velocity, tangent);

			// Dot Product Normal
			float dpNorm1 = vec2<float>::dot(t1->velocity, normal);
			float dpNorm2 = vec2<float>::dot(t2->velocity, normal);

			// Conservation of momentum in 1D
			float m1 = (dpNorm1 * (b1->mass - b2->mass) + 2.0f * b2->mass * dpNorm2) / (b1->mass + b2->mass);
			float m2 = (dpNorm2 * (b2->mass - b1->mass) + 2.0f * b1->mass * dpNorm1) / (b1->mass + b2->mass);

			// Update ball velocities
			vec2<float> dv11 = tangent * dpTan1;
			vec2<float> dv12 = normal * m1;
			t1->velocity = dv11 + dv12;
			vec2<float> dv21 = tangent * dpTan2;
			vec2<float> dv22 = normal * m2;
			t2->velocity = dv21 + dv22;

			// Wikipedia Version - Maths is smarter but same
			//float kx = (b1->vx - b2->vx);
			//float ky = (b1->vy - b2->vy);
			//float p = 2.0 * (nx * kx + ny * ky) / (b1->mass + b2->mass);
			//b1->vx = b1->vx - p * b2->mass * nx;
			//b1->vy = b1->vy - p * b2->mass * ny;
			//b2->vx = b2->vx + p * b1->mass * nx;
			//b2->vy = b2->vy + p * b1->mass * ny;
		}

		for (auto& f : fakeBalls) delete f;
		fakeBalls.clear();

		engine.beginRender();

		manager.draw();

		engine.endRender();

		Keyboard::reset();
		Mouse::reset();
	}
}