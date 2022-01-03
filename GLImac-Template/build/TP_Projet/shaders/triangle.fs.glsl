#version 300 es

precision mediump float;

in vec3 vColor;
in vec3 vNormal;
in vec2 vTexCoords;
in vec3 vPosition;

uniform sampler2D uTexture;

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
    vec3 wi = normalize(uLightPos_vs - vPosition);
    vec3 N  = normalize(vNormal);
    float d = distance(vPosition, uLightPos_vs);
    vec3 Li = uLightIntensity / (d * d);
    vec3 halfVector = normalize((normalize(-vPosition) + wi) / 2.);
    return Li * (uKd * dot_0(wi,N) + uKs * pow(dot_0(halfVector,N),uShininess));
}

void main() {
    //fFragColor = blinnPhong() + texture(uTexture, vTexCoords).xyz;
    fFragColor = texture(uTexture, vTexCoords).xyz;
}
