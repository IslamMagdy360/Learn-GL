
#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;
in vec3 fragPos;
in vec3 normal;

uniform vec3 eyePos;

struct Material {
    sampler2D diffuse1;
    sampler2D specular1;    
    float shininess;
}; 

uniform Material material;

struct Light {
    vec3 position;
	vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	//forpointLight
    float constant;
    float linear;
    float quadratic;
	// 
	float cutOff;

};
uniform Light light;

vec3 calculate_PointLight();
vec3 calculate_FlashLight();
vec3 calculate_DireactionalLight();

void main()
{ 
	FragColor = vec4(calculate_FlashLight(), 1.0);
	//FragColor = texture(ourTexture, TexCoord);
} 

vec3 calculate_DireactionalLight()
{
	vec3 ambient = light.ambient * texture(material.diffuse1, TexCoords).rgb;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(-light.direction); //directional light
	vec3 diffuse = max(dot(norm, lightDir), 0.0) * light.diffuse * texture(material.diffuse1, TexCoords).rgb;

	vec3 eyeDir = normalize(eyePos - fragPos);
	vec3 reflectLight = reflect(-lightDir, norm);
	float spec = pow(max(dot(eyeDir, reflectLight), 0.0) , material.shininess);
	vec3 specular =  light.specular * spec * texture(material.specular1, TexCoords).rgb;
	
	vec3 fragLight = specular + diffuse + ambient;

	return fragLight;
}
vec3 calculate_PointLight()
{

	float distance    = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

	vec3 ambient = light.ambient * texture(material.diffuse1, TexCoords).rgb;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(light.position - fragPos);
	//vec3 lightDir = normalize(-light.direction); //directional light
	vec3 diffuse = max(dot(norm, lightDir), 0.0) * light.diffuse * texture(material.diffuse1, TexCoords).rgb;

	
	vec3 eyeDir = normalize(eyePos - fragPos);
	vec3 reflectLight = reflect(-lightDir, norm);
	float spec = pow(max(dot(eyeDir, reflectLight), 0.0) , material.shininess);
	vec3 specular =  light.specular * spec * texture(material.specular1, TexCoords).rgb;
	vec3 fragLight =  attenuation * (specular + diffuse + ambient);
	return fragLight;
}


vec3 calculate_FlashLight()
{

	vec3 lightDir = normalize(light.position - fragPos);
	float theta = dot(lightDir,normalize(-light.direction));
	vec3 ambient = light.ambient * texture(material.diffuse1, TexCoords).rgb;
	if(theta > light.cutOff )
	{
		vec3 norm = normalize(normal);
		//vec3 lightDir = normalize(-light.direction); //directional light
		vec3 diffuse = max(dot(norm, lightDir), 0.0) * light.diffuse * texture(material.diffuse1, TexCoords).rgb;

		
		vec3 eyeDir = normalize(eyePos - fragPos);
		vec3 reflectLight = reflect(-lightDir, norm);
		float spec = pow(max(dot(eyeDir, reflectLight), 0.0) , material.shininess);
		vec3 specular =  light.specular * spec * texture(material.specular1, TexCoords).rgb;
		
		
		float distance    = length(light.position - fragPos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 

		vec3 fragLight =  (attenuation * (specular + diffuse)) + ambient;
		return fragLight;
	}
	else
	 return ambient;
	
}

