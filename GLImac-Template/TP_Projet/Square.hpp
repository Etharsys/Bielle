#pragma once

#include "BielleCommon.hpp"

#include "Vector2DColor.hpp"



struct Square
{
    Square(glm::vec3 color)
        : _color { color }
    {
        gen_square();
    }

    void gen_square()
    {
        glm::vec4 normal = glm::vec4(0, 0, .5, 1);
        _vertices.emplace_back(glm::vec4(-.5, +.5, 0, 1), _color, normal, glm::vec2(-.5, +.5));
        _vertices.emplace_back(glm::vec4(+.5, +.5, 0, 1), _color, normal, glm::vec2(+.5, +.5));
        _vertices.emplace_back(glm::vec4(-.5, -.5, 0, 1), _color, normal, glm::vec2(-.5, -.5));
        _vertices.emplace_back(glm::vec4(+.5, +.5, 0, 1), _color, normal, glm::vec2(+.5, +.5));
        _vertices.emplace_back(glm::vec4(-.5, -.5, 0, 1), _color, normal, glm::vec2(-.5, -.5));
        _vertices.emplace_back(glm::vec4(+.5, -.5, 0, 1), _color, normal, glm::vec2(+.5, -.5));
    }

    void translate(glm::vec3 translation)
    {
        for (Vertex2DColor& vertex : _vertices)
        {
            vertex.translate(translation);
        }
    }

    void rotate(float alpha, float theta, float gamma)
    {
        for (Vertex2DColor& vertex : _vertices)
        {
            vertex.rotate(alpha, theta, gamma);
        }
    }

    void scale(glm::vec3 scale)
    {
        for (Vertex2DColor& vertex : _vertices)
        {
            vertex.scale(scale);
        }
    }

    const Vertex2DColor* getDataPointer() const 
    {
        return &_vertices[0];
    }

    glm::vec3 _color;
    std::vector<Vertex2DColor> _vertices;
};