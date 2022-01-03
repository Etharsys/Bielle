#pragma once

#include "BielleCommon.hpp"



struct Vertex2DColor
{
    Vertex2DColor ()
        : position { glm::vec4{.0f, .0f, .0f, .1f} }, 
            color  { glm::vec3{0.0f, 0.0f, 0.0f} }
    { }

    Vertex2DColor (glm::vec4 _position, glm::vec3 _color, glm::vec4 _normal)
        : position { _position }, color { _color }, normal { _normal }
    { }

    Vertex2DColor (glm::vec4 _position, glm::vec3 _color, glm::vec4 _normal, glm::vec2 _texCoords)
        : position { _position }, color { _color }, normal { _normal }, texCoords { _texCoords }
    { }

    void translate(glm::vec3 translation)
    {
        position = glm::translate(glm::mat4(1), translation) * position;

        normal = glm::translate(glm::mat4(1), translation) * normal;
    }

    void rotate(float alpha, float theta, float gamma)
    {
        position = glm::rotate(glm::mat4(1), glm::radians(alpha), glm::vec3(1,0,0)) * position;
        position = glm::rotate(glm::mat4(1), glm::radians(theta), glm::vec3(0,1,0)) * position;
        position = glm::rotate(glm::mat4(1), glm::radians(gamma), glm::vec3(0,0,1)) * position;

        normal = glm::rotate(glm::mat4(1), glm::radians(alpha), glm::vec3(1,0,0)) * normal;
        normal = glm::rotate(glm::mat4(1), glm::radians(theta), glm::vec3(0,1,0)) * normal;
        normal = glm::rotate(glm::mat4(1), glm::radians(gamma), glm::vec3(0,0,1)) * normal;
    }

    void scale(glm::vec3 scale)
    {
        position = glm::scale(glm::mat4(1), scale) * position;

        normal = glm::scale(glm::mat4(1), scale) * normal;
    }


    glm::vec4 position;
    glm::vec3 color;
    glm::vec4 normal;
    glm::vec2 texCoords;
};