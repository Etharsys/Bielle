#pragma once

#include "BielleCommon.hpp"


#include "Cube.hpp"
#include "GLbuffers.hpp"



struct Hangar
{
    Hangar(float _windowRatio)
        : windowRatio { _windowRatio }
    {
        hangar.scale(glm::vec3(20, 20, 20));
        loadTexture();
    }

    void updateBuffers()
    {
        bufferHangar.initVBO(hangar.nbVertices(), hangar.getDataPointer());
        //for (auto v : hangar._vertices)
        //    cout << v.position << endl;

        bufferHangar.initVAO();
    }

    void drawVertices(GLuint uMVPMatrix, GLuint uMVMatrix, GLuint uNormalMatrix, GLuint uTexture)
    {
        glBindTexture(GL_TEXTURE_2D, texHangar);
            glUniform1i(uTexture, 0);

            glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), windowRatio, .1f, 1000.f);
            glm::mat4 MVMatrix = glm::mat4(1.);
            glm::mat4 NormalMatrix = glm::mat4(1.);
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            MVMatrix = cameraMatrix * MVMatrix;
            //std::cout << ProjMatrix << std::endl;
            //glUniformMatrix4fv(uMVPMatrix   , 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
            glUniformMatrix4fv(uMVMatrix    , 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            bufferHangar.drawVertices();

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void loadTexture()
    {
        auto texture = glimac::loadImage("../../assets/textures/hangar2.jpg");
        if (texture == NULL)
        {
            std::cerr << "Cannot load texture" << std::endl;
            return;
        }

        glGenTextures(1, &texHangar);
        glBindTexture(GL_TEXTURE_2D, texHangar);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.get()->getWidth(), 
                texture.get()->getHeight(), 0, GL_RGBA, GL_FLOAT, texture.get()->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void getCameraMatrix(glm::mat4 mat)
    {
        cameraMatrix = mat;
    }

    void deleteArbreBuffers()
    {
        bufferHangar.deleteBuffers();
    }

    void translate(glm::vec3 translation)
    {
        hangar.translate(translation);
        updateBuffers();
    }

    void rotate(float alpha, float theta, float gamma)
    {
        hangar.rotate(alpha, theta, gamma);
        updateBuffers();
    }

    void scale(glm::vec3 scale)
    {
        hangar.scale(scale);
        updateBuffers();
    }


    Cube hangar;

    GLBuffers bufferHangar;

    glm::mat4 cameraMatrix;
    float windowRatio;

    GLuint texHangar;
};
