#version 300 es

precision mediump float;

in vec3 vColor;
in vec2 vPos;

out vec3 fFragColor;

int N = 100;

vec2 complexSqr(vec2 z) {
    float x = z[0] * z[0] - z[1] * z[1];
    float y = 2. * z[0] * z[1];
    z[0] = x;
    z[1] = y;
    return z;
}

vec3 zn(vec2 c, int n) {
    vec2 znCur = c;
    if (sqrt(znCur[0] * znCur[0] + znCur[1] * znCur[1]) > 2.) {
        return vec3(1.,1.,1.);
    }
    for (int n = 0; n <= N; ++n) {
        vec2 znInc = complexSqr(znCur) + c;
        znCur = znInc;
        if (sqrt(znCur[0] * znCur[0] + znCur[1] * znCur[1]) > 2.) {
            return vec3(1.,1.,1.);
        }
    }
    return vec3(0.,0.,0.);
}

void main() {
    fFragColor = zn(vPos * 2., N);
}
