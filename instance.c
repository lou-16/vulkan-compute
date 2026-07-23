#include "instance.h"
#include "vulkan/vk_platform.h"
#include "vulkan/vulkan_core.h"
#include <stdio.h>
#include <string.h>

VkPhysicalDevice PhysicalDevice = VK_NULL_HANDLE;
VkInstance Instance = VK_NULL_HANDLE;

void GetPhysicalDevice()
{
    VkPhysicalDevice devices[100];
    uint32_t count = 100;

    if(Instance == VK_NULL_HANDLE){
        printf("instance is VK_NULL_HANDLE");
        return;
    }

    if(vkEnumeratePhysicalDevices(Instance, &count, devices) != VK_SUCCESS){
        printf("enumerating physical devices failed");
    }

    PhysicalDevice = devices[0];
    VkPhysicalDeviceProperties physicalDeviceProperties;
    VkPhysicalDeviceFeatures physicalDeviceFeatures;

    vkGetPhysicalDeviceProperties(PhysicalDevice, &physicalDeviceProperties);
    vkGetPhysicalDeviceFeatures(PhysicalDevice, &physicalDeviceFeatures);

    printf("device name: %s\n", physicalDeviceProperties.deviceName);

}

void CreateInstance()
{
    VkInstanceCreateInfo CreateInfo;
    memset(&CreateInfo, 0, sizeof(CreateInfo));

    const char* vkLayers[] = { "VK_LAYER_KHRONOS_validation" };

    CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    CreateInfo.ppEnabledExtensionNames = vkLayers;
    CreateInfo.enabledLayerCount = 1;

    if(vkCreateInstance(&CreateInfo, NULL, &Instance) != VK_SUCCESS){
        printf("failed to create vulkan instance");
    };
}
