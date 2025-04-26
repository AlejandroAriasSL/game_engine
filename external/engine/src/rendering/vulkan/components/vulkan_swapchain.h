#pragma once
#include "VkBootstrap.h"

#include <vector>
namespace vkb {
  class Swapchain;
};

class VulkanSwapChain {
public:
  void buildSwapChain(int width, int height, VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface);
  VkSwapchainKHR getSwapchain() const { return _swapchain; }
  VkFormat getImageFormat() const { return _swapchainImageFormat; }
  std::vector<VkImage> getImages() const { return _swapchainImages; }
  std::vector<VkImageView> getImageViews() const { return _swapchainImageViews; }
private: 
  vkb::Swapchain _vkbSwapchain;
  VkSwapchainKHR _swapchain;           
  VkFormat _swapchainImageFormat;
  std::vector<VkImage> _swapchainImages;      
  std::vector<VkImageView>_swapchainImageViews; 
};