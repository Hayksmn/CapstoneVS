#include "Engine.h"
#include "IO\Mouse.h"
#include "IO\Keyboard.h"

/// <summary>
/// Initialize static variables.
/// </summary>
int Engine::SCREEN_WIDTH = 1024;
int Engine::SCREEN_HEIGHT = 768;
GLFWwindow* Engine::window = NULL;


/// <summary>
/// Initializes a new instance of the <see cref="Engine"/> class.
/// </summary>
Engine::Engine() {}


/// <summary>
/// Finalizes an instance of the <see cref="Engine"/> class.
/// </summary>
Engine::~Engine() {}


/// <summary>
/// Initializes opengl stuff.
/// </summary>
/// <param name="windowTitle">Takes the window title as a char* parameter.</param>
/// <returns>boolean value indicating whether initialization has concluded successfully or not</returns>
bool Engine::initialize(char* windowTitle) {

        //Initializing GLFW
        if (!glfwInit()) {
                cout << "Error when Initializing GLFW" << endl;
                return false;
        }
        //Creating the window and checking if it was successful
        window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowTitle, NULL, NULL);
        if (window == NULL) {
                cout << "Error While creating the window" << endl;
                return false;
        }

        //GLFW Setup
        glfwMakeContextCurrent(window);
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        glfwSwapInterval(1);
        glfwSetCursorPosCallback(window, Mouse::mousePosCallback);
        glfwSetMouseButtonCallback(window, Mouse::mouseButtonCallback);
        glfwSetKeyCallback(window, Keyboard::keyCallback);

        const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        int xPos = (mode->width - SCREEN_WIDTH) / 2;
        int yPos = (mode->height - SCREEN_HEIGHT) / 2;
        glfwSetWindowPos(window, xPos, yPos);

        //OpenGl setup
        //Viewport
        glViewport(0, 0, width, height);
        glMatrixMode(GL_PROJECTION); //sufficient for 2D
        glLoadIdentity();
        glOrtho(0, width, 0, height, -10, 10);
        glDepthRange(-10, 10);
        glMatrixMode(GL_MODELVIEW);

        //Alpha blending
        glEnable(GL_ALPHA_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        return true;
}

/// <summary>
/// Updates the back buffer.
/// </summary>
void Engine::update() {
        glfwPollEvents();
}

/// <summary>
/// Starts rendering everything in back buffer.
/// </summary>
void Engine::beginRender() {
        glClearColor(0, 0, 0, 0); //cleared back buffer and set to blue
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //cleared the depth buffer
}

void Engine::endRender(){
        glfwSwapBuffers(window);
}