 #pragma once
#include "vulkan/vulkan_core.h"
#include <vulkan/vulkan.h>

extern VkPipeline pipeline;
extern VkPipelineLayout PipelineLayout;

void CreatePipeline();
void DestroyPipeline();