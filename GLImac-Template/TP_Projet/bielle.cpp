#include "BielleCommon.hpp"

#include "Arbre.hpp"
#include "GLbuffers.hpp"
#include "Piston.hpp"
#include "Bras.hpp"
#include "Rail.hpp"
#include "Bielle.hpp"
#include "Hangar.hpp"
#include "Square.hpp"
#include "Cube.hpp"
#include "Circle.hpp"
#include "Cylinder.hpp"
#include "Vector2DColor.hpp"
#include "BielleProgram.hpp"

using namespace glimac;
using namespace std;




struct Test
{
    Test()
    {
        //rail.scale(glm::vec3(l+d+2*e, 2*e, e));
    }

    void updateBuffers()
    {
        bufferRail.initVBO(rail.getVertexCount(), rail.getDataPointer());

        bufferRail.initVAO();
    }

    void drawVertices()
    {
        bufferRail.drawVertices();
    }

    void deleteArbreBuffers()
    {
        bufferRail.deleteBuffers();
    }

    void translate(glm::vec3 translation)
    {
        rail.translate(translation);
        updateBuffers();
    }

    void rotate(float alpha, float theta, float gamma)
    {
        rail.rotate(alpha, theta, gamma);
        updateBuffers();
    }

    void scale(glm::vec3 scale)
    {
        rail.scale(scale);
        updateBuffers();
    }


    Cylinder rail { 16, glm::vec3(1, 0, 0)};

    GLBuffers bufferRail;
};




int main(int argc, char** argv) 
{

    // Initialize SDL and open a window
    float width  = 1920;
    float height = 1080;
    SDLWindowManager windowManager(width, height, "Bielle");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);    

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Objects
    Bielle bielle {width/height, applicationPath};
    Hangar hangar {width/height};
    Test test {};

    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), width/height, .1f, 1000.f);
    glm::mat4 MVMatrix;
    glm::mat4 NormalMatrix;


    // VBO & VAO
    bielle.updateBuffers();
    hangar.updateBuffers();
    test.updateBuffers();


    // Camera
    FreeflyCamera camera {};
    SDLKey kmove = SDLK_a;
    SDLKey kdir  = SDLK_a;

    // Bielle Rotation
    int rotationAngle = 0;
    int stepAngle = 1;
    bool rotateBielle = false;

    // Light
    glUniform3fv(bielle.program.uLightPos_vs    , 1, glm::value_ptr(glm::vec3(0,0,0)));
    glUniform3fv(bielle.program.uKd             , 1, glm::value_ptr(glm::vec3(255,255,255)));
    glUniform3fv(bielle.program.uKs             , 1, glm::value_ptr(glm::vec3(255,255,255)));
    glUniform3fv(bielle.program.uLightIntensity , 1, glm::value_ptr(glm::vec3(255,255,255)));
    glUniform1f (bielle.program.uShininess      , 60);

    // Application loop:
    bool done = false;
    while(!done) {
        bielle.update_bielle(rotationAngle);
        // Rotation 180 deg.
        /*if (rotationAngle == +90) stepAngle = -1;
        if (rotationAngle == -90) stepAngle = +1;
        rotationAngle += stepAngle;*/
        // Rotation 360 deg.
        if (rotateBielle) {
            //rotationAngle = rotationAngle % 360 == 0 ? stepAngle : rotationAngle + stepAngle;
            rotationAngle += stepAngle;
            rotationAngle = rotationAngle > 360 ? rotationAngle - 360 : rotationAngle;
        }

        // SDL KEYBOARD & MOUSE MANAGMENT:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            } else if (e.type == SDL_KEYDOWN) {
                kmove = e.key.keysym.sym;
            } else if (e.type == SDL_KEYUP) {
                kmove = SDLK_a;
            } 
        }

        if (kmove == SDLK_ESCAPE) {
            done = true;
        } 
        if (kmove == SDLK_z) { //std::cout << "mov up" << std::endl;
            camera.moveFront(+.1);
        } 
        if (kmove == SDLK_s) { //std::cout << "mov down" << std::endl;
            camera.moveFront(-.1);
        } 
        if (kmove == SDLK_q) { //std::cout << "mov left" << std::endl;
            camera.moveLeft(+.1);
        } 
        if (kmove == SDLK_d) { //std::cout << "mov right" << std::endl;
            camera.moveLeft(-.1);
        } 
        if (kmove == SDLK_e) {
            rotateBielle = rotateBielle == true ? false : true;
        } 
        if (kmove == SDLK_r) {
            stepAngle = stepAngle >= 10 ? 10 : ++stepAngle;
        }
        if (kmove == SDLK_f) {
            stepAngle = stepAngle <= 1 ? 1 : --stepAngle;
        }
        SDL_Delay(60); // delay to avoid key override

        int x, y;
        SDL_PumpEvents();  // make sure we have the latest mouse state.
        SDL_GetMouseState(&x, &y);
        //std::cout << "mouse tracking : " << x << "," << y << std::endl;
        float paddingX = width / 10.;
        float paddingY = height / 10.;
        if (x < paddingX) { //std::cout << "rot left" << std::endl;
            camera.rotateLeft(+1.);
        } else if (x > width - paddingX) { //std::cout << "rot right" << std::endl;
            camera.rotateLeft(-1.);
        }
        if (y < paddingY) { //std::cout << "rot up" << std::endl;
            camera.rotateUp(+1.);
        } else if (y > height - paddingY) { //std::cout << "rot down" << std::endl;
            camera.rotateUp(-1.);
        }


        // Light


        // GL DISPLAY
        glClearColor(.5,.5,.5,0.0);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        bielle.getCameraMatrix(camera.getViewMatrix());
        MVMatrix = camera.getViewMatrix();

        NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
        glUniformMatrix4fv(bielle.program.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
        glUniformMatrix4fv(bielle.program.uMVMatrix , 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(bielle.program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));

        hangar.drawVertices(bielle.program.uMVPMatrix, bielle.program.uMVMatrix, bielle.program.uNormalMatrix, bielle.program.uTexture);
        bielle.drawVertices();
        //test.drawVertices();

        // Update the display
        windowManager.swapBuffers();
    }

    bielle.deleteArbreBuffers();
    hangar.deleteArbreBuffers();
    test.deleteArbreBuffers();


    return EXIT_SUCCESS;
}
