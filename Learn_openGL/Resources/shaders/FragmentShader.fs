
#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 texCoord;
in vec3 fragPos;
in vec3 normal;

uniform sampler2D ourTexture;
uniform vec3 eyePos;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; 
uniform Material material;

struct Light {
    vec3 position;
	vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

vec3 calculate_light()
{
	vec3 ambient = light.ambient * material.ambient;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	vec3 diffuse = max(dot(norm, lightDir), 0.0) * light.diffuse * material.diffuse;

	float specularStrength = 1;
	vec3 eyeDir = normalize(eyePos - fragPos);
	vec3 reflectLight = reflect(-lightDir, norm);
	float spec = pow(max(dot(eyeDir, reflectLight), 0.0) , material.shininess);
	vec3 specular = material.specular * light.specular * spec;

	vec3 fragLight = (specular + diffuse + ambient) * light.color;
	return fragLight;
}

void main()
{
	FragColor = vec4(calculate_light(), 1.0);
	//FragColor = texture(ourTexture, TexCoord);
} 