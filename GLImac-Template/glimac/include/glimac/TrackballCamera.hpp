#pragma once

#include <math.h>

#include "common.hpp"

class TrackballCamera {

    float m_fDistance;
    float m_fAngleX;
    float m_fAngleY;

    public:
        TrackballCamera()
            : m_fDistance { 5. }, m_fAngleX { 0. }, m_fAngleY { 0. }
        { }

        // move front (or back if delta < 0) the camera
        void moveFront(float delta)
        {
            //std::cout << "Moving front by " << delta << std::endl;
            m_fDistance += delta;
        }

        // camera rotation on axe X
        void rotateLeft(float degrees)
        {
            m_fAngleY += degrees;
        }

        // camera rotation on axe Y
        void rotateUp(float degrees)
        {
            m_fAngleX += degrees;
        }

        glm::mat4 getViewMatrix() const
        {
            float radX = M_PI * m_fAngleX / 180;
            float radY = M_PI * m_fAngleY / 180;

            glm::mat4 mat = glm::translate(glm::mat4(1), glm::vec3(0,0,-m_fDistance));
            mat = glm::rotate(mat, radX, glm::vec3(1,0,0));
            mat = glm::rotate(mat, radY, glm::vec3(0,1,0));

            return mat;
        }
};