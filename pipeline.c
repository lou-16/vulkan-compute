#include "pipeline.h"
#include "log.h"
#include "vulkan/vk_platform.h"
#include "vulkan/vulkan_core.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

VkPipeline pipeline = VK_NULL_HANDLE;
VkPipelineLayout PipelineLayout = VK_NULL_HANDLE;
extern VkDevice LogicalDevice;

VkShaderModule CreateComputeShader()
{
    uint8_t shaderData[20000];
    FILE *f = fopen("comp.spv", "rb");
    
    if(f == NULL){
        Log("info","failed to open shader");
        return VK_NULL_HANDLE;
    }

    size_t size = fread(shaderData, 1, sizeof(shaderData), f);
    fclose(f);

    VkShaderModuleCreateInfo createInfo;
    memset(&createInfo, 0, sizeof(createInfo));
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = size;
    createInfo.pCode = (uint32_t*)shaderData;

    VkShaderModule shaderModule;

    if(vkCreateShaderModule(
        LogicalDevice, 
        &createInfo, 
        NULL, 
        &shaderModule
    ) != VK_SUCCESS){
        Log("info","failed to create shader module");
    }
    return shaderModule;
}

void CreatePipelineLayout(){

    VkPipelineLayoutCreateInfo createLayout;
    memset(&createLayout, 0, sizeof(createLayout));
    createLayout.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

    if(vkCreatePipelineLayout(
        LogicalDevice, 
        &createLayout,
        NULL, 
        &PipelineLayout) != VK_SUCCESS)
        {
            Log("info","failed to create pipeline layout");
            return;
        };
}

void CreatePipeline() {

    CreatePipelineLayout();

    VkComputePipelineCreateInfo createPipeline;
    memset(&createPipeline, 0, sizeof(createPipeline));
    createPipeline.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
    createPipeline.layout = PipelineLayout;
    createPipeline.basePipelineIndex = -1;
    createPipeline.stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    createPipeline.stage.stage = VK_SHADER_STAGE_COMPUTE_BIT;
    createPipeline.stage.pName = "main";
    createPipeline.stage.module = CreateComputeShader();

    if(
        vkCreateComputePipelines(
            LogicalDevice,
            VK_NULL_HANDLE,
            1,
            &createPipeline, 
            NULL, 
            &pipeline
        ) != VK_SUCCESS
    ) 
    {
        Log("info","failed to create a pipeline");
        return; 
    }
}

void DestroyPipeline()
{
    if(PipelineLayout != VK_NULL_HANDLE) vkDestroyPipelineLayout(LogicalDevice, PipelineLayout, NULL);
    if(pipeline != VK_NULL_HANDLE) vkDestroyPipeline(LogicalDevice, pipeline, NULL);
}