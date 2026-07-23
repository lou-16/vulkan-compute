#include "device.h"
#include "instance.h"

VkDevice LogicalDevice = VK_NULL_HANDLE;
VkQueue ComputingQueue = VK_NULL_HANDLE;

VkCommandPool CommandPool = VK_NULL_HANDLE;

uint32_t computeQueueFamilyIndex;

void CreateDeviceAndCommandQueue()
{
    VkQueueFamilyProperties families[100];
    uint32_t count = 100;

    vkGetPhysicalDeviceQueueFamilyProperties(
    PhysicalDevice,
    &count,
    families
    );

    printf("found %d queue families", count);

    computeQueueFamilyIndex = 0;

    while ((computeQueueFamilyIndex < count) && (families[computeQueueFamilyIndex].queueFlags & VK_QUEUE_COMPUTE_BIT) == 0) {
        computeQueueFamilyIndex ++;
    }

    if(computeQueueFamilyIndex == count) {
        printf("compute queue not found");
    }

    float priority = 1.0f;

    VkDeviceQueueCreateInfo queueCreateInfo;
    memset(&queueCreateInfo, 0, sizeof(queueCreateInfo));
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = computeQueueFamilyIndex;
    queueCreateInfo.queueCount = 1;
    queueCreateInfo.pQueuePriorities = &priority;

    VkDeviceCreateInfo deviceCreateInfo;
    memset(&deviceCreateInfo, 0, sizeof(deviceCreateInfo));
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
    deviceCreateInfo.queueCreateInfoCount = 1;

    if(vkCreateDevice(PhysicalDevice, &deviceCreateInfo, NULL, &LogicalDevice) != VK_SUCCESS){
        printf("failed to create logical device");
        return;
    }

    vkGetDeviceQueue(LogicalDevice, computeQueueFamilyIndex, 0, &ComputingQueue);
}

void CreateCommandPool(){
    VkCommandPoolCreateInfo poolCreateInfo;
    memset(&poolCreateInfo, 0, sizeof(poolCreateInfo));
    poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolCreateInfo.queueFamilyIndex = computeQueueFamilyIndex;

    if(vkCreateCommandPool(LogicalDevice, &poolCreateInfo, NULL, &CommandPool) != VK_SUCCESS) {
      printf("failed to create command pool");
      return;
    };
}

void DestroyCommandPoolAndLogicalDevice() {
    if(CommandPool != VK_NULL_HANDLE){vkDestroyCommandPool(LogicalDevice, CommandPool, NULL);}
    if(LogicalDevice != VK_NULL_HANDLE){vkDestroyDevice(LogicalDevice, NULL);}
}
