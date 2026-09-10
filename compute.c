#include "log.h"
#include <_string.h>
#include <stdio.h>
#include <vulkan/vulkan.h>
#include <string.h>
#include "compute.h"
#include "device.h"
#include "vulkan/vk_platform.h"
#include "vulkan/vulkan_core.h"
#include "pipeline.h"

VkCommandBuffer CommandBuf = VK_NULL_HANDLE;

void PrepareCommandBuffer(void) {

    VkCommandBufferAllocateInfo allocInfo;
    memset(&allocInfo,0,sizeof(allocInfo));
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = CommandPool;
    allocInfo.commandBufferCount = 1;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

    if(vkAllocateCommandBuffers(LogicalDevice, &allocInfo, &CommandBuf) != VK_SUCCESS){
        Log("info","failed to allocate command \n");
        return;
    }

    VkCommandBufferBeginInfo beginInfo;
    memset(&beginInfo, 0, sizeof(beginInfo));
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    if(vkBeginCommandBuffer(CommandBuf, &beginInfo) !=VK_SUCCESS){
        Log("info","failed to begin command buffer\n");
        return;
    };

    vkCmdBindPipeline(CommandBuf, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline);

    vkCmdDispatch(CommandBuf, 1, 1, 1);
    if(vkEndCommandBuffer(CommandBuf) != VK_SUCCESS){
        Log("info","failed to end command buffer\n");
        return;
    };
    return;
}

void compute(){

    VkFence fence;
    VkFenceCreateInfo fenceCreateInfo;
    memset(&fenceCreateInfo, 0, sizeof(fenceCreateInfo));
    fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    if(vkCreateFence(LogicalDevice, &fenceCreateInfo, NULL, &fence) != VK_SUCCESS){
        Log("error",  "failed to created fence\n");
        return;
    }

    VkSubmitInfo submitInfo;
    memset(&submitInfo, 0, sizeof(submitInfo));
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &CommandBuf;

    if(vkQueueSubmit(ComputingQueue, 1, &submitInfo, NULL) != VK_SUCCESS){
        Log("info","failed to submit compute queue to GPU, sory :(\n");
        return;
    };

    VkResult waitForFenceResult;
    if((waitForFenceResult = vkWaitForFences(LogicalDevice, 1, &fence, VK_TRUE, 1000000000)) != VK_SUCCESS){
        Log("error",  "faild to wait for fence due to error: %zu\n", waitForFenceResult);
    }

    vkDestroyFence(LogicalDevice, fence, NULL);
    return;
}
