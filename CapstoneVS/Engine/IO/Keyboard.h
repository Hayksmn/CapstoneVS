#ifndef MAIN_KEYBOARD
#define MAIN_KEYBOARD

#include "GLFW\glfw3.h"
#include <string.h>

class Keyboard {
public:
        static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

        static bool keyDown(int key);
        static bool keyUp(int key);
        static bool key(int key);

		static void reset();

private:
        static bool keys[];
        static bool keysDown[];
        static bool keysUp[];
};
#endif // !MAIN_KEYBOARD

