#include "vulkan_pipeline_builder.h"
#include <iostream>

VkPipeline ONI::VulkanPipelineBuilder::buildPipeline(VkDevice device, VkRenderPass pass){
    VkPipelineViewportStateCreateInfo viewportState { VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO };
    viewportState.viewportCount = 1;
    viewportState.pViewports = &_viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &_scissor;

    VkPipelineColorBlendStateCreateInfo colorBlendStateCreateInfo { VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO };
    colorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
    colorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_COPY;
    colorBlendStateCreateInfo.attachmentCount = 1;
    colorBlendStateCreateInfo.pAttachments = &_colorBlendAttachment;

    VkGraphicsPipelineCreateInfo pipelineCreateInfo { VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO };
    pipelineCreateInfo.stageCount = _shaderStages.size();
    pipelineCreateInfo.pStages = _shaderStages.data();
    pipelineCreateInfo.pVertexInputState = &_vertexInputInfo;
    pipelineCreateInfo.pInputAssemblyState = &_inputAssembly;
    pipelineCreateInfo.pViewportState = &viewportState;
    pipelineCreateInfo.pRasterizationState = &_rasterizer;
    pipelineCreateInfo.pMultisampleState = &_multisampling;
    pipelineCreateInfo.pColorBlendState = &colorBlendStateCreateInfo;
    pipelineCreateInfo.layout = _pipelineLayout;
    pipelineCreateInfo.renderPass = pass;
    pipelineCreateInfo.subpass = 0;
    pipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;

    VkPipeline newPipeline;

    if(vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineCreateInfo, nullptr, &newPipeline) != VK_SUCCESS){
        std::cout << "Failed to create pipeline" << std::endl;
        return VK_NULL_HANDLE;
    }


    return newPipeline;
}