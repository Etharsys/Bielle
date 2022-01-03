#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <math.h>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

using namespace glimac;

struct Vertex2DUV {

    Vertex2DUV (float x, float y)
        : _pos { glm::vec2(x, y) }, 
          _tex { glm::vec2(0., 0.) }
    { }

    glm::vec2 _pos;
    glm::vec2 _tex;
};



glm::mat3 translate(float tx, float ty) {
    return glm::mat3(glm::vec3(1,0,0), 
                     glm::vec3(0,1,0), 
                     glm::vec3(tx,ty,1));
}

glm::mat3 scale(float sx, float sy) {
    return glm::mat3(glm::vec3(sx,0,0), 
                     glm::vec3(0,sy,0), 
                     glm::vec3(0,0,1));
}

glm::mat3 rotate(float a) {
    float r = a * M_PI / 180;
    return glm::mat3(glm::vec3(cos(r),sin(r),0), 
                     glm::vec3(-sin(r),cos(r),0), 
                     glm::vec3(0,0,1));
}




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

    GLint uModelMatrix = glGetUniformLocation(program.getGLId(), "uModelMatrix");
    GLint uColor       = glGetUniformLocation(program.getGLId(), "uColor");

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);


    Vertex2DUV vertices[] = {
        Vertex2DUV {-1., -1.},
        Vertex2DUV { 1., -1.},
        Vertex2DUV { 0.,  1.}
    };
    glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex2DUV), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_TEXTURE  = 1;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*) offsetof(Vertex2DUV, _pos));
    glVertexAttribPointer(VERTEX_ATTR_TEXTURE , 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*) offsetof(Vertex2DUV, _tex));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    // Application loop:
    bool done = false;
    float angle = 0.;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }


        glClearColor(0.4,0.4,0.4,0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glBindVertexArray(vao);

        float step = 1.;
        angle += step;

        glm::mat3 T = rotate(angle) * scale(0.25,0.25) ;

        glm::mat3 tranform = rotate(angle) * translate(-0.5,-0.5) * T;
        glUniformMatrix3fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(tranform));
        glUniform3f(uColor, 1., 1., 0.);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        tranform = rotate(angle) * translate(0.5,-0.5) * T;
        glUniformMatrix3fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(tranform));
        glUniform3f(uColor, 1., 0., 0.);       
        glDrawArrays(GL_TRIANGLES, 0, 3);

        tranform = rotate(angle) * translate(-0.5,0.5) * T;
        glUniformMatrix3fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(tranform));
        glUniform3f(uColor, 0., 1., 0.);    
        glDrawArrays(GL_TRIANGLES, 0, 3);

        tranform = rotate(angle) * translate(0.5,0.5) * T;
        glUniformMatrix3fv(uModelMatrix, 1, GL_FALSE, glm::value_ptr(tranform));
        glUniform3f(uColor, 0., 0., 1.);  
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
