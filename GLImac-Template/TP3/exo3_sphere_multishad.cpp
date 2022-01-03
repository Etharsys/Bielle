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


struct EarthProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uEarthTexture;
    GLint uCloudTexture;

    EarthProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/multiTex3D.fs.glsl")) {
        uMVPMatrix    = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uEarthTexture = glGetUniformLocation(m_Program.getGLId(), "uEarthTexture");
        uCloudTexture = glGetUniformLocation(m_Program.getGLId(), "uCloudTexture");
    }
};

struct MoonProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    MoonProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/Tex3D.fs.glsl")) {
        uMVPMatrix    = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix     = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture      = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};


int main(int argc, char** argv) {

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
    MoonProgram  moon_p  (applicationPath);
    EarthProgram earth_p (applicationPath);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);

    // Textures
    auto texEarth = loadImage("../../assets/textures/EarthMap.jpg");
    auto texMoon  = loadImage("../../assets/textures/MoonMap.jpg");
    auto texCloud = loadImage("../../assets/textures/CloudMap.jpg");
    if (texEarth == NULL || texMoon == NULL || texCloud == NULL) {
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

    GLuint textCloud;
    glGenTextures(1, &textCloud);
    glBindTexture(GL_TEXTURE_2D, textCloud);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texCloud.get()->getWidth(), 
            texCloud.get()->getHeight(), 0, GL_RGBA, GL_FLOAT, texCloud.get()->getPixels());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    // variables
    Sphere sphere(1, 32, 32);

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

    std::cout << earth_p.uCloudTexture << std::endl;
    std::cout << earth_p.uEarthTexture << std::endl;
    std::cout << moon_p.uTexture << std::endl;

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

        earth_p.m_Program.use();
        glBindVertexArray(vao); 
            MVMatrix     = glm::translate(glm::mat4(1.), glm::vec3(.0f, .0f, -5.f));
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            glUniformMatrix4fv(earth_p.uMVPMatrix   , 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
            glUniformMatrix4fv(earth_p.uMVMatrix    , 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(earth_p.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, textEarth);
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, textCloud);
                    glUniform1i(earth_p.uEarthTexture, 0);
                    glUniform1i(earth_p.uCloudTexture, 1);
                    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
                glActiveTexture(GL_TEXTURE1);
                glBindTexture(GL_TEXTURE_2D, 0);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);


            moon_p.m_Program.use();
            for (u_int i = 0; i < nbMoons; ++i)
            {
                MVMatrix     = glm::translate(glm::mat4(1.), glm::vec3(.0f, .0f, -5.f));
                NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
                MVMatrix     = glm::rotate(MVMatrix, windowManager.getTime(), rotAxes.at(i)); 
                MVMatrix     = glm::translate(MVMatrix, translations.at(i)); 
                MVMatrix     = glm::scale(MVMatrix, glm::vec3(0.2, 0.2, 0.2));
                NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
                glUniformMatrix4fv(moon_p.uMVPMatrix   , 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                glUniformMatrix4fv(moon_p.uMVMatrix    , 1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(moon_p.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                glBindTexture(GL_TEXTURE_2D, textMoon);
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
    glDeleteTextures(1, &textCloud);

    return EXIT_SUCCESS;
}
