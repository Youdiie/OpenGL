#version 330 core
out vec4 FragColor;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{   
    // ambient
    vec3 ambient = material.ambient * light.ambient;
    
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos); // 빛과 fragment 사이의 방향 벡터
    float diff = max(dot(norm, lightDir), 0.0); // 빛과 fragment 사이의 각도
    vec3 diffuse = material.diffuse * diff * light.diffuse;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos); // 뷰어와 fragment 사이의 방향 벡터
    vec3 reflectDir = reflect(-lightDir, norm); // 빛이 반사되는 방향 벡터(빛의 방향 벡터를 normal 벡터에 대칭)
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // 반사된 빛과 뷰어 사이의 각도에 shiness를 적용
    vec3 specular = material.specular * spec * light.specular;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}