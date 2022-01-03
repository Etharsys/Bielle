#version 300 es

precision mediump float;

layout(location = 0) in vec2 aVertexPosition;
layout(location = 1) in vec3 aVertexColor;

out vec3 vColor;

mat3 translate(float tx, float ty) {
    return mat3(vec3(1,0,0), vec3(0,1,0), vec3(tx,ty,1));
}

mat3 scale(float sx, float sy) {
    return mat3(vec3(sx,0,0), vec3(0,sy,0), vec3(0,0,1));
}

mat3 rotate(float a) {
    float r = radians(a);
    return mat3(vec3(cos(r),sin(r),0), vec3(-sin(r),cos(r),0), vec3(0,0,1));
}

void main() {
    vColor = aVertexColor;
    //vec2  translate = vec2(0.5, 0.5);
    //float scale1    = 2.;
    //vec2  scale2    = vec2(2. , 0.5);

    mat3 M = translate(0.5, 0.) * rotate(45.) * scale(0.5, 0.5);

    gl_Position = vec4((M * vec3(aVertexPosition, 1)).xy, 0, 1);
}
