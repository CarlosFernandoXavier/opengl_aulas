#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform vec3 modifier;

// Texture sampler
uniform sampler2D ourTexture1;

void main()
{
    color = texture(ourTexture1, TexCoord);// * vec4(ourColor, 1.0);
    //Adição de uma nova cor na minha imagem (colorização)
    color = vec4(color.r + modifier.r, color.g + modifier.g, color.b + modifier.b, 1);
}
