#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include "Application.h"
class Texture
{
public:
	Texture(Application* App,std::string path);
	~Texture();
	VkImage GetTxture();
	VkImageView textureImageView;
	VkSampler textureSampler;
private:

	Application* mainApp;

	VkImage textureImage;
	VkDeviceMemory textureImageMemory;
	

	void createTextureImageView();
	void createTextureSampler();
	void createTextureImage(std::string path);
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
	void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
	void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
};

