#include "Application.h"
#include "CommandBuffer.h"
#include "VertexBuffer.h"
#include "UniformBuffer.h"
#include "Texture.h"
#include <chrono>
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

float zoom = 0;
float deltatime = 0;
const float movespeed = 0.001f , movedecrease=0.1f;
bool paused = false;
bool nextframe = false;
glm::vec3 ppos = {0,-2,-1};
glm::vec3 move;
glm::vec2 lookangle;

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	zoom += yoffset;
}
bool input[10];
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
	switch (action) {
	case GLFW_PRESS:
		switch (key) {
		case GLFW_KEY_A:input[0] = true;
			break;
		case GLFW_KEY_D:input[1] = true;
			break;
		case GLFW_KEY_S:input[2] = true;
			break;
		case GLFW_KEY_W:input[3] = true;
			break;
		case GLFW_KEY_LEFT_CONTROL:input[4] = true;
			break;
		case GLFW_KEY_LEFT_SHIFT:input[5] = true;
			break;
		}
		break;
	case GLFW_RELEASE:
		switch (key) {
		case GLFW_KEY_A:input[0] = false;
			break;
		case GLFW_KEY_D:input[1] = false;
			break;
		case GLFW_KEY_S:input[2] = false;
			break;
		case GLFW_KEY_W:input[3] = false;
			break;
		case GLFW_KEY_LEFT_CONTROL:input[4] = false;
			break;
		case GLFW_KEY_LEFT_SHIFT:input[5] = false;
			break;
		}
		break;
	}
	
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		paused = !paused;
	if (key == GLFW_KEY_RIGHT)
		nextframe = true;
}
void UpdateMove() {
	
	move += glm::vec3{
		(int)(input[0]) - (int)(input[1]) ,
		(int)(input[2]) - (int)(input[3]) ,
		(int)(input[4]) - (int)(input[5])
	};

	if (abs(move.x) > 3)move.x = 3 * move.x / abs(move.x);
	if (abs(move.y) > 3)move.y = 3 * move.y / abs(move.y);
	if (abs(move.z) > 3)move.z = 3 * move.z / abs(move.z);

	ppos += glm::vec3{
		move.y * cos(lookangle.x) - move.x * cos(lookangle.x + 3.14f / 2),
		move.y * sin(lookangle.x) - move.x * sin(lookangle.x + 3.14f / 2) ,
	    move.z
	} *movespeed * deltatime;

	abs(move.x) <= 0.2 ? move.x = 0 : move.x -= movedecrease * deltatime * move.x / abs(move.x);
	abs(move.y) <= 0.2 ? move.y = 0 : move.y -= movedecrease * deltatime * move.y / abs(move.y);
	abs(move.z) <= 0.2 ? move.z = 0 : move.z -= movedecrease * deltatime * move.z / abs(move.z);
}
#define DEBUG 0

void Application::mainLoop()
{
	const std::string filepathVert = "shaders/vert.spv";
	const std::string filepathFrag = "shaders/frag.spv";
	const std::string filepathTexture = "textures/octav.jpg";
	Shader vert(filepathVert, &device);
	Shader frag(filepathFrag, &device);
	Pipeline pipeline(&vert, &frag, &device, &renderPass);
	Texture texture(this, filepathTexture);	
	UniformBuffer uniformBuffer(this,&pipeline,&texture);
	VertexBuffer vertexBuffer(this);
	CommandBuffer commandBuffer(this, &pipeline,&vertexBuffer,&uniformBuffer);
	recreateSwapChain();
	float w = 0, fps = 0, avragefps = 0, fpscount = 0,time=0;
	int framecount = 0;
	float rotxspeed = 0.01f,rotyspeed = 0.01f;
	double lastxpos = 0 , lastypos = 0,xpos =0 , ypos =0;

	while (!glfwWindowShouldClose(window)){

		
		glfwGetCursorPos(window, &xpos, &ypos);
		lookangle += glm::vec2(
			(float)(lastxpos - xpos)* rotxspeed,
			(float)(lastypos - ypos)* rotyspeed
		);
		lookangle.x >= 360 ? lookangle.x - 360: 0;
		lookangle.y >= 360 ? lookangle.y - 360: 0;
		lastxpos = xpos;
		lastypos = ypos;
		auto startTime = std::chrono::high_resolution_clock::now();
		glm::vec3 lookdir(cos(lookangle.x), sin(lookangle.x), lookangle.y);
		if (DEBUG) {
			system("CLS");

			std::cout << "x:" << ppos.x << std::endl << "  y:" << ppos.y << std::endl << "  z:" << ppos.z << std::endl << "cos:" << cos(lookangle.x) << std::endl << "  sin:" << sin(lookangle.x) << std::endl;
			if ((int)time > 2000) {
				avragefps = fpscount / framecount;
				fpscount = 0;
				framecount = 0;
				time = 0;
				glfwSetWindowTitle(window, ("avrage fps:" + std::to_string((int)avragefps)).c_str());

			}
			else {
				fps = 1000 / deltatime;
				fpscount += fps;
			}
		
		}
		else {
			if ((int)time > 2000) {
				avragefps = fpscount / framecount;
				fpscount = 0;
				framecount = 0;
				time = 0;
				glfwSetWindowTitle(window, ("avrage fps:" + std::to_string((int)avragefps)).c_str());

			}
			else {
				fps = 1000 / deltatime;
				fpscount += fps;
			}
			
		}

		glfwSetScrollCallback(window, scroll_callback);
		glfwSetKeyCallback(window, key_callback);
		UpdateMove();
		w += 0.0004f;
		if (w > 3.14)w = 0;
		glfwPollEvents();
		uniformBuffer.updatexyz(ppos,lookdir, deltatime, zoom);
		if (!paused || nextframe) {
			nextframe = false;
			commandBuffer.drawFrame();
			++framecount;
			time += deltatime;
		}
		//glfwSetWindowPos(window, (int)(sin(w)*1700), 100);
		
		auto currentTime = std::chrono::high_resolution_clock::now();
		deltatime = std::chrono::duration<float, std::chrono::milliseconds::period>(currentTime - startTime).count();
	}
	vkDeviceWaitIdle(device);
}



