#include <GLFW/glfw3.h>
#include <glad\glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
#include "Shader\Shader.h"
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\projection.hpp>
#include "Camera/EulerCamera.h"
#include <memory>
#include "Shapes/cube.h"
#include "model.h"

using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
// camera
EulerCamera* Cam;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float angle = 0.3; 
void framebuffer_size_callback(GLFWwindow* window, int width, int height); 
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void initialize_data();
void initialize_geometery();
void handel_cam(int key);

Shader* shader_obj;

struct attenuation {
	float constant;
	float linear;
	float quadratic;
};

attenuation light_attenuations_list[] = {
	 1.0, 0.0014, 0.000007
	
	, 1.0, 0.007, 0.0002
	
	, 1.0, 0.014, 0.0007
	
	, 1.0, 0.022, 0.0019
	
	, 1.0, 0.027, 0.0028
	
	, 1.0, 0.045, 0.0075
	
	, 1.0, 0.07, 0.017
	
	, 1.0, 0.09, 0.032
	
	, 1.0, 0.14, 0.07
	
	, 1.0, 0.22, 0.20
	
	, 1.0, 0.35, 0.44
	
	, 1.0, 0.7, 1.8
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	////////////////

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);

	////////////////

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, 800, 600);

	///////////////

	//shader_obj = new Shader("Resources/shaders/VertexShader.vs", "Resources/shaders/FragmentShader.fs");
	//Shader ourShader("Resources/shaders/model_loading.vs", "Resources/shaders/model_loading.fs");
	Shader shader("Resources/shaders/Model_light.vs", "Resources/shaders/Model_light.fs");
	Cam = new EulerCamera();

	glm::vec3 light_pos(10.0f, 10.0f, 0.0f);
	Cube light_source(0.1,light_pos);
	Cube cubey(0.9, glm::vec3(0, 0, 0));
	////////////////////////

	Model ourModel("Resources/objects/nanosuit/nanosuit.obj");
	// Model ourModel("Resources/objects/rifle/rifle.obj");


	/////////////
	////////////////////////
	// get matrix's uniform location and set matrix
	shader.use();
	shader.setVec3("light.position", Cam->GetEyePosition());
	shader.setVec3("light.direction", Cam->GetLookDirection());

	shader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
	shader.setVec3("light.diffuse", 1.0f, 1.0f, 1.0f);
	shader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

	shader.setFloat("light.constant", light_attenuations_list[4].constant);
	shader.setFloat("light.linear", light_attenuations_list[4].linear);
	shader.setFloat("light.quadratic", light_attenuations_list[4].quadratic);

	shader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));

	shader.setFloat("material.shininess", 32.0f);
	
	glm::vec3 light_source_color(1.0f, 1.0f, 1.0f);

	///////////////
	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  60.0f),
		glm::vec3(2.0f,  0.0f, -15.0f),
		glm::vec3(-15.5f, -0.0f, -7.5f),
		glm::vec3(-8.8f, -0.0f, -20.3f),
		glm::vec3(24.4f, -0.0f, -13.5f),
		glm::vec3(-6.7f,  0.0f, -7.5f),
		glm::vec3(15.3f, -0.0f, -40.5f),
		glm::vec3(7.5f,  0.0f, -25.5f),
		glm::vec3(13.5f,  0.0f, -15.5f),
		glm::vec3(-9.3f,  0.0f, -26.5f)
	};
	while (!glfwWindowShouldClose(window))
	{
		//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); //greeny
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		/////////////////
		shader.use();
		// view/projection transformations
		glm::mat4 view = Cam->GetProjectionMatrix() * Cam->GetViewMatrix();
		shader.setMat4("view", view);
		shader.setVec3("eyePos", Cam->GetEyePosition());
		shader.setVec3("light.position", Cam->GetEyePosition());
		shader.setVec3("light.direction", Cam->GetLookDirection());
		///////////// render the loaded model

		
		for (int i = 0; i < 10; i++)
		{
			glm::mat4 translate = glm::translate(glm::mat4(1), cubePositions[i]);
			 // translate it down so it's at the center of the scene
			glm::mat4 scale = glm::scale(glm::mat4(1), glm::vec3(0.02f));
			float angle1 = 50.0f * i;
			glm::mat4 rotate = glm::rotate(glm::mat4(1), glm::radians(angle1)*(float)glfwGetTime(), glm::vec3(0, 1, 0));
			glm::mat4 model = scale * translate * rotate;
			shader.setMat4("model", model);
			ourModel.Draw(&shader);
		}

		////////////
		//cubey.draw(&shader, view, light_source_color);
		light_source.draw(&shader, view, light_source_color);

		////////////
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return -1;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;// reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.01;
	xoffset *= sensitivity;
	yoffset *= sensitivity;
	Cam->Yaw(xoffset);
	Cam->Pitch(yoffset);
	Cam->UpdateViewMatrix();
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

	//camera.ProcessMouseScroll(yoffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{	
	//handel_cube()
	handel_cam(key);
	switch (key) {
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
			break;
		default:
			break;
		}
}
void handel_cam(int key)
{
	switch (key) {
	case GLFW_KEY_LEFT:
		Cam->Strafe(-0.1);
		cout << "hi left" << endl;
		break;
	case GLFW_KEY_RIGHT:
		Cam->Strafe(0.1);
		cout << "hi right" << endl;
		break;

	case GLFW_KEY_UP:
		Cam->Walk(0.1);
		cout << "hi left" << endl;
		break;
	case GLFW_KEY_DOWN:
		Cam->Walk(-0.1);
		cout << "hi right" << endl;
		break;
	case GLFW_KEY_W:
		Cam->Fly(0.1);
		cout << "hi left" << endl;
		break;
	case GLFW_KEY_S:
		Cam->Fly(-0.1);

		cout << "hi right" << endl;
		break;

	case GLFW_KEY_T:
		Cam->Roll(angle);
		cout << "Roll" << endl;
		break;
	case GLFW_KEY_Y:
		Cam->Roll(-angle);
		cout << "Roll" << endl;
		break;

	case GLFW_KEY_1:
		Cam->Pitch(angle);
		cout << "hi left" << endl;
		break;
	case GLFW_KEY_2:
		Cam->Pitch(-angle);
		cout << "hi right" << endl;
		break;

	case GLFW_KEY_3:
		Cam->Yaw(angle);
		cout << "hi left" << endl;
		break;
	case GLFW_KEY_4:
		Cam->Yaw(-angle);
		cout << "hi right" << endl;
		break;

	case GLFW_KEY_0:
		Cam->Reset(0, 0, 0, 0, 0, -1, 0, 1, 0);
		cout << "Reseting" << endl;
		break;
	default:
		break;
	}

	Cam->UpdateViewMatrix();
}
void handel_cube(Cube* cube, int key)
{
	switch (key) {
	case GLFW_KEY_LEFT:
		Cam->Strafe(-0.1);
		cout << "hi left" << endl;
		break;
	case GLFW_KEY_RIGHT:
		Cam->Strafe(0.1);
		cout << "hi right" << endl;
		break;

	case GLFW_KEY_UP:
		Cam->Walk(0.1);
		cout << "hi left" << endl;
		break;
	case GLFW_KEY_DOWN:
		Cam->Walk(-0.1);
		cout << "hi right" << endl;
		break;
	case GLFW_KEY_W:
		Cam->Fly(0.1);
		cout << "hi left" << endl;
		break;
	case GLFW_KEY_S:
		Cam->Fly(-0.1);

		cout << "hi right" << endl;
		break;
	}
}
/*
void initialize_data()
{

	float depth = 1;
	float unit = 0.4f;
	// [TODO] 1) create the data array (stored in RAM)
	float vertices[] =
	{
		-unit, unit, -unit,		0.0f, 0.1f, 0.0f,	1.0f, 1.0f, //0
		
		-unit, -unit, -unit,	0.0f, 1.0f, 1.0f,	1.0f, 0.0f,//1 2
		
		 unit, unit, -unit,		1.0f, 1.0f, 0.0f ,	0.0f, 0.0f,//2 4
		
		unit, -unit, -unit,		0.1f, 0.0f, 0.1f ,	0.0f, 1.0f, //3 6
		
		-unit, unit, unit,		1.0f, 0.0f, 0.0f ,	1.0f, 1.0f, //4 8	

		-unit, -unit, unit,		0.0f, 0.0f, 1.0f ,	1.0f, 0.0f,	//5 10		

		unit, unit, unit,		1.0f, 1.0f, 1.0f ,	0.0f, 0.0f,//6 12		

		unit, -unit, unit,		0.0f, 0.0f, 0.0f ,	0.0f, 1.0f,//7 14
		

	};

	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	//	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	//};
	//unsigned int indices[] = {
	//	0, 1, 3, // first triangle
	//	1, 2, 3  // second triangle
	//};
	int indices[] = { 0,1,2,1,2,3,0,1,4,1,4,5,2,3,6,6,7,3,3,7,1,1,5,7,6,7,4,4,5,7,0,4,2,2,6,4 };

	unsigned int  EBO, VBO;
	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
   // glBindVertexArray(0);

	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
										   // set the texture wrapping parameters

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;
		unsigned char *data = stbi_load("Resources/textures/wall.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} 
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}*/
void initialize_geometery()
{
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
	shader_obj->setMat4("transform", trans);
}
/*
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/projection.hpp>

#include "Shader/Shader.h"
#include "Camera/EulerCamera.h"
#include "model.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader ourShader("model_loading.vs", "model_loading.fs");

    // load models
    // -----------
    Model ourModel("Resources/objects/nanosuit/nanosuit.obj");

    
    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model;
       // model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f));	// it's a bit too big for our scene, so scale it down
        ourShader.setMat4("model", model);
        ourModel.Draw(ourShader);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}*/