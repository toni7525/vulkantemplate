#pragma once
#include"Pipeline.h"
#include"Application.h"
#include "VertexBuffer.h"
#include "UniformBuffer.h"
class CommandBuffer
{
public:
	CommandBuffer(Application* app, Pipeline* graphicspipeline, VertexBuffer* vertexbufferin,UniformBuffer* UBI);
	~CommandBuffer();
	void drawFrame();
	
private:
	UniformBuffer* uniformBuffer;
	VertexBuffer* vertexBuffer;
	Application* mainapp;
	Pipeline* graphicsPipelineptr;
	
	std::vector<VkCommandBuffer> commandBuffers;
	
	void createCommandBuffer();
	void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
};

