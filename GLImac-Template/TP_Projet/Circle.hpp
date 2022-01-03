#pragma once

#include "BielleCommon.hpp"

#include "Vector2DColor.hpp"


struct Circle
{
    Circle (int nbSide, glm::vec3 color)
        : _nbSide { nbSide }, _color { color }
    {
        gen_circle();
    }

    void gen_circle()
    {
        float theta = 0.;
        int radius = .5;
        glm::vec4 normal = glm::vec4(0, 0, .5, 1);
        for ( u_int n = 0; n < _nbSide; ++n )
        {
            _vertices.emplace_back(glm::vec4(0.,0.,0.,1.), _color, normal);
            _vertices.emplace_back(glm::vec4(0.5 * glm::cos<float>(theta), 0.5 * glm::sin<float>(theta), 0., 1.), _color, normal);
            theta += glm::pi<float>() * 2 / _nbSide;
            _vertices.emplace_back(glm::vec4(0.5 * glm::cos<float>(theta), 0.5 * glm::sin<float>(theta), 0., 1.), _color, normal);
        }
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

    int _nbSide;
    glm::vec3 _color;
    std::vector<Vertex2DColor> _vertices;
};