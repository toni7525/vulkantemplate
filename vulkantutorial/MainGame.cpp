#include "Application.h"
#include "CommandBuffer.h"
#include "VertexBuffer.h"
#include "UniformBuffer.h"

float x = 0, y = 0, z = 0;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_A && action == GLFW_PRESS)
		x += 0.1f;
	if (key == GLFW_KEY_D && action == GLFW_PRESS)
		x -= 0.1f;
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
		y += 0.1f;
	if (key == GLFW_KEY_S && action == GLFW_PRESS)
		y -= 0.1f;
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		z += 0.1f;
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
		z -= 0.1f;
}

void Application::mainLoop()
{
	const std::string filepathVert = "shaders/vert.spv";
	const std::string filepathFrag = "shaders/frag.spv";

	Shader vert(filepathVert, &device);
	Shader frag(filepathFrag, &device);
	Pipeline pipeline(&vert, &frag, &device, &renderPass);	
	UniformBuffer uniformBuffer(this,&pipeline);
	VertexBuffer vertexBuffer(this);
	CommandBuffer commandBuffer(this, &pipeline,&vertexBuffer,&uniformBuffer);
	float w = 0;
	while (!glfwWindowShouldClose(window) ){
		glfwSetKeyCallback(window, key_callback);
		w += 0.0004f;
		if (w > 3.14)w = 0;
		glfwPollEvents();
		uniformBuffer.updatexyz(x, y, z);
		commandBuffer.drawFrame();	
		glfwSetWindowPos(window, (int)(sin(w)*1700), 100);
	}
	vkDeviceWaitIdle(device);
}



