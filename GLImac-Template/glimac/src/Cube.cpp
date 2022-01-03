#include <cmath>
#include <vector>
#include <iostream>
#include "glimac/common.hpp"
#include "glimac/Cube.hpp"

namespace glimac {

void Cube::build(GLsizei size) {
    // 8 vertex for a cube
    m_nVertexCount = 8;

    GLfloat halfsize = size / 2.;

    std::vector<ShapeVertex> data;

    ShapeVertex vertex;

    vertex.texCoords.x = -halfsize;
    vertex.texCoords.y = -halfsize;
    data.push_back(vertex);
}

}
