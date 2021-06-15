#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

// Texture sampler
uniform sampler2D ourTexture1;

void main()
{
    color = texture(ourTexture1, TexCoord);// * vec4(ourColor, 1.0);
    //Efeito amarelo queimado
    color = vec4(color.r, color.g * 0, color.b, 1);
}
