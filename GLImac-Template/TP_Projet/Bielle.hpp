#pragma once

#include "BielleCommon.hpp"


#include "Arbre.hpp"
#include "Piston.hpp"
#include "Bras.hpp"
#include "Rail.hpp"
#include "BielleProgram.hpp"





struct Bielle
{
    Bielle(float _windowRatio, glimac::FilePath appPath)
        : windowRatio { _windowRatio }, program { appPath }
    {
        program.m_Program.use();
        loadTexture();
        gen_bielle();
    }

    void gen_bielle()
    {
        arbre.translate(glm::vec3(arbrePostionOnRail, 0, 2*e));
        piston.translate(glm::vec3(pistonPositionOnRail, 0, e));
        //rail.translate(glm::vec3(0, 0, 0));
        bras.translate(glm::vec3(brasPositionOnRail, 0, e));
    }

    void update_bielle(float rotationAngle)
    {
        _rotationAngle = rotationAngle;
    }

    void updateBuffers()
    {
        //arbre.updateBuffers();
        //piston.updateBuffers();
        rail.updateBuffers();
        bras.updateBuffers();
    }

    float calculateArbreDistance(float alpha)
    {
        float height = d * sin(alpha);
        float theta = acos(height / l);
        float hb = sin(theta) * l;
        float obdist = d * cos(alpha) + hb; // canonique position of B 
        //cout << "angle : " << alpha << " | height : " << height << " | hb : " << hb << endl;
        return obdist; // on bielle position of B
    }

    float calculateArbreRotation(float alpha)
    {
        float height = d * sin(alpha);
        //cout << "angle : " << alpha << " | height : " << height << endl;
        return asin(height / l); // rotation from B
    }

    void drawVertices()
    {
        glBindTexture(GL_TEXTURE_2D, texBielle);
            glUniform1i(program.uTexture, 0);

            // ARBRE
            //arbre.translate(glm::vec3(arbrePostionOnRail, 0, 2*e));
            float arbreDist = calculateArbreDistance(glm::radians(_rotationAngle));
            //cout << arbreDist << endl;
            float arbreRot  = calculateArbreRotation(glm::radians(_rotationAngle));
            glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), windowRatio, .1f, 1000.f);
            glm::mat4 MVMatrix = glm::mat4(1.);
            glm::mat4 NormalMatrix;
            MVMatrix     = glm::translate(glm::mat4(1.), glm::vec3(-arbrePostionOnRail - l/2 - e, 0, 0));
            MVMatrix     = glm::translate(MVMatrix, glm::vec3(arbreDist, 0, 0)); 
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            MVMatrix     = glm::rotate(MVMatrix, -arbreRot, glm::vec3(0,0,1)); 
            MVMatrix     = glm::translate(MVMatrix, glm::vec3(-arbrePostionOnRail-l/2, 0, 0)); 
            MVMatrix = cameraMatrix * MVMatrix;
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            glUniformMatrix4fv(program.uMVPMatrix   , 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
            glUniformMatrix4fv(program.uMVMatrix    , 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            arbre.drawVertices();

            // PISTON
            ProjMatrix = glm::perspective(glm::radians(70.f), windowRatio, .1f, 1000.f);
            MVMatrix = glm::mat4(1.);
            NormalMatrix = glm::mat4(1.);
            MVMatrix     = glm::translate(glm::mat4(1.), glm::vec3(-2*arbrePostionOnRail - l - e, 0, 0));
            MVMatrix     = glm::translate(MVMatrix, glm::vec3(arbreDist, 0, 0)); 
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            MVMatrix = cameraMatrix * MVMatrix;
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            glUniformMatrix4fv(program.uMVPMatrix   , 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
            glUniformMatrix4fv(program.uMVMatrix    , 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            piston.drawVertices();

            // RAIL
            ProjMatrix = glm::perspective(glm::radians(70.f), windowRatio, .1f, 1000.f);
            MVMatrix = glm::mat4(1.);
            NormalMatrix = glm::mat4(1.);
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            MVMatrix = cameraMatrix * MVMatrix;
            glUniformMatrix4fv(program.uMVPMatrix   , 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
            glUniformMatrix4fv(program.uMVMatrix    , 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            rail.drawVertices();

            // BRAS
            ProjMatrix   = glm::perspective(glm::radians(70.f), windowRatio, .1f, 1000.f);
            MVMatrix     = glm::translate(glm::mat4(1.), glm::vec3(brasPositionOnRail - e/2, 0, 0));
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            MVMatrix     = glm::rotate(MVMatrix, glm::radians(_rotationAngle), glm::vec3(0,0,1)); 
            MVMatrix     = glm::translate(MVMatrix, glm::vec3(-brasPositionOnRail + e/2, 0, 0)); 
            MVMatrix = cameraMatrix * MVMatrix;
            NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
            glUniformMatrix4fv(program.uMVPMatrix   , 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
            glUniformMatrix4fv(program.uMVMatrix    , 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(program.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
            bras.drawVertices();
        
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void getCameraMatrix(glm::mat4 mat)
    {
        cameraMatrix = mat;
    }

    void deleteArbreBuffers()
    {
        arbre.deleteArbreBuffers();
        piston.deleteArbreBuffers();
        rail.deleteArbreBuffers();
        bras.deleteArbreBuffers();
        glDeleteTextures(1, &texBielle);
    }

    void translate(glm::vec3 translation)
    {
        arbre.translate(translation);
        piston.translate(translation);
        rail.translate(translation);
        bras.translate(translation);
        updateBuffers();
    }

    void rotate(float alpha, float theta, float gamma)
    {
        arbre.rotate(alpha, theta, gamma);
        piston.rotate(alpha, theta, gamma);
        rail.rotate(alpha, theta, gamma);
        bras.rotate(alpha, theta, gamma);
        updateBuffers();
    }

    void scale(glm::vec3 scale)
    {
        arbre.scale(scale);
        piston.scale(scale);
        rail.scale(scale);
        bras.scale(scale);
        updateBuffers();
    }


    void loadTexture()
    {
        auto texMetal = glimac::loadImage("../../assets/textures/metal3.jpg");
        if (texMetal == NULL)
        {
            std::cerr << "Cannot load texture" << std::endl;
            return;
        }

        glGenTextures(1, &texBielle);
        glBindTexture(GL_TEXTURE_2D, texBielle);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texMetal.get()->getWidth(), 
                texMetal.get()->getHeight(), 0, GL_RGBA, GL_FLOAT, texMetal.get()->getPixels());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glBindTexture(GL_TEXTURE_2D, 0);
    }


    Arbre arbre;
    Piston piston;
    Rail rail;
    Bras bras;

    float windowRatio;
    BielleProgram program;

    glm::mat4 cameraMatrix;

    float pistonPositionOnRail = (l+d)/2 - e/2;
    float brasPositionOnRail   = -(l+d)/2;
    float arbrePostionOnRail   = d/2 - e/2;

    float _rotationAngle = 0;

    GLuint texBielle;
};