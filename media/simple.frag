#version 130

in vec4 fColor;
//Q26
in vec2 fTexCoord;

out vec4 fragColor;

//Q26
uniform sampler2D texture;
uniform float coeff;

void main() {
    //fragColor = fColor;

    //Q26
    //fragColor = texture2D(texture,fTexCoord);

    //Q32
    // rouge de la texture multiplié par le rouge de fColor, idem pour green, et blue.
    //fragColor=texture2D(texture,fTexCoord)*fColor; // fColor étant la couleur interpolée aux sommets(questions précédentes)

    //Q33
    fragColor=texture2D(texture,fTexCoord)*fColor.b;
    fragColor.g*=(1.0-coeff);
}
