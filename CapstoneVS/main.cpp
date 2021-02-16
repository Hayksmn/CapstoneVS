#include "Engine\Engine.h"
#include <iostream>
#include <cmath>

#include "ECS/Components.h"
#include "ECS/Collision.h"

#include "Utils.h"

using namespace std;

Manager manager;

int main(void) {
	cout << "Hello!" << endl;

	Engine engine;
	engine.initialize("Capstone"); //TODO have to look into why i have to typecast const char* to char* for this to work
	//now you dont )

	float borders[24] = {
		42, 541,
		42, 106,

		106, 42,
		541, 42,

		106, 602,
		541, 602,

		626, 602,
		1071, 602,

		626, 42,
		1071, 42,
		1129, 541,
		1129, 106
	};

	for (int i = 0; i < 24; i+=4) {
		auto& line(manager.addEntity());
		line.addComponent<LineComponent>(vec2<float>(borders[i], borders[i+1]), vec2<float>(borders[i+2], borders[i+3]), 15);
		line.getComponent<LineComponent>().setVisibility(false);
	}

	for (int i = 0; i < 10; i++) {
		auto& ball(manager.addEntity());

		ball.addComponent<TransformComponent>(Utils::random(106, 1068), Utils::random(106, 540), 45, 45);
		ball.addComponent<SpriteComponent>("Assets/Art/8ball.png", "ball" + i + 1);
		ball.addComponent<TouchComponent>();
		ball.addComponent<CircleColliderComponent>("ball" + std::to_string(i));
		ball.addComponent<KeyboardController>();
	}

	auto& background(manager.addEntity());
	background.addComponent<TransformComponent>(0, 0, Engine::SCREEN_WIDTH, Engine::SCREEN_HEIGHT);
	background.addComponent<SpriteComponent>("Assets/Art/background.png", "bcg");


	bool running = true;
	while (!glfwWindowShouldClose(Engine::window)) {

		engine.update();

		manager.update();

		std::vector<CircleColliderComponent*> colliders = manager.getColliders();
		vector<pair<CircleColliderComponent*, CircleColliderComponent*>> currentCollisions;
		vector<Entity*> fakeEntities;

		for (int i = 0; i <= colliders.size() - 1; i++)
		{
			CircleColliderComponent *srcCol = colliders[i];

			TransformComponent* transform = &srcCol->entity->getComponent<TransformComponent>();
			
			#pragma region Circle to line collision
			//line to circle
			for (auto& edge : Game::lines) {

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
					Entity* fake = new Entity();
					CircleColliderComponent* fakeball = &fake->addComponent<CircleColliderComponent>("fake");// &fake.getComponent<CircleColliderComponent>();
					&fake->addComponent<TransformComponent>(closestPoint.x - edge->radius, closestPoint.y - edge->radius, 2 * edge->radius, 2 * edge->radius);
					fakeball->rad = edge->radius;
					fakeball->mass = srcCol->mass * 0.8f;
					fakeball->center = closestPoint;

					fakeball->entity->getComponent<TransformComponent>().velocity = srcCol->entity->getComponent<TransformComponent>().velocity * (-1);	// We will use these later to allow the lines to impart energy into ball
																						// if the lines are moving, i.e. like pinball flippers

					// Store Fake Ball
					fakeEntities.push_back(fake);

					// Add collision to vector of collisions for dynamic resolution
					currentCollisions.push_back({ srcCol, fakeball });

					float fOverlap;

					if (fDistance == 0)
					{
						cout << 0 << endl;

						fDistance = 0.1;
					}

					// Calculate displacement required
					fOverlap = -(fDistance - srcCol->rad - fakeball->rad);

					// Displace Current Ball away from collision
					srcCol->entity->getComponent<TransformComponent>().moveBy(fOverlap * (srcCol->center.x - fakeball->center.x) / fDistance, fOverlap * (srcCol->center.y - fakeball->center.y) / fDistance);

					//fake
				}

			}
#pragma endregion
			
			#pragma region Circle To Circle
			//circle to circle
			for (int j = i + 1; j < colliders.size(); j++)
			{
				CircleColliderComponent* targetCol = colliders[j];
				//TODO: find a better way to check if it's the same ball (maybe tag is not set)
				//if (srcCol->tag != targetCol->tag) {
				if (Collision::circle(*srcCol, *targetCol)) {


					//cout <<"" << 

					TransformComponent* t1 = &srcCol->entity->getComponent<TransformComponent>();

					TransformComponent* t2 = &targetCol->entity->getComponent<TransformComponent>();



					float dst = Collision::centerDistance(srcCol->center, targetCol->center);

					if (dst == 0)
					{
						cout << 0 << endl;

						dst = 0.1;

					}

					float overlap = 0.5f * (dst - srcCol->rad - targetCol->rad);

					float xDst = srcCol->center.x - targetCol->center.x;
					float yDst = srcCol->center.y - targetCol->center.y;

					t1->moveBy(-overlap * xDst / dst,
						-overlap * yDst / dst);
					t2->moveBy(overlap * xDst / dst,
						overlap * yDst / dst);

					currentCollisions.push_back({ srcCol, targetCol });
				}
				//}
			}
#pragma endregion

			
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


		if (Keyboard::keyDown(GLFW_KEY_D)) {

			auto mX = Mouse::getMouseX();
			auto mY = Mouse::getMouseY();
			if (mX > 0 && mX < Engine::SCREEN_WIDTH && mY>0 && mY < Engine::SCREEN_HEIGHT)
			{
				auto& line(manager.addEntity());
				line.addComponent<LineComponent>();
			}
		}

		//resolve collisions
		for (auto& c : currentCollisions) {
			Utils::drawLine(c.first->center, c.second->center, 5);



			CircleColliderComponent *b1 = c.first;
			CircleColliderComponent *b2 = c.second;

			TransformComponent* t1 = &b1->entity->getComponent<TransformComponent>();
			TransformComponent* t2 = &b2->entity->getComponent<TransformComponent>();

			// Distance between balls
			float fDistance = Utils::distance(b1->center, b2->center);

			float nx;
			float ny;
			vec2<float> normal;

			if (fDistance == 0)
			{
				cout << 0 << endl;

				fDistance = 0.1;
				// Normal

				nx = (((float(rand()) / float(RAND_MAX)) * (0.2f)) - 0.1f) / fDistance;
				ny = (((float(rand()) / float(RAND_MAX)) * (0.2f)) - 0.1f) / fDistance;
				normal = vec2<float>(nx, ny);

				t1->velocity = normal;
				t2->velocity = normal * -1;

			}
			else
			{
				// Normal
				nx = (b2->center.x - b1->center.x) / fDistance;
				ny = (b2->center.y - b1->center.y) / fDistance;
				normal = vec2<float>(nx, ny);
			}
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

			float m12 = (dpTan1 * (b2->mass - b1->mass) + 2.0f * b1->mass * dpTan1) / (b1->mass + b2->mass);
			float m22 = (dpTan2 * (b2->mass - b1->mass) + 2.0f * b1->mass * dpTan2) / (b1->mass + b2->mass);

			// Update ball velocities
			vec2<float> dv11 = tangent * m12;
			vec2<float> dv12 = normal * m1;
			t1->velocity = dv11 + dv12;
			vec2<float> dv21 = tangent * m22;
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

		for (auto& f : fakeEntities) {
			delete f;
		}
		fakeEntities.clear();

		engine.beginRender();
		manager.draw();
		engine.endRender();

		Keyboard::reset();
		Mouse::reset();
	}
}