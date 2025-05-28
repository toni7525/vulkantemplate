#include "UniformBuffer.h"

#include <iostream>
UniformBuffer::UniformBuffer(Application* App, Pipeline* pipelinein, Texture* intexture):mainApp(App),pipeline(pipelinein),texture(intexture)
{
   createUniformBuffers();
   createDescriptorSets();
}

UniformBuffer::~UniformBuffer()
{
	vkDestroyDescriptorPool(mainApp->device, mainApp->descriptorPool, nullptr);

}

void UniformBuffer::updateUniformBuffer(uint32_t currentImage)
{
    glm::dot(glm::vec3(1,1,1), glm::vec3(1,1,1));
    UniformBufferObject ubo{};  
    ubo.model = glm::mat4(1.0f);
    ubo.view = glm::mat4(1.0f);
    ubo.proj = glm::mat4(1.0f);
    ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(time / 100.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = glm::lookAt(glm::vec3(0, 0, 0), lookdir, glm::vec3(0.0f, 0.0f, 1.0f)) * glm::translate(glm::mat4(1), ppos);
    ubo.proj = glm::perspective(glm::radians(60.0f-zoom), mainApp->swapChainExtent.width / (float)(mainApp->swapChainExtent.height), 0.1f, 10.0f);
    ubo.proj[1][1] *= -1;

    //std::cout << x << " " << y + 1.1f <<" " << -3.0f + z << " " << std::endl;
    //glm::vec4 point1 = (ubo.view * ubo.model * glm::vec4(0.0f,0.0f, 0.0f, 1.0f));
    //glm::vec4 point2 = (ubo.view * ubo.model * glm::vec4(1.5f,1.5f, 0.0f, 1.0f));
    //std::cout << point.x << "  " << point.y << " " << point.z << "  " << mainApp->swapChainExtent.width / (float)(mainApp->swapChainExtent.height) << std::endl;
   // std::cout <<"first cube "<< point1.z <<" second cube  " << point2.z<<std::endl;
    memcpy(uniformBuffersMapped[currentImage], &ubo, sizeof(ubo));
}

void UniformBuffer::updatexyz(glm::vec3 pposin, glm::vec3 lookdirin, float timein, float zoomin){
    ppos = pposin;
    lookdir = lookdirin;
    time += timein;
    zoom = zoomin;
}

void UniformBuffer::createUniformBuffers()
{
    VkDeviceSize bufferSize = sizeof(UniformBufferObject);

    uniformBuffers.resize(mainApp->MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMemory.resize(mainApp->MAX_FRAMES_IN_FLIGHT);
    uniformBuffersMapped.resize(mainApp->MAX_FRAMES_IN_FLIGHT);

    for (size_t i = 0; i < mainApp->MAX_FRAMES_IN_FLIGHT; i++) {
        mainApp->createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);

        vkMapMemory(mainApp->device, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]);
    }
}

void UniformBuffer::createDescriptorSets()
{
    std::vector<VkDescriptorSetLayout> layouts(mainApp->MAX_FRAMES_IN_FLIGHT, pipeline->descriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = mainApp->descriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(mainApp->MAX_FRAMES_IN_FLIGHT);
    allocInfo.pSetLayouts = layouts.data();
   
    descriptorSets.resize(mainApp->MAX_FRAMES_IN_FLIGHT);
    if (vkAllocateDescriptorSets(mainApp->device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate descriptor sets!");
    }

    for (size_t i = 0; i < mainApp->MAX_FRAMES_IN_FLIGHT; i++) {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = uniformBuffers[i];
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UniformBufferObject);

        VkDescriptorImageInfo imageInfo{};
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageInfo.imageView = texture->textureImageView;
        imageInfo.sampler = texture->textureSampler;

        std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

        descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[0].dstSet = descriptorSets[i];
        descriptorWrites[0].dstBinding = 0;
        descriptorWrites[0].dstArrayElement = 0;
        descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrites[0].descriptorCount = 1;
        descriptorWrites[0].pBufferInfo = &bufferInfo;

        descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrites[1].dstSet = descriptorSets[i];
        descriptorWrites[1].dstBinding = 1;
        descriptorWrites[1].dstArrayElement = 0;
        descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptorWrites[1].descriptorCount = 1;
        descriptorWrites[1].pImageInfo = &imageInfo;

        vkUpdateDescriptorSets(mainApp->device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
    }
}
