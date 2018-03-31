#ifndef MAIN_SPRITE
#define MAIN_SPRITE

#include <GLFW\glfw3.h>
#include "Texture.h"

#include <iostream>
#include <string>

using namespace std;

class Sprite {
public:
        Sprite();
        Sprite(string imagePath);
        Sprite(string imagePath, float _xPos, float _yPos);

        void update();
        void render();

private:
        Texture texture;
        float xPos;
        float yPos;
};
#endif // !MAIN_SPRITE

