#pragma once
#include "Application.h"
#include "Texture.h"
#include "Pipeline.h"
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
struct UniformBufferObject {
    alignas(16) glm::mat4 model;
    alignas(16) glm::mat4 view;
    alignas(16) glm::mat4 proj;
    alignas(4) glm::vec4 ppos;

};



class UniformBuffer
{
public:
    UniformBuffer(Application* App, Pipeline* pipelinein,Texture* intexture);
    ~UniformBuffer();
    std::vector<VkDescriptorSet> descriptorSets;
    void updateUniformBuffer(uint32_t currentImage);
    void updatexyz(glm::vec3 pposin, glm::vec3 lookdirin, float timein,float zoomin);
private:
    float time = 0,zoom;
    glm::vec3 ppos, lookdir;
    Texture* texture;
    Pipeline* pipeline;
    Application* mainApp;

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<void*> uniformBuffersMapped;   

    void createUniformBuffers();
    void createDescriptorSets();

};

