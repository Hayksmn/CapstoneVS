#include "Engine\Engine.h"
#include <iostream>

using namespace std;

int main(void) {
        cout << "Hello!" << endl;

        Engine engine;
        engine.Initialize((char*)"Capstone"); //TODO have to look into why i have to typecast const char* to char* for this to work
        bool running = true;
        while (running) {
                engine.Update();
                engine.Render();
        }
}