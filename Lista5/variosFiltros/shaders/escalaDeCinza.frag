#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture sampler
uniform sampler2D ourTexture1;

void main()
{
    color = texture(ourTexture1, TexCoord);// * vec4(ourColor, 1.0);
    //Escala de cinza com média ponderada
    float average = color.r * 0.2125 + color.g * 0.7154 + color.b * 0.0721;
    color = vec4(average, average, average, 1);
}
