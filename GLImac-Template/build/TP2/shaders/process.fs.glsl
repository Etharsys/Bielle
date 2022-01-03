#version 300 es

precision mediump float;

in vec3 vColor;
in vec2 vPos;

out vec3 fFragColor;

void main() {
    //fFragColor = length(fract(5.0 * vPos)) * vColor;
    //fFragColor = length(abs(fract(5.0 * vPos) * 2.0 - 1.0)) * vColor;
    //fFragColor = mod(floor(10.0 * vPos[0]) + floor(10.0 * vPos[1]), 2.0) * vColor;
    //fFragColor = smoothstep(0.3, 0.32, length(fract(5.0 * vPos) - 0.5)) * vColor;
    fFragColor = smoothstep(0.4, 0.5, max(abs(fract(8.0 * vPos[0] - 0.5 * mod(floor(8.0 * vPos[1]), 2.0)) - 0.5), abs(fract(8.0 * vPos[1]) - 0.5))) * vColor;
}
