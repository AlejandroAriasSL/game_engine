#include "vulkan_renderer.h"

#include "VkBootstrap.h"
#include <example_engine/service_locator.h>
#include "vulkan_initializer.h"
#include "vulkan_types.h"
#include "vulkan_utilities.h"
#include <math.h>

namespace ONI {
  void VulkanRenderer::Init(RendererSettings settings){
    _rendererSettings = settings;

    init_core();
    createSwapChain();
    createCommand();
    createDefaultRenderPass();
    createFrameBuffers();
    createSyncStructures();
    createPipeLines();
  }
  void VulkanRenderer::init_core() {
    _vulkanDevice.createInstance(_rendererSettings);
  
    std::unordered_map<SurfaceArgs, std::any> surfaceArgs {
      {SurfaceArgs::INSTANCE, _vulkanDevice.getInstance()},
      {SurfaceArgs::OUT_SURFACE, &_surface}
    };
  
    ServiceLocator::GetWindow()->RequestDrawSurface(surfaceArgs);
  
    _vulkanDevice.buildDevice(_surface);
  }
  void VulkanRenderer::RenderFrame() {
    VK_CHECK(vkWaitForFences(_vulkanDevice.getDevice(), 1, &_renderFence, true, 1000000000));
    VK_CHECK(vkResetFences(_vulkanDevice.getDevice(), 1, &_renderFence));

    uint32_t swapchainImageIndex;
    VK_CHECK(vkAcquireNextImageKHR(_vulkanDevice.getDevice(), _vulkanSwapChain.getSwapchain(), 1000000000, _presentSemaphore, nullptr, &swapchainImageIndex));

    VK_CHECK(vkResetCommandBuffer(_mainCommandBuffer, 0));

    VkCommandBuffer cmd = _mainCommandBuffer;

    VkCommandBufferBeginInfo beginInfo {VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    VK_CHECK(vkBeginCommandBuffer(cmd, &beginInfo));

    float flashColor = abs(sin((float)_frameNumber / 120.0f));

    VkClearValue clearValue {
      .color = {0.f, 0.f, flashColor, 1.f}
    }; 

    VkRenderPassBeginInfo renderPassBeginInfo {VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO};
    renderPassBeginInfo.renderPass = _renderPass;
    renderPassBeginInfo.renderArea = {
      .offset = {
        .x = 0,
        .y = 0
      },
      .extent = _windowExtent
    };

    renderPassBeginInfo.framebuffer = _frameBuffers[swapchainImageIndex];
    renderPassBeginInfo.clearValueCount = 1;
    renderPassBeginInfo.pClearValues = &clearValue;

    vkCmdBeginRenderPass(cmd, &renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(cmd, VK_PIPELINE_BIND_POINT_GRAPHICS, _trianglePipeline);
    vkCmdDraw(cmd, 3, 1, 0, 0);

    vkCmdEndRenderPass(cmd);
    VK_CHECK(vkEndCommandBuffer(cmd));

    VkSubmitInfo submit {VK_STRUCTURE_TYPE_SUBMIT_INFO};
    
    VkPipelineStageFlags waitStage = VK_PIPELINE_STAGE_2_COLOR_ATTACHMENT_OUTPUT_BIT;
    submit.pWaitDstStageMask = &waitStage;

    submit.waitSemaphoreCount = 1;
    submit.pWaitSemaphores = &_presentSemaphore;

    submit.signalSemaphoreCount = 1;
    submit.pSignalSemaphores = &_renderSemaphore;

    submit.commandBufferCount = 1;
    submit.pCommandBuffers = &_mainCommandBuffer;

    VK_CHECK(vkQueueSubmit(_vulkanDevice.getGraphicsQueue(), 1, &submit, _renderFence));

    VkPresentInfoKHR presentInfoKHR {VK_STRUCTURE_TYPE_PRESENT_INFO_KHR};
    presentInfoKHR.swapchainCount = 1;
    VkSwapchainKHR swapChains = {_vulkanSwapChain.getSwapchain()};
    presentInfoKHR.pSwapchains = &swapChains;

    presentInfoKHR.waitSemaphoreCount = 1;
    presentInfoKHR.pWaitSemaphores = &_renderSemaphore;

    presentInfoKHR.pImageIndices = &swapchainImageIndex;

    VK_CHECK(vkQueuePresentKHR(_vulkanDevice.getGraphicsQueue(), &presentInfoKHR));
    _frameNumber++;
  }
  void VulkanRenderer::Shutdown() {

    vkDeviceWaitIdle(_vulkanDevice.getDevice());

    vkDestroyPipeline(_vulkanDevice.getDevice(), _trianglePipeline, nullptr);
    vkDestroyPipelineLayout(_vulkanDevice.getDevice(), _trianglePipelineLayout, nullptr);
    vkDestroyFence(_vulkanDevice.getDevice(), _renderFence, nullptr);
    vkDestroySemaphore(_vulkanDevice.getDevice(), _presentSemaphore, nullptr);
    vkDestroySemaphore(_vulkanDevice.getDevice(), _renderSemaphore, nullptr);

    for(auto frameBuffer : _frameBuffers) {
      vkDestroyFramebuffer(_vulkanDevice.getDevice(), frameBuffer, nullptr);
    }

    vkDestroyRenderPass(_vulkanDevice.getDevice(), _renderPass, nullptr);

    vkDestroyCommandPool(_vulkanDevice.getDevice(), _commandPool, nullptr); 
    vkDestroySwapchainKHR(_vulkanDevice.getDevice(), _vulkanSwapChain.getSwapchain(), nullptr);

    for (auto _imageView : _vulkanSwapChain.getImageViews()) {
      vkDestroyImageView(_vulkanDevice.getDevice(), _imageView, nullptr);
    }

    vkDestroyDevice(_vulkanDevice.getDevice(), nullptr);
    vkDestroySurfaceKHR(_vulkanDevice.getInstance(), _surface, nullptr);
    vkb::destroy_debug_utils_messenger(_vulkanDevice.getInstance(), _vulkanDevice.getDebugMessenger());
    vkDestroyInstance(_vulkanDevice.getInstance(), nullptr);
  }
  void VulkanRenderer::createSwapChain() {

    auto [width, height] = ServiceLocator::GetWindow()->GetWindowExtents();

    _windowExtent.width = width;
    _windowExtent.height = height;

    _vulkanSwapChain.buildSwapChain(width, height, _vulkanDevice.getPhysicalDevice(), _vulkanDevice.getDevice(), _surface);
  }
  void VulkanRenderer::createCommand() {
    VkCommandPoolCreateInfo commandPoolCreateInfo = VulkanInitializer::CommandPoolCreateInfo(_vulkanDevice.getGraphicsQueueFamily(),
    VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
    VK_CHECK(vkCreateCommandPool(_vulkanDevice.getDevice(), &commandPoolCreateInfo, nullptr, &_commandPool));

    VkCommandBufferAllocateInfo commandBufferAllocateInfo = VulkanInitializer::CommandBufferAllocateInfo(_commandPool);

    VK_CHECK(vkAllocateCommandBuffers(_vulkanDevice.getDevice(), &commandBufferAllocateInfo, &_mainCommandBuffer));
  }
  
  void VulkanRenderer::createDefaultRenderPass() {
    VkAttachmentDescription colorAttachment{
      .format = _vulkanSwapChain.getImageFormat(),
      .samples = VK_SAMPLE_COUNT_1_BIT,
      .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
      .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
      .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
      .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
      .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
      .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
    };

    VkAttachmentReference colorAttachmentRef {
      .attachment = 0,
      .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL
    };

    VkSubpassDescription subpass {
      .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
      .colorAttachmentCount = 1,
      .pColorAttachments = &colorAttachmentRef
    };

    VkRenderPassCreateInfo renderPassCreateInfo { VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO};
    renderPassCreateInfo.attachmentCount = 1;
    renderPassCreateInfo.pAttachments = &colorAttachment;
    renderPassCreateInfo.subpassCount = 1;
    renderPassCreateInfo.pSubpasses = &subpass;

    VK_CHECK(vkCreateRenderPass(_vulkanDevice.getDevice(), &renderPassCreateInfo, nullptr, &_renderPass));
  }
  
  void VulkanRenderer::createFrameBuffers() {
    VkFramebufferCreateInfo framebufferCreateinfo { VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO};
    framebufferCreateinfo.renderPass = _renderPass;
    framebufferCreateinfo.attachmentCount = 1;
    framebufferCreateinfo.width = _windowExtent.width;
    framebufferCreateinfo.height = _windowExtent.height;
    framebufferCreateinfo.layers = 1;

    const uint32_t swapChainImageCount = _vulkanSwapChain.getImages().size();
    _frameBuffers.resize(swapChainImageCount); 

    std::vector<VkImageView> swapchainImageViews = _vulkanSwapChain.getImageViews(); 

    for (int i = 0; i < swapChainImageCount; i++) {
      framebufferCreateinfo.pAttachments = &swapchainImageViews[i];
      VK_CHECK(vkCreateFramebuffer(_vulkanDevice.getDevice(), &framebufferCreateinfo, nullptr, &_frameBuffers[i]));
    }
  }
  
  void VulkanRenderer::createSyncStructures() {
    VkFenceCreateInfo fenceCreateInfo {VK_STRUCTURE_TYPE_FENCE_CREATE_INFO};
    fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    VK_CHECK(vkCreateFence(_vulkanDevice.getDevice(), &fenceCreateInfo, nullptr, &_renderFence));

    VkSemaphoreCreateInfo semaphoreCreateInfo {VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
    VK_CHECK(vkCreateSemaphore(_vulkanDevice.getDevice(), &semaphoreCreateInfo, nullptr, &_presentSemaphore));
    VK_CHECK(vkCreateSemaphore(_vulkanDevice.getDevice(), &semaphoreCreateInfo, nullptr, &_renderSemaphore));
  }
  void VulkanRenderer::createPipeLines() {
    VkShaderModule triangleFragShader;
    if (!VulkanUtilities::loadShaderModule("shaders/triangle.frag.spv", _vulkanDevice.getDevice(), triangleFragShader)) {
      std::cout << "Failed to load triangle fragmen shader module" << std::endl;
    } else {
      std::cout << "Succesfully loaded triangle fragment shader module" << std::endl;
    }

    VkShaderModule triangleVertShader;
    if (!VulkanUtilities::loadShaderModule("shaders/triangle.vert.spv", _vulkanDevice.getDevice(), triangleVertShader)) {
      std::cout << "Failed to load triangle vertex shader module" << std::endl;
    } else {
      std::cout << "Succesfully loaded triangle vertex shader module" << std::endl;
    }

    auto pipelineLayoutInfo = VulkanInitializer::PipelineLayoutCreateInfo();

    VK_CHECK(vkCreatePipelineLayout(_vulkanDevice.getDevice(), &pipelineLayoutInfo, nullptr, &_trianglePipelineLayout));
    
    VulkanPipelineBuilder pipelineBuilder;
    pipelineBuilder._shaderStages.push_back(
        VulkanInitializer::PipelineShaderStageCreateInfo(VK_SHADER_STAGE_VERTEX_BIT, triangleVertShader)
    );
    pipelineBuilder._shaderStages.push_back(
        VulkanInitializer::PipelineShaderStageCreateInfo(VK_SHADER_STAGE_FRAGMENT_BIT, triangleFragShader)
    );
    pipelineBuilder._vertexInputInfo = VulkanInitializer::PipelineVertexInputStateCreateInfo();
    pipelineBuilder._inputAssembly = VulkanInitializer::PipelineInputAssemblyStateCreateInfo(VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST);
    pipelineBuilder._viewport = {
      .x = 0.f,
      .y = 0.f,
      .width = static_cast<float>(_windowExtent.width),
      .height = static_cast<float>(_windowExtent.height),
      .minDepth = 0.f,
      .maxDepth = 1.f
    };
    pipelineBuilder._scissor = {
      .offset {0, 0},
      .extent {_windowExtent}
    };
    pipelineBuilder._rasterizer = VulkanInitializer::PipelineRasterizationStateCreateInfo(VK_POLYGON_MODE_FILL);
    pipelineBuilder._multisampling = VulkanInitializer::PipelineMultisampleStateCreateInfo();
    pipelineBuilder._colorBlendAttachment = VulkanInitializer::PipelineColorBlendAttachmentState();
    pipelineBuilder._pipelineLayout = _trianglePipelineLayout;

    _trianglePipeline = pipelineBuilder.buildPipeline(_vulkanDevice.getDevice(), _renderPass);

    vkDestroyShaderModule(_vulkanDevice.getDevice(), triangleFragShader, nullptr);
    vkDestroyShaderModule(_vulkanDevice.getDevice(), triangleVertShader, nullptr);

  };
}