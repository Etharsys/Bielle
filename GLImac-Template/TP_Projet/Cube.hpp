#pragma once

#include "BielleCommon.hpp"

#include "Square.hpp"
#include "Vector2DColor.hpp"


struct Cube
{
    Cube() :
        _face1 { glm::vec3(1,0,0) }, _face2 { glm::vec3(0,1,0) },
        _face3 { glm::vec3(0,0,1) }, _face4 { glm::vec3(1,1,0) },
        _face5 { glm::vec3(0,1,1) }, _face6 { glm::vec3(1,0,1) }
    {
        gen_cube();
    }

    void gen_cube()
    {
        _face1.translate(glm::vec3(0.,0.,-.5));

        _face2.rotate(90,0,0);
        _face2.translate(glm::vec3(0.,.5,0.));
        
        _face3.rotate(-90,0,0);
        _face3.translate(glm::vec3(0.,-.5,0.));
        
        _face4.translate(glm::vec3(0.,0.,.5));
        
        _face5.rotate(0,90,0);
        _face5.translate(glm::vec3(.5,0.,0.));

        _face6.rotate(0,90,0);
        _face6.translate(glm::vec3(-.5,0.,0.));
    }

    void translate(glm::vec3 translation)
    {
        _face1.translate(translation); _face2.translate(translation);
        _face3.translate(translation); _face4.translate(translation);
        _face5.translate(translation); _face6.translate(translation);
    }

    void rotate(float alpha, float theta, float gamma)
    {
        _face1.rotate(alpha, theta, gamma); _face2.rotate(alpha, theta, gamma);
        _face3.rotate(alpha, theta, gamma); _face4.rotate(alpha, theta, gamma);
        _face5.rotate(alpha, theta, gamma); _face6.rotate(alpha, theta, gamma);
    }

    void scale(glm::vec3 scale)
    {
        _face1.scale(scale); _face2.scale(scale);
        _face3.scale(scale); _face4.scale(scale);
        _face5.scale(scale); _face6.scale(scale);
    }

    Vertex2DColor* getDataPointer() 
    {
        for (int i = 0; i < _face1._vertices.size(); i++)
        {
            _vertices[0+i]  = _face1._vertices[i];
            _vertices[6+i]  = _face2._vertices[i];
            _vertices[12+i] = _face3._vertices[i];
            _vertices[18+i] = _face4._vertices[i];
            _vertices[24+i] = _face5._vertices[i];
            _vertices[30+i] = _face6._vertices[i];
        }
        return &_vertices[0];
    }

    const u_int nbVertices() const
    {
        return 6 * _face1._vertices.size();
    }

    Square _face1;
    Square _face2;
    Square _face3;
    Square _face4;
    Square _face5;
    Square _face6;

    std::vector<Vertex2DColor> _vertices { nbVertices() };
};