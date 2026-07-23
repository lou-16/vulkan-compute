#include <stdio.h>
#include <vulkan/vulkan.h>
#include <string.h>
#include "compute.h"
#include "device.h"
#include "vulkan/vk_platform.h"
#include "vulkan/vulkan_core.h"

VkCommandBuffer CommandBuf = VK_NULL_HANDLE;

void PrepareCommandBuffer(void) {

    VkCommandBufferAllocateInfo allocInfo;
    memset(&allocInfo,0,sizeof(allocInfo));
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = CommandPool;
    allocInfo.commandBufferCount = 1;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

    if(vkAllocateCommandBuffers(LogicalDevice, &allocInfo, &CommandBuf) != VK_SUCCESS){
        printf("failed to allocate command \n");
        return;
    }

    VkCommandBufferBeginInfo beginInfo;
    memset(&beginInfo, 0, sizeof(beginInfo));
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

    if(vkBeginCommandBuffer(CommandBuf, &beginInfo) !=VK_SUCCESS){
        printf("failed to begin command buffer\n");
        return;
    };

    vkCmdDispatch(CommandBuf, 1, 1, 1);
    if(vkEndCommandBuffer(CommandBuf) != VK_SUCCESS){
        printf("failed to end command buffer\n");
        return;
    };
    return;
}

void compute(){
    VkSubmitInfo submitInfo;
    memset(&submitInfo, 0, sizeof(submitInfo));
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &CommandBuf;

    if(vkQueueSubmit(ComputingQueue, 1, &submitInfo, NULL) != VK_SUCCESS){
        printf("failed to submit compute queue to GPU, sory :(\n");
        return;
    };
    return;
}
