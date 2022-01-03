#pragma once

#include "BielleCommon.hpp"

#include "Vector2DColor.hpp"



struct GLBuffers
{
    void initVBO (int _verticesCount, Vertex2DColor* ptr)
    {
        verticesCount = _verticesCount;

        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(Vertex2DColor), ptr, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void initVAO ()
    {
        constexpr GLuint VERTEX_ATTR_POSITION  = 0;
        constexpr GLuint VERTEX_ATTR_COLOR     = 1;
        constexpr GLuint VERTEX_ATTR_NORMAL    = 2;
        constexpr GLuint VERTEX_ATTR_TEXCOORDS = 3;

        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);

                glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
                glVertexAttribPointer(VERTEX_ATTR_POSITION, 4, GL_FLOAT, GL_FALSE, 
                    sizeof(Vertex2DColor), (const GLvoid*) offsetof(Vertex2DColor, position));
                
                glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
                glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, 
                    sizeof(Vertex2DColor), (const GLvoid*) offsetof(Vertex2DColor, color));

                glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
                glVertexAttribPointer(VERTEX_ATTR_COLOR, 4, GL_FLOAT, GL_FALSE, 
                    sizeof(Vertex2DColor), (const GLvoid*) offsetof(Vertex2DColor, normal));
            
                glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORDS);
                glVertexAttribPointer(VERTEX_ATTR_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 
                    sizeof(Vertex2DColor), (const GLvoid*) offsetof(Vertex2DColor, texCoords));

            glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);
    }

    void drawVertices()
    {
        glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, verticesCount);
        glBindVertexArray(0);
    }

    void deleteBuffers()
    {
        glDeleteBuffers(1, &vbo);
        glDeleteVertexArrays(1, &vao);
    }

    GLuint vao;
    GLuint vbo;
    int verticesCount;
};