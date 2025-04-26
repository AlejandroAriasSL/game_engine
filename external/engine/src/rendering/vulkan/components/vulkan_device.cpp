#include "vulkan_device.h"
#include "example_engine/rendering/renderer.h"
#include <iostream>

void VulkanDevice::createInstance(const ONI::RendererSettings& renderSettings){

  vkb::InstanceBuilder builder;

  auto builtInstance = builder.set_app_name(renderSettings.ApplicationName.c_str())
    .request_validation_layers(true)
    .require_api_version(1, 2, 0)
    .use_default_debug_messenger()
    .build();

  _vkbInstance = builtInstance.value();
  _instance = _vkbInstance.instance;
  _debug_messenger = _vkbInstance.debug_messenger;

}

void VulkanDevice::buildDevice(VkSurfaceKHR surface){

  vkb::PhysicalDeviceSelector selector {_vkbInstance};
  vkb::PhysicalDevice vkbPhysicalDevice{
    selector
    .set_minimum_version(1, 1)
    .set_surface(surface)
    .select()
    .value()
  };

  vkb::DeviceBuilder deviceBuilder {vkbPhysicalDevice};
  vkb::Device vkbDevice {deviceBuilder.build().value()};

  _device = vkbDevice.device;
  _physicalDevice = vkbPhysicalDevice.physical_device;

  _graphicsQueue = vkbDevice.get_queue(vkb::QueueType::graphics).value();
  _graphicsQueueFamily = vkbDevice.get_queue_index(vkb::QueueType::graphics).value();
}