#pragma once

#include "BielleCommon.hpp"


#include "Cube.hpp"
#include "GLbuffers.hpp"
#include "Cylinder.hpp"



struct Bras
{
    Bras()
        : base {}, bras {}, edge {16, glm::vec3(0,1,0)}, axe {16, glm::vec3(0,1,0)}, attach {16, glm::vec3(0,1,0)}
    {
        gen_piston();
    }

    void gen_piston()
    {
        base.scale(glm::vec3(d/2., d/2., 2*e));
        bras.scale(glm::vec3(d/2. + d, 2*e, e));
        edge.scale(glm::vec3(2*e, 2*e, e));
        axe.scale(glm::vec3(e, e, e));
        attach.scale(glm::vec3(e, e, e));

        base.translate(glm::vec3(-d/2. - d/4. - e/2., 0, e/2));
        bras.translate(glm::vec3(3*d/4 - (d/2 + e/2), 0, 0));
        edge.translate(glm::vec3(d - e/2, 0, 0));
        axe.translate(glm::vec3(-e/2., 0, e/2.));
        attach.translate(glm::vec3(d - e/2., 0, e/2.));
    }

    void updateBuffers()
    {
        bufferBase.initVBO(base.nbVertices(), base.getDataPointer());
        bufferBras.initVBO(bras.nbVertices(), bras.getDataPointer());
        bufferEdge.initVBO(edge.getVertexCount(), edge.getDataPointer());
        bufferAxe.initVBO(axe.getVertexCount(), axe.getDataPointer());
        bufferAttach.initVBO(attach.getVertexCount(), attach.getDataPointer());

        bufferBase.initVAO();
        bufferBras.initVAO();
        bufferEdge.initVAO();
        bufferAxe.initVAO();
        bufferAttach.initVAO();
    }

    void drawVertices()
    {
        bufferBase.drawVertices();
        bufferBras.drawVertices();
        bufferEdge.drawVertices();
        bufferAxe.drawVertices();
        bufferAttach.drawVertices();
    }

    void deleteArbreBuffers()
    {
        bufferBase.deleteBuffers();
        bufferBras.deleteBuffers();
        bufferEdge.deleteBuffers();
        bufferAxe.deleteBuffers();
        bufferAttach.deleteBuffers();
    }

    void translate(glm::vec3 translation)
    {
        base.translate(translation);
        bras.translate(translation);
        edge.translate(translation);
        axe.translate(translation);
        attach.translate(translation);
        updateBuffers();
    }

    void rotate(float alpha, float theta, float gamma)
    {
        base.rotate(alpha, theta, gamma);
        bras.rotate(alpha, theta, gamma);
        edge.rotate(alpha, theta, gamma);
        axe.rotate(alpha, theta, gamma);
        attach.rotate(alpha, theta, gamma);
        updateBuffers();
    }

    void scale(glm::vec3 scale)
    {
        base.scale(scale);
        bras.scale(scale);
        edge.scale(scale);
        axe.scale(scale);
        attach.scale(scale);
        updateBuffers();
    }

    Cube base;
    Cube bras;
    Cylinder edge;
    Cylinder axe;
    Cylinder attach;

    GLBuffers bufferBase;
    GLBuffers bufferBras;
    GLBuffers bufferEdge;
    GLBuffers bufferAxe;
    GLBuffers bufferAttach;
};