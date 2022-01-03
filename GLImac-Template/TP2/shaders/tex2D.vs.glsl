#version 300 es

precision mediump float;

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec2 aVertexTexture;

out vec3 vColor;
out vec2 vTex;

uniform mat3 uModelMatrix;
uniform vec3 uColor;

void main() {
    vColor = uColor;
    vTex = aVertexTexture;

    gl_Position = vec4(
        (uModelMatrix * vec3(aVertexPosition, 1)).xy, 
        0, 1);
}
