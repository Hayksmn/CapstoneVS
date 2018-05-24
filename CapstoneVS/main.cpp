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
		newSprite.addComponent<SpriteComponent>("Assets/Art/circle.png");
		newSprite.addComponent<TouchComponent>();
		newSprite.addComponent<KeyboardController>(); 
		//auto tex = newSprite.getComponent<SpriteComponent>().getTextureParams();

		//todo: see why this gives a delay
		//newSprite.getComponent<TransformComponent>().setScale(30/(float)tex.getWidth());

		cout << (newSprite.hasComponent<TransformComponent>() ? "Yes!" : "NO") << endl;

        bool running = true;
        while (running) {
                engine.update();
				
                //newSprite.getComponent<TransformComponent>().moveTo((float)Mouse::getMouseX(), (float)Mouse::getMouseY());

				manager.update();

				engine.beginRender();
				manager.draw();
                engine.endRender();
        }
}