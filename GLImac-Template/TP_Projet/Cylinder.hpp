#pragma once

#include "BielleCommon.hpp"

#include "Vector2DColor.hpp"
#include "Circle.hpp"


struct Cylinder
{
    Cylinder (int nbSide, glm::vec3 color)
        : _nbSide { nbSide }, _color { color },
          _circle1 { nbSide, color }, _circle2 { _nbSide, _color }
    {
        gen_cylinder();
    }

    void gen_cylinder()
    {
        _circle1.translate(glm::vec3(.0,.0,.5));
        _circle2.translate(glm::vec3(.0,.0,-.5));

        for (int i = 0; i < _circle1._vertices.size(); i++)
        {
            int step = 0;
            _vertices[0+i] = _circle1._vertices[i];
            step += _circle1._vertices.size();
            _vertices[step+i] = _circle2._vertices[i];
        }
        for (int i = 0; i < _nbSide; i++)
        {
            int offset = 2 * _circle1._vertices.size();
            _vertices[offset+i*6  ] = _circle1._vertices[i*3+1];
            _vertices[offset+i*6+1] = _circle2._vertices[i*3+1];
            _vertices[offset+i*6+2] = _circle2._vertices[i*3+2];
            _vertices[offset+i*6+3] = _circle1._vertices[i*3+1];
            _vertices[offset+i*6+4] = _circle1._vertices[i*3+2];
            _vertices[offset+i*6+5] = _circle2._vertices[i*3+2];
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


    Vertex2DColor* getDataPointer() 
    {
        return &_vertices[0];
    }

    const u_int getVertexCount() const
    {
        return 2 * _circle1._vertices.size() + 6 * _nbSide;// + _nbSide * _sideSquares.at(0)._vertices.size();
    }

    int _nbSide;
    glm::vec3 _color;

    //std::vector<Square> _sideSquares { _nbSide };
    Circle _circle1;
    Circle _circle2;

    std::vector<Vertex2DColor> _vertices { getVertexCount() };
};