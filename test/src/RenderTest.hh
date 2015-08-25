/**
 *  Copyright (c) 2015 Timothy Greenfield <tjgreenfield@gmail.com>
 *
 * This file is part of SViGGLe.
 *
 * SViGGLe is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.

 * SViGGLe is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with SViGGLe.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#define GLEW_STATIC
#include "screenshot.hh"

#include <SVGL/Render/RenderContext.hh>
#include <SVGL/Elements/Transform/Transform.hh>
#include <SVGL/Document.hh>
#include <SVGL/Elements/ElementsElement.hh>

#include <SVGL/GL/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace SVGL;

SVGL::Document_uptr document(nullptr);
CSS::StyleSheet styleSheet;
float viewX = 0.0f;
float viewY = 0.0f;
float scale = 0.0008f;
double tolerance = 2000 / 480.f;
bool wireframe = true;
bool needScreenshot = false;


static void errorCallback(int error, const char* description)
{
    fputs(description, stderr);
}

int windowWidth = 0;
int windowHeight = 0;

static void windowSizeCallback(GLFWwindow* window, int width, int height)
{
    windowWidth = width;
    windowHeight = height;
}

double mouseX = 0.0f;
double mouseY = 0.0f;
int mouseLeftButton = 0;

static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    switch (button)
    {
    case GLFW_MOUSE_BUTTON_1:
        mouseLeftButton = action;
        break;
    }
}

static void mouseMoveCallback(GLFWwindow* window, double x, double y)
{
    if (mouseLeftButton == GLFW_PRESS)
    {
        viewX += (x - mouseX) / scale / windowWidth * 2;
        viewY += (y - mouseY) / scale / windowWidth * 2;
    }
    mouseX = x;
    mouseY = y;
}

static void mouseScrollCallback(GLFWwindow* window, double x, double y)
{
    scale *= std::pow(0.9, -y);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        if (action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        break;
    case GLFW_KEY_UP:
        if (action == GLFW_PRESS)
        {
            viewY += 0.05 / scale;
        }
        break;
    case GLFW_KEY_DOWN:
        if (action == GLFW_PRESS)
        {
            viewY -= 0.05 / scale;
        }
        break;
    case GLFW_KEY_LEFT:
        if (action == GLFW_PRESS)
        {
            viewX += 0.05 / scale;
        }
        break;
    case GLFW_KEY_RIGHT:
        if (action == GLFW_PRESS)
        {
            viewX -= 0.05 / scale;
        }
        break;

    case GLFW_KEY_EQUAL:
        if (action == GLFW_PRESS)
        {
            scale /= 0.9;
        }
        break;
    case GLFW_KEY_MINUS:
        if (action == GLFW_PRESS)
        {
            scale *= 0.9;
        }
        break;
    case GLFW_KEY_COMMA:
        if (action == GLFW_PRESS)
        {
            tolerance *= 2;
            document->clearBuffers();
            document->buffer(tolerance);
        }
        break;
    case GLFW_KEY_PERIOD:
        if (action == GLFW_PRESS)
        {
            tolerance *= 0.5;
            document->clearBuffers();
            document->buffer(tolerance);
        }
        break;
    case GLFW_KEY_SPACE:
        if (action == GLFW_PRESS)
        {
            wireframe = !wireframe;
            if (wireframe)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            }
            else
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
        }
        break;
    case GLFW_KEY_ENTER:
        if (action == GLFW_PRESS)
        {
            SVGL::Parser parser;
            parser.loadFile("data/example.svg");
            document = parser.readSVG();
            document->applyStyleSheet(&styleSheet);
            document->buffer(tolerance);
        }
        break;
    case GLFW_KEY_F10:
        if (action == GLFW_PRESS)
        {
            needScreenshot = true;
        }

        break;
    }
}

static GLFWwindow* initGL()
{
    glfwSetErrorCallback(errorCallback);
    if (!glfwInit())
        exit(EXIT_FAILURE);

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    windowWidth = 1280;
    windowHeight = 720;

    glfwMakeContextCurrent(window);

    glfwSetWindowSizeCallback(window, windowSizeCallback);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);
    glfwSetCursorPosCallback(window, mouseMoveCallback);
    glfwSetScrollCallback(window, mouseScrollCallback);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        cerr << "Error: " << glewGetErrorString(err) << endl;
        exit(1);

    }

    if (!glewIsSupported("GL_VERSION_1_4"))
    {
        cerr << "Need OpenGL 4+ support." << endl;
        exit(1);
    }

    return window;
}

static int initShaders()
{
    const char* vertexShader =
        "#version 400\n"
        "uniform dmat3x2 transform;"
        "uniform float depth;"
        "in vec2 vp;"
        "void main () {"
        "  gl_Position = vec4 (vp.x * transform[0][0] + vp.y * transform[1][0] + transform[2][0],"
        "                      vp.x * transform[0][1] + vp.y * transform[1][1] + transform[2][1],"
        "                      depth,"
        "                      1.0);"
        "}";

    const char* fragmentShader =
        "#version 400\n"
        "uniform vec4 pen;"
        "out vec4 frag_colour;"
        "void main () {"
        "  frag_colour = vec4 (pen);"
        "}";


    unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vertexShader, NULL);
    glCompileShader(vs);
    GLchar buffer[4096];
    GLsizei len;
    GLint status;
    glGetShaderiv(vs, GL_COMPILE_STATUS, &status);
    glGetShaderInfoLog(vs, 4095, &len, buffer);
    cout << "Vertex Shader Log: (" << status << ") " << buffer << endl;

    unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fragmentShader, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &status);
    glGetShaderInfoLog(fs, 4095, &len, buffer);
    cout << "Fragment Shader Log: (" << status << ") " << buffer << endl;

    unsigned int shaderProgramme = glCreateProgram();
    glAttachShader(shaderProgramme, fs);
    glAttachShader(shaderProgramme, vs);
    glLinkProgram(shaderProgramme);

    return shaderProgramme;
}

void renderTest()
{
    GLFWwindow* window = initGL();
    int shaderProgramme = initShaders();


    SVGL::Parser parser;
    parser.loadFile("data/example.svg");

    document = parser.readSVG();

    styleSheet.add("path {stroke:red;}");

    document->applyStyleSheet(&styleSheet);
    document->buffer(tolerance);


    const unsigned int size(5);
    GLuint buffer;
    GLuint vertexArray;
    double points[] = {-0.3, -0.3,
                                    0.3, -0.3,
                                    0.3, 0.3,
                                    -0.3, 0.3,
                                    -0.3, -0.3};

    glGenBuffers(1, &buffer);
    glGenVertexArrays(1, &vertexArray);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, size * 2 * sizeof(double), points, GL_STATIC_DRAW);

    glBindVertexArray(vertexArray);
    glEnableVertexAttribArray(0); // ??
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 0, (GLubyte*)NULL);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_BLEND);
    glEnable (GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(1.0);

    while (!glfwWindowShouldClose(window))
    {
        // Update window information to adapt to any window size changes
        float ratio;
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float) height;

        // Reset GL rendering
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgramme);

        // Setup SVG rendering
        SVGL::Render::Context context;

        SVGL::Transform t;
        t.scaleR(1, ratio);
        //t.rotateR(glfwGetTime() / 10);
        t.scaleR(scale, -scale);
        t.translateR(viewX, viewY);
        context.pushTransform(&t);
        context.pushColor(rgb(128, 128, 128));

        glBegin(GL_TRIANGLE_STRIP);
        glVertex2f(-0.5, -0.5);
        glVertex2f(0.5, -0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(-0.5, 0.5);
        glVertex2f(-0.5, -0.5);
        glEnd();

        context.pushColor(rgb(128, 0, 128));

        glBindVertexArray(vertexArray);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, size);

        // Next frame
        document->render(&context);

        if (needScreenshot)
        {
            std::unique_ptr<GLubyte> buffer(new GLubyte[windowWidth * windowHeight * 4]);
            glReadPixels(0, 0, windowWidth, windowHeight, GL_RGB, GL_UNSIGNED_BYTE, buffer.get());
            screenshot(buffer.get(), windowWidth, windowHeight);
            needScreenshot = false;
        }

        // next frame
        glfwPollEvents();

        glfwSwapBuffers(window);

    }
}
