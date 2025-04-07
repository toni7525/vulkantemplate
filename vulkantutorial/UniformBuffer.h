#pragma once
#include "Application.h"
#include "Pipeline.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
};



class UniformBuffer
{
public:
    UniformBuffer(Application* App, Pipeline* pipelinein);
    ~UniformBuffer();
    std::vector<VkDescriptorSet> descriptorSets;
    void updateUniformBuffer(uint32_t currentImage);
    void updatexyz(float xin,float yin, float zin);
private:
    float x = 0, y = 0, z = 0;
    


    Pipeline* pipeline;
    Application* mainApp;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;
    
    

    void createUniformBuffers();
    void createDescriptorSets();

    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};

