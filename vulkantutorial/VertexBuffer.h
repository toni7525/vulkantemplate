#pragma once
#include "Application.h"
#include <glm/glm.hpp>
#include <array>
//vec2 positions[3] = vec2[](
//vec2(0.0, -0.5),
//vec2(0.5, 0.5),
//vec2(-0.5, 0.5)
//);
//
//vec3 colors[3] = vec3[](
//vec3(1.0, 1.0, 0.2),
//vec3(1.0, 0.5, 0.1),
//vec3(1.0, 0.5, 0.1)
//);
struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};
const std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f,0.0f}, {1.0f, 0.0f, 0.0f}},
    {{0.5f , -0.5f,0.0f}, {0.0f, 1.0f, 0.0f}},
    {{0.5f , 0.5f ,0.0f}, {0.0f, 0.0f, 1.0f}},
    {{-0.5f, 0.5f ,0.0f}, {1.0f, 1.0f, 1.0f}}
};

class VertexBuffer{
public:
    
    VertexBuffer(Application* App);
    ~VertexBuffer();
    
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0
    };
    VkBuffer Getindex();
private:
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    Application *mainApp;
    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
    void createIndexBuffer();
    void createVertexBuffer();
    uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
};

