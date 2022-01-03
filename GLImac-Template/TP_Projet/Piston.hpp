#pragma once

#include "BielleCommon.hpp"


#include "Cube.hpp"
#include "GLbuffers.hpp"


struct Piston
{
    Piston()
    {
        gen_piston();
    }

    void gen_piston()
    {
        middle.scale(glm::vec3(2*e, 2*e, e));
        rail1.scale(glm::vec3(2*e, e/4., 3*e));
        rail2.scale(glm::vec3(2*e, e/4., 3*e));

        rail1.translate(glm::vec3(0, -(e+e/8.), 0));
        rail2.translate(glm::vec3(0, +(e+e/8.), 0));
    }

    void updateBuffers()
    {
        bufferMiddle.initVBO(middle.nbVertices(), middle.getDataPointer());
        bufferRail1.initVBO(rail1.nbVertices(), rail1.getDataPointer());
        bufferRail2.initVBO(rail2.nbVertices(), rail2.getDataPointer());

        bufferMiddle.initVAO();
        bufferRail1.initVAO();
        bufferRail2.initVAO();
    }

    void drawVertices()
    {
        bufferMiddle.drawVertices();
        bufferRail1.drawVertices();
        bufferRail2.drawVertices();
    }

    void deleteArbreBuffers()
    {
        bufferMiddle.deleteBuffers();
        bufferRail1.deleteBuffers();
        bufferRail2.deleteBuffers();
    }

    void translate(glm::vec3 translation)
    {
        middle.translate(translation);
        rail1.translate(translation);
        rail2.translate(translation);
        updateBuffers();
    }

    void rotate(float alpha, float theta, float gamma)
    {
        middle.rotate(alpha, theta, gamma);
        rail1.rotate(alpha, theta, gamma);
        rail2.rotate(alpha, theta, gamma);
        updateBuffers();
    }

    void scale(glm::vec3 scale)
    {
        middle.scale(scale);
        rail1.scale(scale);
        rail2.scale(scale);
        updateBuffers();
    }

    Cube middle;
    Cube rail1;
    Cube rail2;

    GLBuffers bufferMiddle;
    GLBuffers bufferRail1;
    GLBuffers bufferRail2;
};