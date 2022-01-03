#version 300 es

precision mediump float;

in vec3 vColor;

out vec3 fFragColor;

void main() {
    float average = (vColor[0] + vColor[1] + vColor[2]) / 3.;
    fFragColor = vec3(average, average, average);
}
