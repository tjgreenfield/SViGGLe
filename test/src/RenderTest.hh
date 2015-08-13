#include <SVGL/Render/RenderContext.hh>
#include <SVGL/Elements/Transform/Transform.hh>
#include <SVGL/Document.hh>
#include <SVGL/Elements/ElementsElement.hh>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace SVGL;

static void errorCallback(int error, const char* description)
{
    fputs(description, stderr);
}

static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
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

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, keyCallback);

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
        "in vec2 vp;"
        "void main () {"
        "  gl_Position = vec4 (vp.x * transform[0][0] + vp.y * transform[1][0] + transform[2][0],"
        "                      vp.x * transform[0][1] + vp.y * transform[1][1] + transform[2][1],"
        "                      0.0,"
        "                      1.0);"
        "}";

    const char* fragmentShader =
        "#version 400\n"
        "uniform vec3 pen;"
        "out vec4 frag_colour;"
        "void main () {"
        "  frag_colour = vec4 (pen, 1.0);"
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

    SVGL::Document_uptr document = parser.readSVG();
    
    CSS::StyleSheet styleSheet;
    styleSheet.add("path {stroke:red;}");

    document->applyStyleSheet(&styleSheet);
    document->buffer(20 / 480.f);


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

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );

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
        glUseProgram(shaderProgramme);
        glLineWidth(3.0);

        // Setup SVG rendering
        SVGL::Render::Context context;
        //float scale = float(cos(glfwGetTime()/2) + 1.2) * 0.5;
        float scale = 0.2f;
        
        SVGL::Transform t;
        t.scaleR(1, ratio);
        //t.rotateR(glfwGetTime() / 10);
        t.scaleR(scale, scale);
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

        // next frame
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
