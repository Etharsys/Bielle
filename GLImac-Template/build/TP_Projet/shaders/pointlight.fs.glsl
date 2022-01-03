#version 300 es

precision mediump float;

in vec3 vPosition_vs;
in vec3 vNormal_vs;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightPos_vs;
uniform vec3 uLightIntensity;

out vec3 fFragColor;

float dot_0(vec3 v1, vec3 v2) {
    float res = dot(v1,v2);
    return max(0., res);
}

vec3 blinnPhong() {
    vec3 wi = normalize(uLightPos_vs - vPosition_vs);
    vec3 N  = normalize(vNormal_vs);
    float d = distance(vPosition_vs, uLightPos_vs);
    vec3 Li = uLightIntensity / (d * d);
    vec3 halfVector = normalize((normalize(-vPosition_vs) + wi) / 2.);
    return Li * (uKd * dot_0(wi,N) + uKs * pow(dot_0(halfVector,N),uShininess));
}

void main() {
    fFragColor = blinnPhong();
}
