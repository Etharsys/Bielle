#version 300 es

precision mediump float;

layout(location = 0) in vec4 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;
layout(location = 2) in vec4 aVertexNormal;
layout(location = 3) in vec2 aVertexTexCoords;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vColor;
out vec3 vNormal;
out vec2 vTexCoords;
out vec3 vPosition;

void main() {  
    vColor = aVertexColor;
    vNormal = vec3(uNormalMatrix * aVertexNormal);
    vTexCoords = aVertexTexCoords;
    vPosition = vec3(uMVMatrix * aVertexPosition);

    gl_Position = uMVPMatrix * aVertexPosition;
}
