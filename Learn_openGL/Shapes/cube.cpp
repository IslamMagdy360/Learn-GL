#include "cube.h"

using namespace glm;
using namespace std;
Cube::Cube(float size, vec3 pos)
{

	model = scale(mat4(1), vec3(size, size, size)) * translate(mat4(1), pos);
	init();
}
void Cube::change_position(glm::vec3 new_pos)
{
	model = model * translate(mat4(1), new_pos);
}
void Cube::init()
{
		// [TODO] 1) create the data array (stored in RAM)
		float vertices[] = {	
			//vert						//norm				//color				//coord
			-0.5f, -0.5f, -0.5f,	  0.0f,  0.0f, -1.0f,	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,	0.0f, 1.0f, 0.0f,	 1.0f, 0.0f,
			0.5f,  0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,	0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
			0.5f,  0.5f, -0.5f,		 0.0f,  0.0f, -1.0f,	0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,	  0.0f,  0.0f, -1.0f,	1.0f, 1.0f, 0.0f,	 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,	  0.0f,  0.0f, -1.0f,	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
																				
			-0.5f, -0.5f,  0.5f,	  0.0f,  0.0f,  1.0f,	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
			0.5f, -0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,	0.0f, 1.0f, 0.0f,	 1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,	0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,		 0.0f,  0.0f,  1.0f,	0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,	  0.0f,  0.0f,  1.0f,	1.0f, 1.0f, 0.0f,	 0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,	  0.0f,  0.0f,  1.0f,	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
																				
			-0.5f,  0.5f,  0.5f,	 -1.0f,  0.0f,  0.0f,	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,	 -1.0f,  0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	 1.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,	 -1.0f,  0.0f,  0.0f,	0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,	 -1.0f,  0.0f,  0.0f,	0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,	 -1.0f,  0.0f,  0.0f,	1.0f, 1.0f, 0.0f,	 0.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,	 -1.0f,  0.0f,  0.0f,	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
																				
			0.5f,  0.5f,  0.5f,		 1.0f,  0.0f,  0.0f,	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
			0.5f,  0.5f, -0.5f,		 1.0f,  0.0f,  0.0f,	0.0f, 1.0f, 0.0f,	 1.0f, 0.0f,
			0.5f, -0.5f, -0.5f,		 1.0f,  0.0f,  0.0f,	0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
			0.5f, -0.5f, -0.5f,		 1.0f,  0.0f,  0.0f,	0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,		 1.0f,  0.0f,  0.0f,	1.0f, 1.0f, 0.0f,	 0.0f, 1.0f,
			0.5f,  0.5f,  0.5f,		 1.0f,  0.0f,  0.0f,	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
																				
			-0.5f, -0.5f, -0.5f,	  0.0f, -1.0f,  0.0f,	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
			0.5f, -0.5f, -0.5f,		 0.0f, -1.0f,  0.0f,	0.0f, 1.0f, 0.0f,	 1.0f, 0.0f,
			0.5f, -0.5f,  0.5f,		 0.0f, -1.0f,  0.0f,	0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
			0.5f, -0.5f,  0.5f,		 0.0f, -1.0f,  0.0f,	0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,	  0.0f, -1.0f,  0.0f,	1.0f, 1.0f, 0.0f,	 0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,	  0.0f, -1.0f,  0.0f,	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
																				
			-0.5f,  0.5f, -0.5f,	  0.0f,  1.0f,  0.0f,	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,
			0.5f,  0.5f, -0.5f,		 0.0f,  1.0f,  0.0f,	0.0f, 1.0f, 0.0f,	 1.0f, 0.0f,
			0.5f,  0.5f,  0.5f,		 0.0f,  1.0f,  0.0f,	0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
			0.5f,  0.5f,  0.5f,		 0.0f,  1.0f,  0.0f,	0.0f, 0.0f, 1.0f,	 1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,	  0.0f,  1.0f,  0.0f,	1.0f, 1.0f, 0.0f,	 0.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,	  0.0f,  1.0f,  0.0f,	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f
		};

		unsigned int  EBO, VBO;
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8 * sizeof(float)));
		glEnableVertexAttribArray(3);

		//unsigned int texture;
		//glGenTextures(1, &texture);
		//glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
		//									   // set the texture wrapping parameters

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//// set texture filtering parameters
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//int width, height, nrChannels;
		//unsigned char *data = stbi_load("Resources/textures/wall.jpg", &width, &height, &nrChannels, 0);
		//if (data)
		//{
		//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		//	glGenerateMipmap(GL_TEXTURE_2D);
		//}
		//else
		//{
		//	std::cout << "Failed to load texture" << std::endl;
		//}
		//stbi_image_free(data);
}
void Cube::draw(Shader* shader, glm::mat4 view, vec3 color)
{
	glm::mat4 mvp = view * model;
	shader->use();
	
	shader->setMat4("model", model);
	shader->setMat4("view", view);
	//glActiveTexture(GL_TEXTURE31);
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}