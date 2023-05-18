#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    // vec3 specular;
    sampler2D specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 direction; // directional light
    float cutoff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{   
    // vec3 lightDir = normalize(light.position - FragPos);

    // if (theta > light.cutoff) // cosine 값이기 때문에 > 일때가 범위 내
    // {
    // ambient
    vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos); // 빛과 fragment 사이의 방향 벡터
    // vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0); // 빛과 fragment 사이의 각도
    // vec3 diffuse = material.diffuse * diff * light.diffuse;
    vec3 diffuse = vec3(texture(material.diffuse, TexCoords)) * diff * light.diffuse;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos); // 뷰어와 fragment 사이의 방향 벡터
    vec3 reflectDir = reflect(-lightDir, norm); // 빛이 반사되는 방향 벡터(빛의 방향 벡터를 normal 벡터에 대칭)
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); // 반사된 빛과 뷰어 사이의 각도에 shiness를 적용
    vec3 specular = vec3(texture(material.specular, TexCoords)) * spec * light.specular;

    // spotlight (soft edges)
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutoff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    diffuse *= intensity;
    specular *= intensity;
    
    // attenuation
    float distance = length(light.position - FragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 result = (ambient + diffuse + specular) * attenuation;
    FragColor = vec4(result, 1.0);
    // }
    // else
    // {
    //     // else, use ambitent light so scene isn't completely dark outside the spotlight.
    //     FragColor = vec4(vec3(texture(material.diffuse, TexCoords)) * light.ambient, 1.0);
    // }
    
    
}