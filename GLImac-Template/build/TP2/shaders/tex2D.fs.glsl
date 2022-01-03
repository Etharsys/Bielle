#version 300 es

precision mediump float;

in vec3 vColor;
in vec2 vTex;

out vec3 fFragColor;

uniform sampler2D uTexture;

void main() {
    fFragColor = texture(uTexture, vTex).xyz;
}
