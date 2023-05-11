#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

void main()
{   
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos); // 빛과 fragment 사이의 방향 벡터
    float diff = max(dot(norm, lightDir), 0.0); // 빛과 fragment 사이의 각도
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos); // 뷰어와 fragment 사이의 방향 벡터
    vec3 reflectDir = reflect(-lightDir, norm); // 빛이 반사되는 방향 벡터(빛의 방향 벡터를 normal 벡터에 대칭)
    int shiness = 32;
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shiness); // 반사된 빛과 뷰어 사이의 각도에 shiness를 적용
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}