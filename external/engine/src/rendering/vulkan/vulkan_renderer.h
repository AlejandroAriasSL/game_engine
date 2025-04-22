#pragma once

#include <example_engine/rendering/renderer.h>
#include <vulkan/vulkan.h>
#include <vector>

namespace ONI {
class VulkanRenderer : public Renderer {
public:
  void Init(RendererSettings settings) override;
  void Shutdown() override;
  void RenderFrame() override;

private:
  void init_core();
  void createSwapChain(); 
  void createCommand();
  void createDefaultRenderPass();
  void createFrameBuffers();
  void createSyncStructures();

private:

  uint64_t _frameNumber {0};
  
  RendererSettings _rendererSettings {};

  VkInstance _instance;
  VkDebugUtilsMessengerEXT _debug_messenger;
  VkPhysicalDevice _physicalDevice;
  VkDevice _device;
  VkSurfaceKHR _surface;

  VkSwapchainKHR _swapchain;
  VkFormat _swapchainImageFormat;
  std::vector<VkImage> _swapchainImages;
  std::vector<VkImageView> _swapchainImageViews;
  VkExtent2D _windowExtent;

  VkQueue _graphicsQueue;
  uint32_t _graphicsQueueFamily;

  VkCommandPool _commandPool;
  VkCommandBuffer _mainCommandBuffer;

  VkRenderPass _renderPass;
  std::vector<VkFramebuffer> _frameBuffers {3};

  VkSemaphore _presentSemaphore, _renderSemaphore;
  VkFence _renderFence;
};
};