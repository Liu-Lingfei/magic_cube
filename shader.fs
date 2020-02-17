#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2D texture3;
uniform sampler2D texture4;
uniform sampler2D texture5;

uniform int index;

void main() {
    switch (index) {
        case 0:
            FragColor = texture(texture0, TexCoord);
            break;
        case 1:
            FragColor = texture(texture1, TexCoord);
            break;
        case 2:
            FragColor = texture(texture2, TexCoord);
            break;
        case 3:
            FragColor = texture(texture3, TexCoord);
            break;
        case 4:
            FragColor = texture(texture4, TexCoord);
            break;
        case 5:
            FragColor = texture(texture5, TexCoord);
            break;
    }
}