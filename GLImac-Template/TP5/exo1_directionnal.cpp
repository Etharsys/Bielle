#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/common.hpp>
#include <glm/gtc/random.hpp>
#include <glimac/TrackballCamera.hpp>

using namespace glimac;


struct ProgramGeneral {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uKd;
    GLint uKs;
    GLint uShininess;
    GLint uLightDir_vs;
    GLint uLightIntensity;

    ProgramGeneral(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/directionallight.fs.glsl")) {
        uMVPMatrix      = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix       = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix   = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uKd             = glGetUniformLocation(m_Program.getGLId(), "uKd");
        uKs             = glGetUniformLocation(m_Program.getGLId(), "uKs");
        uShininess      = glGetUniformLocation(m_Program.getGLId(), "uShininess");
        uLightDir_vs    = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
    }
};


double rand01() {
    return ((double) rand() / (RAND_MAX));
}

struct Material {
    Material (const glm::vec3& color) 
        : _Kd             { color },
          _Ks             { color },
          _LightIntensity { color },
          _Shininess      { (float) (rand() % 256 + 1) }
    {
        //std::cout << "Kd:" << _Kd << " | Ks:" << _Ks << " | LInt:" << _LightIntensity << " | Shin:" << _Shininess << std::endl;
    }

    glm::vec3 _Kd;
    glm::vec3 _Ks;
    glm::vec3 _LightIntensity;
    float     _Shininess;
};

struct Materials {
    Materials (u_int count)
    {
        for (u_int i = 0; i < count; ++i) {
            Material mat {glm::vec3(rand01(),rand01(),rand01())};
            _materials.emplace_back(mat);
        }
    }

    void affect_material(ProgramGeneral& program, u_int id) {
        if (id >= _materials.size()) {
            std::cerr << "id : " << id << ", cannot be read as material" << std::endl;
            return;
        }
        glUniform3fv(program.uKd             , 1, glm::value_ptr(_materials.at(id)._Kd));
        glUniform3fv(program.uKs             , 1, glm::value_ptr(_materials.at(id)._Ks));
        glUniform3fv(program.uLightIntensity , 1, glm::value_ptr(_materials.at(id)._LightIntensity));
        glUniform1f (program.uShininess      , _materials.at(id)._Shininess);
    }

    std::vector<Material> _materials;
};





int main(int argc, char** argv) {

    std::srand(std::time(nullptr));

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
    ProgramGeneral  program  (applicationPath);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);


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
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

            glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
            glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 
                sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));

            glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
            glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 
                sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));

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

    // Camera
    TrackballCamera camera {};
    Materials materials {nbMoons + 1};

    // Application loop:
    bool done = false;
    SDLKey keydown = SDLK_a;
    float light_angle = M_PI / 64.;
    glm::vec3 light_dir = glm::vec3(1,1,1);
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            } else if (e.type == SDL_KEYDOWN) {
                keydown = e.key.keysym.sym;
            } else if (e.type == SDL_KEYUP) {
                keydown = SDLK_a;
            }
        }

        if (keydown == SDLK_p) {
            camera.moveFront(-.1);
        } else if (keydown == SDLK_m) {
            camera.moveFront(+.1);
        } else if (keydown == SDLK_LEFT) {
            camera.rotateLeft(+1.);
        } else if (keydown == SDLK_RIGHT) {
            camera.rotateLeft(-1.);
        } else if (keydown == SDLK_UP) {
            camera.rotateUp(+1.);
        } else if (keydown == SDLK_DOWN) {
            camera.rotateUp(-1.);
        }

        light_dir = glm::vec3(light_dir.x * cos(light_angle) - light_dir.z * sin(light_angle),
                              light_dir.y,
                              light_dir.x * sin(light_angle) + light_dir.z * cos(light_angle));
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        program.m_Program.use();
        glBindVertexArray(vao); 
            // Light
            glUniform3fv(program.uLightDir_vs, 1, glm::value_ptr(light_dir));
            materials.affect_material(program, nbMoons);
            MVMatrix     = camera.getViewMatrix();
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            glUniformMatrix4fv(program.uMVPMatrix    , 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
            glUniformMatrix4fv(program.uMVMatrix     , 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(program.uNormalMatrix , 1, GL_FALSE, glm::value_ptr(NormalMatrix));

            glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

            for (u_int i = 0; i < nbMoons; ++i)
            {
                materials.affect_material(program, i);
                MVMatrix     = camera.getViewMatrix();
                NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
                MVMatrix     = glm::rotate(MVMatrix, windowManager.getTime(), rotAxes.at(i)); 
                MVMatrix     = glm::translate(MVMatrix, translations.at(i)); 
                MVMatrix     = glm::scale(MVMatrix, glm::vec3(0.2, 0.2, 0.2));
                NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
                glUniformMatrix4fv(program.uMVPMatrix   , 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                glUniformMatrix4fv(program.uMVMatrix    , 1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                
                glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
            }
        glBindVertexArray(0);
    
        windowManager.swapBuffers();
        
    }

    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);

    return EXIT_SUCCESS;
}
