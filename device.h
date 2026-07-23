#include "vulkan/vulkan_core.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>

void CreateDeviceAndCommandQueue(void);
void CreateCommandPool(void);

void DestroyCommandPoolAndLogicalDevice(void);

extern VkDevice LogicalDevice;
extern VkQueue ComputingQueue;
extern VkCommandPool CommandPool;

uint32_t computeQueueFamilyIndex;
