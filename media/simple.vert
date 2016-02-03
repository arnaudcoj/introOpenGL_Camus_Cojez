#version 130
        
in vec3 position;
in vec4 color;
//Q26
in vec2 texCoord;

out vec4 fColor;
//Q26
out vec2 fTexCoord;

//Q24
uniform float coeff;

void main() {
    vec3 newPosition = position;
    //Q24
    //newPosition *= coeff;

    fColor = color;
    //Q26
    fTexCoord = texCoord;

    gl_Position = vec4(newPosition,1.0);
}
