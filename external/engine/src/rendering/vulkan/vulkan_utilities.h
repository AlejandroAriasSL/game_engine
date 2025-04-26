#pragma once

#include <iostream>

#define VK_CHECK(x)                                         \
  do{                                                       \
    VkResult err = x;                                       \
    if (err) {                                              \
        std::cerr << "Vulkan error: " << err << std::endl;  \
        std::abort();                                       \
    }                                                       \
  } while(0)                                                \

class VulkanUtilities {

};