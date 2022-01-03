#version 300 es

precision mediump float;

in vec3 vColor;
in vec2 vPos;

out vec3 fFragColor;

void main() {
    float dist  = distance(vec2(0.,0.), vPos);
    float alpha = 3.;
    float beta  = 50.;
    float halo  = alpha * exp(-beta * dist * dist);

    fFragColor = halo * vColor;
}
