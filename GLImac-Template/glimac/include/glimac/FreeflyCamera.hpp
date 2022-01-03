#pragma once

#include <math.h>
#include <cmath>

#include "common.hpp"

class FreeflyCamera {

    glm::vec3 m_Position;
    float m_fPhi;
    float m_fTheta;

    glm::vec3 m_FrontVector;
    glm::vec3 m_LeftVector;
    glm::vec3 m_UpVector;

    public:
        FreeflyCamera()
            : m_Position { glm::vec3(0,0,5) }, m_fPhi { M_PI }, m_fTheta { 0 }
        {
            computeDirectionVectors();
        }

        void computeDirectionVectors()
        {
            m_FrontVector = glm::vec3(cos(m_fTheta) * sin(m_fPhi), sin(m_fTheta), cos(m_fTheta) * cos(m_fPhi));
            m_LeftVector  = glm::vec3(sin(m_fPhi+M_PI/2), 0, cos(m_fPhi+M_PI/2));
            m_UpVector    = glm::cross(m_FrontVector, m_LeftVector);
        }

        void moveLeft(float t)
        {
            m_Position += t * m_LeftVector;
        }
        
        void moveFront(float t)
        {
            m_Position += t * m_FrontVector;
        }

        void rotateLeft(float degrees)
        {
            float rad = glm::radians(degrees);
            m_fPhi += rad;
            computeDirectionVectors();
        } 
        
        void rotateUp(float degrees)
        {
            float rad = glm::radians(degrees);
            m_fTheta += rad;
            computeDirectionVectors();
        }

        glm::mat4 getViewMatrix() const
        {
            auto v = m_Position + m_FrontVector;

            glm::mat4 mat = glm::lookAt(m_Position, v, m_UpVector);

            return mat;
        }
};