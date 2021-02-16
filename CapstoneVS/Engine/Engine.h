#ifndef MAIN_ENGINE
#define MAIN_ENGINE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;

class Engine {
public:
        static int SCREEN_WIDTH;
        static int SCREEN_HEIGHT;

        Engine();
        ~Engine();

        bool initialize(const char* windowTitle);

        void update(); 
        void beginRender(); 
        void endRender();

        static GLFWwindow* window;
private:
        
};
#endif // !MAIN_ENGINE

