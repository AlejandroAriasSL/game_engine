#pragma once

#include <example_engine/rendering/renderer.h>
#include <vulkan/vulkan.h>
#include "components/vulkan_swapchain.h"
#include "components/vulkan_device.h"
#include "components/vulkan_pipeline_builder.h"
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
  void createPipeLines();

private:

  VulkanSwapChain _vulkanSwapChain;
  VulkanDevice _vulkanDevice;
  VkSurfaceKHR _surface;
  
  uint64_t _frameNumber {0};
  
  RendererSettings _rendererSettings {};
  VkExtent2D _windowExtent;

  VkCommandPool _commandPool;
  VkCommandBuffer _mainCommandBuffer;

  VkRenderPass _renderPass;
  std::vector<VkFramebuffer> _frameBuffers {3};

  VkSemaphore _presentSemaphore, _renderSemaphore;
  VkFence _renderFence;

  VkPipelineLayout _trianglePipelineLayout;
  VkPipeline _trianglePipeline;

};
};