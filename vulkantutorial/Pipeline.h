#pragma once
#include "Shader.h"
class Pipeline
{
	public:

	    Pipeline(Shader* vert, Shader* frag, VkDevice *device,VkRenderPass* renderPass);
	    ~Pipeline();
	    
		VkPipeline graphicsPipeline;
		VkDescriptorSetLayout descriptorSetLayout;
		VkPipelineLayout pipelineLayout;
    private:
		
		
		VkDevice* deviceptr;
		Shader* vertex;
		Shader* fragment;
		void createDescriptorSetLayout();
		void createGraphicsPipeline(VkRenderPass* renderPass);
};

