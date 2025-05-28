#pragma once
#include "Application.h"
#include <glm/glm.hpp>
#include <array>
// 
// vertex
// {{-0.5f, -0.5f,0.0f}, {1.0f, 0.0f, 0.0f}}, //front
//    {{0.5f, -0.5f, 0.0f}, { 0.0f, 1.0f, 0.0f }},
//    { {0.5f , 0.5f ,0.0f}, {0.0f, 0.0f, 1.0f} },
//    { {-0.5f, 0.5f ,0.0f}, {1.0f, 1.0f, 1.0f} }
// 
// index
// 0, 1, 2, 2, 3, 0//front

struct Vertex {
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec3 normal;
    glm::vec2 texCoord;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 4> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 4> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(Vertex, pos);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(Vertex, normal);

        attributeDescriptions[3].binding = 0;
        attributeDescriptions[3].location = 3;
        attributeDescriptions[3].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[3].offset = offsetof(Vertex, texCoord);

        return attributeDescriptions;
    }
};

const std::vector<Vertex> vertices = {
    //front
     {{-0.5f - 0.5f,-0.5f,-0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f, 0.0f,-1.0f }, {0.0f, 0.0f}}, //0
     {{0.5f - 0.5f,-0.5f,-0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f,-1.0f }, {1.0f, 0.0f}}, //1
     {{0.5f - 0.5f, 0.5f,-0.5f}, {0.0f, 0.0f, 1.0f}, { 0.0f, 0.0f,-1.0f }, {1.0f, 1.0f}}, //2
     {{-0.5f - 0.5f, 0.5f,-0.5f}, {1.0f, 1.0f, 1.0f}, { 0.0f, 0.0f,-1.0f }, {0.0f, 1.0f}}, //3
     //back
     {{-0.5f - 0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, { 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f}},//7
     {{0.5f - 0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, { 0.0f, 0.0f, 1.0f }, {1.0f, 1.0f}},//6
     {{0.5f - 0.5f,-0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f, 1.0f }, {1.0f, 0.0f}},//5
     {{-0.5f - 0.5f,-0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f, 0.0f, 1.0f }, {0.0f, 0.0f}},//4
     //left
     {{-0.5f - 0.5f,-0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f }, {0.0f, 0.0f}}, //8
     {{-0.5f - 0.5f,-0.5f,-0.5f}, {0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f }, {1.0f, 0.0f}},//9
     {{-0.5f - 0.5f, 0.5f,-0.5f}, {0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f }, {1.0f, 1.0f}},//10
     {{-0.5f - 0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f }, {0.0f, 1.0f}},//11
     // right
     {{ 0.5f - 0.5f,-0.5f,-0.5f}, {1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f, 0.0f }, {0.0f, 0.0f}},//12
     {{ 0.5f - 0.5f,-0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, { 1.0f, 0.0f, 0.0f }, {1.0f, 0.0f}}, //13
     {{ 0.5f - 0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, { 1.0f, 0.0f, 0.0f }, {1.0f, 1.0f}}, //14
     {{ 0.5f - 0.5f, 0.5f,-0.5f}, {1.0f, 1.0f, 1.0f}, { 1.0f, 0.0f, 0.0f }, {0.0f, 1.0f}},//15
     //bottom
     {{-0.5f - 0.5f,-0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f,-1.0f, 0.0f }, {0.0f, 0.0f}},//16
     {{ 0.5f - 0.5f,-0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f,-1.0f, 0.0f }, {1.0f, 0.0f}},//17
     {{ 0.5f - 0.5f,-0.5f,-0.5f}, {0.0f, 0.0f, 1.0f}, { 0.0f,-1.0f, 0.0f }, {1.0f, 1.0f}},//18
     {{-0.5f - 0.5f,-0.5f,-0.5f}, {1.0f, 1.0f, 1.0f}, { 0.0f,-1.0f, 0.0f }, {0.0f, 1.0f}},//19
     //top
     {{-0.5f - 0.5f, 0.5f,-0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f }, {0.0f, 0.0f}},//20
     {{ 0.5f - 0.5f, 0.5f,-0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f, 1.0f, 0.0f }, {1.0f, 0.0f}},//21
     {{ 0.5f - 0.5f, 0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, { 0.0f, 1.0f, 0.0f }, {1.0f, 1.0f}},//22
     {{-0.5f - 0.5f, 0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, { 0.0f, 1.0f, 0.0f }, {0.0f, 1.0f}},//23
     //2
     //front
     {{-0.5f + 1.5f,-0.5f + 1.5f,-0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f, 0.0f,-1.0f }, {0.0f, 0.0f} }, //0
     {{0.5f + 1.5f,-0.5f + 1.5f,-0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f,-1.0f }, {1.0f, 0.0f}}, //1
     {{0.5f + 1.5f, 0.5f + 1.5f,-0.5f}, {0.0f, 0.0f, 1.0f}, { 0.0f, 0.0f,-1.0f }, {1.0f, 1.0f}}, //2
     {{-0.5f + 1.5f, 0.5f + 1.5f,-0.5f}, {1.0f, 1.0f, 1.0f}, { 0.0f, 0.0f,-1.0f }, {0.0f, 1.0f}}, //3
     //back +1.5f
     {{-0.5f + 1.5f, 0.5f + 1.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, { 0.0f, 0.0f, 1.0f }, {0.0f, 1.0f}},//7
     {{0.5f + 1.5f, 0.5f + 1.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, { 0.0f, 0.0f, 1.0f }, {1.0f, 1.0f}},//6
     {{0.5f + 1.5f,-0.5f + 1.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f, 0.0f, 1.0f }, {1.0f, 0.0f}},//5
     {{-0.5f + 1.5f,-0.5f + 1.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f, 0.0f, 1.0f }, {0.0f, 0.0f}},//4
     //left +1.5f
     {{-0.5f + 1.5f,-0.5f + 1.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {-1.0f, 0.0f, 0.0f }, {0.0f, 0.0f}}, //8
     {{-0.5f + 1.5f,-0.5f + 1.5f,-0.5f}, {0.0f, 1.0f, 0.0f}, {-1.0f, 0.0f, 0.0f }, {1.0f, 0.0f}},//9
     {{-0.5f + 1.5f, 0.5f + 1.5f,-0.5f}, {0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, 0.0f }, {1.0f, 1.0f}},//10
     {{-0.5f + 1.5f, 0.5f + 1.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, {-1.0f, 0.0f, 0.0f }, {0.0f, 1.0f}},//11
     // righ+1.5ft
     {{ 0.5f + 1.5f,-0.5f + 1.5f,-0.5f}, {1.0f, 0.0f, 0.0f}, { 1.0f, 0.0f, 0.0f }, {0.0f, 0.0f}},//12
     {{ 0.5f + 1.5f,-0.5f + 1.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, { 1.0f, 0.0f, 0.0f }, {1.0f, 0.0f}}, //13
     {{ 0.5f + 1.5f, 0.5f + 1.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, { 1.0f, 0.0f, 0.0f }, {1.0f, 1.0f}}, //14
     {{ 0.5f + 1.5f, 0.5f + 1.5f,-0.5f}, {1.0f, 1.0f, 1.0f}, { 1.0f, 0.0f, 0.0f }, {0.0f, 1.0f}},//15
     //botto+1.5fm
     {{-0.5f + 1.5f,-0.5f + 1.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f,-1.0f, 0.0f }, {0.0f, 0.0f}},//16
     {{ 0.5f + 1.5f,-0.5f + 1.5f, 0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f,-1.0f, 0.0f }, {1.0f, 0.0f}},//17
     {{ 0.5f + 1.5f,-0.5f + 1.5f,-0.5f}, {0.0f, 0.0f, 1.0f}, { 0.0f,-1.0f, 0.0f }, {1.0f, 1.0f}},//18
     {{-0.5f + 1.5f,-0.5f + 1.5f,-0.5f}, {1.0f, 1.0f, 1.0f}, { 0.0f,-1.0f, 0.0f }, {0.0f, 1.0f}},//19
     //top  +1.5f
     {{-0.5f + 1.5f, 0.5f + 1.5f,-0.5f}, {1.0f, 0.0f, 0.0f}, { 0.0f, 1.0f, 0.0f }, {0.0f, 0.0f}},//20
     {{ 0.5f + 1.5f, 0.5f + 1.5f,-0.5f}, {0.0f, 1.0f, 0.0f}, { 0.0f, 1.0f, 0.0f }, {1.0f, 0.0f}},//21
     {{ 0.5f + 1.5f, 0.5f + 1.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, { 0.0f, 1.0f, 0.0f }, {1.0f, 1.0f}},//22
     {{-0.5f + 1.5f, 0.5f + 1.5f, 0.5f}, {1.0f, 1.0f, 1.0f}, { 0.0f, 1.0f, 0.0f }, {0.0f, 1.0f}}//23
};

class VertexBuffer{
public:
    
    VertexBuffer(Application* App);
    ~VertexBuffer();
    
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    std::vector<uint16_t> indices;
    //= {
    // 0, 1, 2, 2, 3, 0//front
    //,4, 6, 5, 7, 6, 4//back
    //,8, 9, 10, 10, 11, 8//left
    //,12, 13, 14, 14, 15, 12//right
    //,16, 17, 18, 18, 19, 16//bottom
    //,20, 21, 22, 22, 23, 20//top
    //};
    VkBuffer Getindex();
private:
    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;
    Application *mainApp;
    void addIndices(int faceNum);
    void createIndexBuffer();
    void createVertexBuffer();
};

