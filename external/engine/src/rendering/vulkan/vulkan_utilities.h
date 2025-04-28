#pragma once

#include <iostream>
#include <vulkan/vulkan.h>

#define VK_CHECK(x)                                         \
  do{                                                       \
    VkResult err = x;                                       \
    if (err) {                                              \
        std::cerr << "Vulkan error: " << err << std::endl;  \
        std::abort();                                       \
    }                                                       \
  } while(0)                                                \

namespace ONI {
  class VulkanUtilities {
    public:
      static bool loadShaderModule(const std::string& filePath, VkDevice device, VkShaderModule& outShaderModule);
  };

};