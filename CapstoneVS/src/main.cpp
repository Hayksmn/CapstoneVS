#include "Engine\Engine.h"
#include "Engine\Graphics\Sprite.h"
#include <iostream>

using namespace std;

int main(void) {
        cout << "Hello!" << endl;

        Engine engine;
        engine.initialize((char*)"Capstone"); //TODO have to look into why i have to typecast const char* to char* for this to work

        Sprite sprite = Sprite("./src/Assets/Art/Biplane.png", 100, 100);

        bool running = true;
        while (running) {
                engine.update();
                sprite.update();

                engine.beginRender();
                sprite.render();
                engine.endRender();
        }
}