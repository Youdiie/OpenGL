#version 330 core
out vec4 FragColor;

uniform vec3 lightColor;

void main()
{
    // FragColor = vec4(1.0); // set all 4 vector values to 1.0
    // FragColor = vec4(1.0, 0.5, 0.2, 1.0); // change the color of light
    FragColor = vec4(lightColor, 1.0); // set the color of light to a uniform
}