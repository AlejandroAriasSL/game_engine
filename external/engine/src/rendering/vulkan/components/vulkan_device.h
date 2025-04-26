#pragma once
#include "VkBootstrap.h"

namespace ONI {
  struct RendererSettings;
};

class VulkanDevice{
public:
  void createInstance(const ONI::RendererSettings& renderSettings);
  void buildDevice(VkSurfaceKHR surface);
  VkInstance getInstance() const { return _instance; }
  VkDevice getDevice() const { return _device; }
  VkPhysicalDevice getPhysicalDevice() const { return _physicalDevice; }
  uint32_t getGraphicsQueueFamily() const { return _graphicsQueueFamily; }
  VkQueue getGraphicsQueue() const { return _graphicsQueue; }
  VkDebugUtilsMessengerEXT getDebugMessenger() const { return _debug_messenger; }
private:
 vkb::Instance _vkbInstance;
  VkInstance _instance;
  VkDebugUtilsMessengerEXT _debug_messenger;
  VkPhysicalDevice _physicalDevice;
  VkDevice _device;
  VkQueue _graphicsQueue;
  uint32_t _graphicsQueueFamily;

};