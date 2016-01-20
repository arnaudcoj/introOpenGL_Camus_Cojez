#version 130
        
in vec3 position;
in vec4 color;
uniform float coeff;

out vec4 fColor;
        
void main() {
    vec3 newPosition = position;
    newPosition *= coeff;

    fColor = color;
    gl_Position = vec4(newPosition,1.0);
}
