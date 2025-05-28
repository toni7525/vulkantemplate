#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(Application* App):mainApp(App){
    addIndices(12);
	createVertexBuffer();
    createIndexBuffer();
}

VertexBuffer::~VertexBuffer(){
    vkDestroyBuffer(mainApp->device, indexBuffer, nullptr);
    vkFreeMemory(mainApp->device, indexBufferMemory, nullptr);


	vkDestroyBuffer(mainApp->device, vertexBuffer, nullptr);
	vkFreeMemory(mainApp->device, vertexBufferMemory, nullptr);
}

VkBuffer VertexBuffer::Getindex()
{
    if (indexBuffer == NULL)
        std::cout << "\nNO INDEX BUFFER\n";
    return indexBuffer;
}




//0, 1, 2, 2, 3, 0
void VertexBuffer::addIndices(int faceNum)
{
    for (int i = 0;i < faceNum;++i) {
        indices.push_back(i * 4);
        indices.push_back(i * 4 + 1);
        indices.push_back(i * 4 + 2);
        indices.push_back(i * 4 + 2);
        indices.push_back(i * 4 + 3);
        indices.push_back(i * 4);
    }
}

void VertexBuffer::createIndexBuffer()
{
    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    mainApp->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(mainApp->device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t)bufferSize);
    vkUnmapMemory(mainApp->device, stagingBufferMemory);

    mainApp->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

    mainApp->copyBuffer(stagingBuffer, indexBuffer, bufferSize);

    vkDestroyBuffer(mainApp->device, stagingBuffer, nullptr);
    vkFreeMemory(mainApp->device, stagingBufferMemory, nullptr);
}

void VertexBuffer::createVertexBuffer()
{
    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    mainApp->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(mainApp->device, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, vertices.data(), (size_t)bufferSize);
    vkUnmapMemory(mainApp->device, stagingBufferMemory);

    mainApp->createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

    mainApp->copyBuffer(stagingBuffer, vertexBuffer, bufferSize);

    vkDestroyBuffer(mainApp->device, stagingBuffer, nullptr);
    vkFreeMemory(mainApp->device, stagingBufferMemory, nullptr);
}
