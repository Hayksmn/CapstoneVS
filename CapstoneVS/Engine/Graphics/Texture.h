#ifndef MAIN_TEXTURE
#define MAIN_TEXTURE

#include <GLFW\glfw3.h>
#include "SOIL\src\SOIL.h"

#include <string>
#include <iostream>

using namespace std;

class Texture {
public:
        Texture();
        Texture(int _id);
        Texture(string path);

        int getId();
        int getWidth();
        int getHeight();
private:
        int id;
        int width;
        int height;

        bool getTextureParams();
};
#endif // !MAIN_TEXTURE

