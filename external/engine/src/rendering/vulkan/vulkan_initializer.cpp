#pragma message("✔ Compilando vulkan_initializer.cpp")

#include "vulkan_initializer.h"

namespace ONI {
    VkCommandPoolCreateInfo VulkanInitializer::CommandPoolCreateInfo(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags flag){
        VkCommandPoolCreateInfo commandPoolCreateInfo { VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO };
        commandPoolCreateInfo.queueFamilyIndex = queueFamilyIndex;
        commandPoolCreateInfo.flags = flag;
        
        return commandPoolCreateInfo;
    }
    VkCommandBufferAllocateInfo VulkanInitializer::CommandBufferAllocateInfo(VkCommandPool pool, uint32_t count, VkCommandBufferLevel level){
        VkCommandBufferAllocateInfo commandBufferAllocateInfo { VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO};
        commandBufferAllocateInfo.commandPool = pool;
        commandBufferAllocateInfo.commandBufferCount = count;
        commandBufferAllocateInfo.level = level;
        
        return commandBufferAllocateInfo;
    }
    VkPipelineShaderStageCreateInfo VulkanInitializer::PipelineShaderStageCreateInfo(VkShaderStageFlagBits stage, VkShaderModule shaderModule){
        VkPipelineShaderStageCreateInfo shaderStageCreateInfo { VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO };
        shaderStageCreateInfo.stage = stage;
        shaderStageCreateInfo.module = shaderModule;
        shaderStageCreateInfo.pName = "main";

        return shaderStageCreateInfo;
    }
    VkPipelineVertexInputStateCreateInfo VulkanInitializer::PipelineVertexInputStateCreateInfo(){
        VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo { VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO };

        pipelineVertexInputStateCreateInfo.vertexBindingDescriptionCount = 0;
        pipelineVertexInputStateCreateInfo.vertexAttributeDescriptionCount = 0;

        return pipelineVertexInputStateCreateInfo;
    }
    VkPipelineInputAssemblyStateCreateInfo VulkanInitializer::PipelineInputAssemblyStateCreateInfo(VkPrimitiveTopology topology){
        VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo { VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO };
        pipelineInputAssemblyStateCreateInfo.topology = topology;
        pipelineInputAssemblyStateCreateInfo.primitiveRestartEnable = VK_FALSE;
        
        return pipelineInputAssemblyStateCreateInfo;
    }
    VkPipelineRasterizationStateCreateInfo VulkanInitializer::PipelineRasterizationStateCreateInfo(VkPolygonMode polygonMode){
        VkPipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo { VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO };
        pipelineRasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
        pipelineRasterizationStateCreateInfo.rasterizerDiscardEnable = VK_FALSE;
        pipelineRasterizationStateCreateInfo.polygonMode = polygonMode;
        pipelineRasterizationStateCreateInfo.lineWidth = 1.0f;
        pipelineRasterizationStateCreateInfo.cullMode = VK_CULL_MODE_NONE;
        pipelineRasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
        pipelineRasterizationStateCreateInfo.depthBiasEnable = VK_FALSE;
        pipelineRasterizationStateCreateInfo.depthBiasConstantFactor = 0.f;
        pipelineRasterizationStateCreateInfo.depthBiasClamp = 0.f;
        pipelineRasterizationStateCreateInfo.depthBiasSlopeFactor = 0.f;

        return pipelineRasterizationStateCreateInfo;
    }
    VkPipelineMultisampleStateCreateInfo VulkanInitializer::PipelineMultisampleStateCreateInfo(){
        VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo { VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO };
        pipelineMultisampleStateCreateInfo.sampleShadingEnable = VK_FALSE;
        pipelineMultisampleStateCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        pipelineMultisampleStateCreateInfo.minSampleShading = 1.0f;
        pipelineMultisampleStateCreateInfo.pSampleMask = nullptr;
        pipelineMultisampleStateCreateInfo.alphaToCoverageEnable = VK_FALSE;
        pipelineMultisampleStateCreateInfo.alphaToOneEnable = VK_FALSE;

        return pipelineMultisampleStateCreateInfo;
    }
    VkPipelineColorBlendAttachmentState VulkanInitializer::PipelineColorBlendAttachmentState(){
        VkPipelineColorBlendAttachmentState pipelineColorBlendAttachmentState {};
        pipelineColorBlendAttachmentState.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        pipelineColorBlendAttachmentState.blendEnable = VK_FALSE;

        return pipelineColorBlendAttachmentState;
    }
    VkPipelineLayoutCreateInfo VulkanInitializer::PipelineLayoutCreateInfo(){
        VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo { VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO };
        pipelineLayoutCreateInfo.flags = 0;
        pipelineLayoutCreateInfo.setLayoutCount = 0;
        pipelineLayoutCreateInfo.pSetLayouts = nullptr;
        pipelineLayoutCreateInfo.pushConstantRangeCount = 0;
        pipelineLayoutCreateInfo.pPushConstantRanges = nullptr;

        return pipelineLayoutCreateInfo;
    }
}