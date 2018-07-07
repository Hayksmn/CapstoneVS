#ifndef MAIN_MOUSE
#define MAIN_MOUSE

#include <GLFW\glfw3.h>
#include <string.h>

//making stuff static so that 1 class handles all mouse inputs
class Mouse {
public: 
        static void mousePosCallback(GLFWwindow* window, double _x, double _y);
        static void mouseButtonCallback(GLFWwindow* window, int  button, int action, int mods);

        static double getMouseX();
        static double getMouseY();

        static bool buttonDown(int button);
        static bool buttonUp(int button);
        static bool button(int button); 

		static void reset();

private: 
        static double x;
        static double y;


        static bool buttons[];
        static bool buttonsDown[];
        static bool buttonsUp[];


};
#endif // !MAIN_MOUSE

