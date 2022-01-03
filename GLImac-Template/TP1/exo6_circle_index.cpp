#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstddef>
#include <vector>

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
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/triangle.vs.glsl",
                                  applicationPath.dirPath() + "shaders/triangle.fs.glsl");
    program.use();

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    u_int N = 8;
    float theta = 0;
    std::vector<Vertex2DColor> vertices;
    std::vector<u_int32_t> indices;
    vertices.emplace_back(Vertex2DColor(glm::vec2(0.0f, 0.0f), glm::vec3(1, 1, 1)));
    for ( u_int n = 1; n < N + 2; ++n )
    {
        vertices.emplace_back(Vertex2DColor(glm::vec2(0.5 * glm::cos<float>(theta), 0.5 * glm::sin<float>(theta)), 
                                            glm::vec3(1, 1, 1)));
        theta += glm::pi<float>() * 2/N;
        indices.emplace_back(0);
        indices.emplace_back(n);
        indices.emplace_back(n + 1);
    }

    glBufferData(GL_ARRAY_BUFFER, (N+2) * sizeof(Vertex2DColor), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    GLuint ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (N*3) * sizeof(u_int32_t), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    const GLuint VERTEX_ATTR_POSITION = 3;
    const GLuint VERTEX_ATTR_COLOR    = 8;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*) offsetof(Vertex2DColor, position));
    glVertexAttribPointer(VERTEX_ATTR_COLOR,    3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*) offsetof(Vertex2DColor, color));

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
        glDrawElements(GL_TRIANGLES, N*3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    return EXIT_SUCCESS;
}
