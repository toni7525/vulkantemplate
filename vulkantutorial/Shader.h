#pragma once
#include <vulkan/vulkan.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdint>
#include <limits>
#include <optional>
#include <set>

class Shader
{
public:

	Shader(const std::string& filename, VkDevice* device);
	~Shader();
	VkShaderModule Get();
private:
	VkDevice* deviceptr;
	VkShaderModule shadercop;
};

