#pragma once

#include "BielleCommon.hpp"


#include "Cube.hpp"
#include "Cylinder.hpp"
#include "GLbuffers.hpp"



struct Arbre
{
    Arbre()
        : cube1 { }, cube2 { }, cyl { 16, glm::vec3(0,0,1) }
    { 
        genArbre();
    }

    void genArbre()
    {
        cube1.scale(glm::vec3(e, e, e));
        cube2.scale(glm::vec3(e, e, e));
        cyl.scale(glm::vec3(e/2., e/2., l));
        cyl.rotate(0, 90, 0);

        cube1.translate(glm::vec3(-l/2., 0, 0));
        cube2.translate(glm::vec3( l/2., 0, 0));
    }

    void updateBuffers()
    {
        bufferCube1.initVBO(cube1.nbVertices(), cube1.getDataPointer());
        bufferCube2.initVBO(cube2.nbVertices(), cube2.getDataPointer());
        bufferCyl.initVBO(cyl.getVertexCount(), cyl.getDataPointer());

        bufferCube1.initVAO();
        bufferCube2.initVAO();
        bufferCyl.initVAO();
    }

    void drawVertices()
    {
        bufferCube1.drawVertices();
        bufferCube2.drawVertices();
        bufferCyl.drawVertices();
    }

    void deleteArbreBuffers()
    {
        bufferCube1.deleteBuffers();
        bufferCube2.deleteBuffers();
        bufferCyl.deleteBuffers();
    }

    void translate(glm::vec3 translation)
    {
        cube1.translate(translation);
        cube2.translate(translation);
        cyl.translate(translation);
        updateBuffers();
    }

    void rotate(float alpha, float theta, float gamma)
    {
        cube1.rotate(alpha, theta, gamma);
        cube2.rotate(alpha, theta, gamma);
        cyl.rotate(alpha, theta, gamma);
        updateBuffers();
    }

    void scale(glm::vec3 scale)
    {
        cube1.scale(scale);
        cube2.scale(scale);
        cyl.scale(scale);
        updateBuffers();
    }

    Cube cube1;
    Cube cube2;
    Cylinder cyl;
 
    GLBuffers bufferCube1;
    GLBuffers bufferCube2;
    GLBuffers bufferCyl;
};