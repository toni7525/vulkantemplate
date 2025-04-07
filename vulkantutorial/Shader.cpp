#include "Shader.h"
Shader::Shader(const std::string& filename, VkDevice* device)
{
    deviceptr = device;
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error("failed to open file!");
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> code(fileSize);

    file.seekg(0);
    file.read(code.data(), fileSize);

    file.close();

    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
    if (vkCreateShaderModule(*device, &createInfo, nullptr, &shadercop) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module!");
    }
}
Shader::~Shader()
{
    vkDestroyShaderModule(*deviceptr, shadercop, nullptr);
}
VkShaderModule Shader::Get()
{
    return shadercop;
}
