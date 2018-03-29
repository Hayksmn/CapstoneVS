#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;


/// <summary>
/// Mains this instance.
/// </summary>
/// <returns> returns int to finish the application</returns>
int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit()) {
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!window) {
        glfwTerminate();
        return -1;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*initialize glew AFTER CREATING A CONTEXT*/
    if (glewInit() != GLEW_OK) {
        cout << "Failed to initialize GLEW!" << endl;
    }

    cout << glGetString(GL_VERSION) << endl;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}