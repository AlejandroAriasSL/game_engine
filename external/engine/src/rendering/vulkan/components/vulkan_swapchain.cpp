#include "vulkan_swapchain.h"

void VulkanSwapChain::buildSwapChain(int width, int height, VkPhysicalDevice physicalDevice, VkDevice device, VkSurfaceKHR surface)
{
    vkb::SwapchainBuilder _swapchainBuilder {physicalDevice, device, surface};
    vkb::Swapchain _vkbSwapchain{
      _swapchainBuilder
       .use_default_format_selection()
       .set_desired_present_mode(VK_PRESENT_MODE_FIFO_KHR)
       .set_desired_extent(width, height)
       .build()
       .value()
    };

    _swapchain = _vkbSwapchain.swapchain;
    _swapchainImages = _vkbSwapchain.get_images().value();
    _swapchainImageViews = _vkbSwapchain.get_image_views().value();
    _swapchainImageFormat = _vkbSwapchain.image_format;
}