#include "Engine\Engine.h"
#include "Engine\Graphics\Sprite.h"
#include "Engine\IO\Mouse.h"
#include "Engine\IO\Keyboard.h"
#include <iostream>

#include "ECS/Components.h"

using namespace std;

Manager manager;
auto& newSprite(manager.addEntity());

int main(void) {
        cout << "Hello!" << endl;

        Engine engine;
        engine.initialize((char*)"Capstone"); //TODO have to look into why i have to typecast const char* to char* for this to work

        //Sprite sprite = Sprite("Assets/Art/Biplane.png", 0, 0);
        //sprite.setScale(0.25f);

		newSprite.addComponent<TransformComponent>(100, 100);
		newSprite.addComponent<SpriteComponent>("Assets/Art/Biplane.png");

        bool running = true;
        while (running) {
                engine.update();
                //sprite.update();
				
				//std::cout << newSprite.getComponent<PositionComponent>().x() << ", " <<
				//	newSprite.getComponent<PositionComponent>().y() << std::endl;

                //sprite.moveTo((float)Mouse::getMouseX(), (float)Mouse::getMouseY());

                if (Mouse::buttonDown(GLFW_MOUSE_BUTTON_LEFT)) {
                        //sprite.rotateBy(10);
                }
                if (Mouse::buttonUp(GLFW_MOUSE_BUTTON_RIGHT)) {
                        //sprite.rotateBy(-10);
                }
                if (Mouse::button(GLFW_MOUSE_BUTTON_MIDDLE)) {
                        //sprite.rotateBy(-10);
                }

                if (Keyboard::key(GLFW_KEY_W)) {
                        //sprite.moveUp();
						newSprite.getComponent<TransformComponent>().moveBy(0, 5);
                }
                if (Keyboard::key(GLFW_KEY_S)) {
                        //sprite.moveDown();
						newSprite.getComponent<TransformComponent>().moveBy(0,-5);
                }
                if (Keyboard::key(GLFW_KEY_A)) {
                        //sprite.moveLeft();
						newSprite.getComponent<TransformComponent>().moveBy(-5, 0);
                }
                if (Keyboard::key(GLFW_KEY_D)) {
                        //sprite.moveRight();
						newSprite.getComponent<TransformComponent>().moveBy(5, 0);
				}

				manager.update();
				//manager.resfresh();
                engine.beginRender();
				manager.draw();
                //sprite.render();
                engine.endRender();
        }
}