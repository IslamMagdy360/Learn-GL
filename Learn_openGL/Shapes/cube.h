#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <GLFW/glfw3.h>

#include <glad\glad.h>

#include <..\Shader\Shader.h>

#include <iostream>
//#include "..\Texture_loader\stb_image.h"

class Cube {
 
	unsigned int VAO;
	
public:
	glm::mat4 model;
	Cube(float scale, glm::vec3 pos);
	void change_position(glm::vec3 new_pos);
	void init();
	void draw(Shader*shader,glm::mat4 view, glm::vec3 color);
	
};