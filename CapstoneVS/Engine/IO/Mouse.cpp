#include "Mouse.h"

double Mouse::x = 0;
double Mouse::y = 0;

bool Mouse::buttons[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::buttonsDown[GLFW_MOUSE_BUTTON_LAST] = { 0 };
bool Mouse::buttonsUp[GLFW_MOUSE_BUTTON_LAST] = { 0 };

void Mouse::mousePosCallback(GLFWwindow* window, double _x, double _y) {
        //becuase 0,0 is different for window and opengl
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        x = _x;
        y = height - _y;

}

void Mouse::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        if (button < 0){
                return;
        }

        if (action != GLFW_RELEASE && buttons[button] == false) {
                buttonsDown[button] = true;
                buttonsUp[button] = false;
        }

        if (action == GLFW_RELEASE && buttons[button] == true) {
                buttonsDown[button] = false;
                buttonsUp[button] = true;
        }

        buttons[button] = action != GLFW_RELEASE;
}

double Mouse::getMouseX() {
        return x;
}

double Mouse::getMouseY() {
        return y;
}

bool Mouse::buttonDown(int button) {
        bool x = buttonsDown[button];
        //buttonsDown[button] = false;
        return x;
}

bool Mouse::buttonUp(int button) {
        bool x = buttonsUp[button];
        //buttonsUp[button] = false;
        return x;
}

bool Mouse::button(int button) {
        return buttons[button];
}

void Mouse::reset() {
		memset(buttonsUp, false, GLFW_MOUSE_BUTTON_LAST * sizeof(bool));
		memset(buttonsDown, false, GLFW_MOUSE_BUTTON_LAST * sizeof(bool));
}