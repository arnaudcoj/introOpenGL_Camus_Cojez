#version 130

in vec4 fColor;
in vec2 fTexCoord;

out vec4 fragColor;

uniform sampler2D texture;

void main() {
    fragColor = texture2D(texture,fTexCoord);
}
