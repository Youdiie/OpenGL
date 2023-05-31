#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    //Normal = aNormal;
    Normal = mat3(transpose(inverse(model))) * aNormal; // 모델 행렬을 이용해 법선 벡터를 변환
    FragPos = vec3(model * vec4(aPos, 1.0)); // 정점 데이터를 모델 행렬과 곱해 정점의 월드 좌표를 얻음
    TexCoords = aTexCoords;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}