#version 130

in vec4 fColor;
in vec2 fTexCoord;

out vec4 fragColor;

uniform sampler2D texture;
uniform float coeff;

void main() {
    //fragColor = fColor;
    //fragColor = texture2D(texture,fTexCoord);
    // rouge de la texture multiplié par le rouge de fColor, idem pour green, et blue.
    //fragColor=texture2D(texture,fTexCoord)*fColor; // fColor étant la couleur interpolée aux sommets(questions précédentes)

    fragColor=texture2D(texture,fTexCoord)*fColor.b;
    fragColor.g*=(1.0-coeff);
}
