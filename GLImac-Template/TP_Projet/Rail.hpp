#pragma once

#include "BielleCommon.hpp"


#include "Cube.hpp"
#include "GLbuffers.hpp"



struct Rail
{
    Rail()
    {
        gen_piston();
    }

    void gen_piston()
    {
        rail.scale(glm::vec3(l+d+2*e, 2*e, e));
    }

    void updateBuffers()
    {
        bufferRail.initVBO(rail.nbVertices(), rail.getDataPointer());

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


    Cube rail;

    GLBuffers bufferRail;
};