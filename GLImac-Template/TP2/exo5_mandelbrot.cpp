#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>

using namespace glimac;



class Vertex2DColor
{
    public:
        Vertex2DColor ()
            : position { glm::vec2{0.0f, 0.0f} }, 
              color { glm::vec3{0.0f, 0.0f, 0.0f} }
        { }

        Vertex2DColor (glm::vec2 _position, glm::vec3 _color)
            : position { _position }, color { _color }
        { }


        glm::vec2 position;
        glm::vec3 color;
};


int main(int argc, char** argv) {
    if (argc != 3) {
        std::cout << "Unvalid arguments of shaders : ./exec [VS] [FS]" << std::endl; 
        return 1;
    }

    auto vsPath = argv[1];
    auto fsPath = argv[2];


    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 800, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/" + vsPath,
                                  applicationPath.dirPath() + "shaders/" + fsPath);
    program.use();

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    Vertex2DColor vertices[] = { 
        Vertex2DColor(glm::vec2(-1., 1.), glm::vec3(1, 0, 0)),
        Vertex2DColor(glm::vec2( 1., 1.), glm::vec3(0, 1, 0)),
        Vertex2DColor(glm::vec2(-1.,-1.), glm::vec3(0, 0, 1)),
        Vertex2DColor(glm::vec2( 1., 1.), glm::vec3(0, 1, 0)),
        Vertex2DColor(glm::vec2(-1.,-1.), glm::vec3(0, 0, 1)),
        Vertex2DColor(glm::vec2( 1.,-1.), glm::vec3(1, 0, 0))
    };
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex2DColor), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_COLOR    = 1;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*) offsetof(Vertex2DColor, position));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        //glClearColor(0.4,0.4,0.4,0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
