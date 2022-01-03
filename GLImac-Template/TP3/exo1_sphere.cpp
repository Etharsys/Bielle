#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/common.hpp>
#include <glm/gtc/random.hpp>

using namespace glimac;



int main(int argc, char** argv) {

    if (argc != 3) {
        std::cout << "Unvalid arguments of shaders : ./exec [VS] [FS]" << std::endl; 
        return 1;
    }

    auto vsPath = argv[1];
    auto fsPath = argv[2];


    // Initialize SDL and open a window
    float height = 800;
    float width  = 1000;
    SDLWindowManager windowManager(width, height, "GLImac");

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

    glEnable(GL_DEPTH_TEST);

    // Textures
    auto texEarth = loadImage("../../assets/textures/EarthMap.jpg");
    auto texMoon  = loadImage("../../assets/textures/MoonMap.jpg");
    if (texEarth == NULL || texMoon == NULL) {
        std::cerr << "Cannot load texture at : ~/Documents/Synthèse2/GLImac-Template/assets/textures/" << std::endl;
        return -1;
    }

    GLuint textEarth;
    glGenTextures(1, &textEarth);
    glBindTexture(GL_TEXTURE_2D, textEarth);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texEarth.get()->getWidth(), 
            texEarth.get()->getHeight(), 0, GL_RGBA, GL_FLOAT, texEarth.get()->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLuint textMoon;
    glGenTextures(1, &textMoon);
    glBindTexture(GL_TEXTURE_2D, textMoon);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texMoon.get()->getWidth(), 
            texMoon.get()->getHeight(), 0, GL_RGBA, GL_FLOAT, texMoon.get()->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    GLint uTexture = glGetUniformLocation(program.getGLId(), "uTexture");


    // variables
    Sphere sphere(1, 32, 32);

    GLint uMVPMatrix    = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVMatrix     = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), width/height, .1f, 100.f);
    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;


    // VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount() * sizeof(ShapeVertex), 
            sphere.getDataPointer(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    // VAO
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
        const GLuint VERTEX_ATTR_POSITION  = 0;
        const GLuint VERTEX_ATTR_NORMAL    = 1;
        const GLuint VERTEX_ATTR_TEXCOORDS = 2;
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
            glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 
                sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));

            glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
            glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 
                sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));

            glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
            glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 
                sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));

        glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);


    // 32 moons
    u_int nbMoons = 32;
    std::vector<glm::vec3> rotAxes;
    std::vector<glm::vec3> translations;
    for(u_int i = 0; i < nbMoons; ++i) {
        rotAxes.emplace_back(glm::sphericalRand(1.));
        translations.emplace_back(glm::sphericalRand(2.));
    }
    

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

        //glClearColor(0.,0.,1.,0.0);
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBindVertexArray(vao); 
            MVMatrix     = glm::translate(glm::mat4(1.), glm::vec3(.0f, .0f, -5.f));
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            glUniformMatrix4fv(uMVPMatrix   , 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
            glUniformMatrix4fv(uMVMatrix    , 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            glBindTexture(GL_TEXTURE_2D, textEarth);
                glUniform1i(uTexture, 0);
                glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
            glBindTexture(GL_TEXTURE_2D, 0);

            for (u_int i = 0; i < nbMoons; ++i)
            {
                MVMatrix     = glm::translate(glm::mat4(1.), glm::vec3(.0f, .0f, -5.f));
                NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
                MVMatrix     = glm::rotate(MVMatrix, windowManager.getTime(), rotAxes.at(i)); 
                MVMatrix     = glm::translate(MVMatrix, translations.at(i)); 
                MVMatrix     = glm::scale(MVMatrix, glm::vec3(0.2, 0.2, 0.2));
                NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
                glUniformMatrix4fv(uMVPMatrix   , 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                glUniformMatrix4fv(uMVMatrix    , 1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                glBindTexture(GL_TEXTURE_2D, textMoon);
                    glUniform1i(uTexture, 0);
                    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                glBindTexture(GL_TEXTURE_2D, 0);

            }
        glBindVertexArray(0);
    
        windowManager.swapBuffers();
        
    }

    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteTextures(1, &textEarth);
    glDeleteTextures(1, &textMoon);

    return EXIT_SUCCESS;
}
