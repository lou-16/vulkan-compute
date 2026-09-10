#include "instance.h"
#include "vulkan/vk_platform.h"
#include "log.h"
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
        Log("info","instance is VK_NULL_HANDLE\n");
        return;
    }

    VkResult result = vkEnumeratePhysicalDevices(Instance, &count, devices);

    if(result != VK_SUCCESS){
        Log("info","enumerating physical devices failed with error: %d\n", result);
    }

    PhysicalDevice = devices[0];

    VkPhysicalDeviceProperties physicalDeviceProperties;
    VkPhysicalDeviceFeatures physicalDeviceFeatures;

    vkGetPhysicalDeviceProperties(PhysicalDevice, &physicalDeviceProperties);
    vkGetPhysicalDeviceFeatures(PhysicalDevice, &physicalDeviceFeatures);

    Log("info","device name: %s\n", physicalDeviceProperties.deviceName);

}

void CreateInstance()
{
    VkInstanceCreateInfo CreateInfo;
    memset(&CreateInfo, 0, sizeof(CreateInfo));
;
    const char* vkExtensions[] = {
        "VK_KHR_portability_enumeration"
    };

    const char* vkLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    CreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    CreateInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    CreateInfo.enabledExtensionCount = 1;
    CreateInfo.ppEnabledExtensionNames = vkExtensions;
    CreateInfo.enabledLayerCount = 1;
    CreateInfo.ppEnabledLayerNames = &vkLayers;


    VkResult result = vkCreateInstance(&CreateInfo, NULL, &Instance);

    if(result != VK_SUCCESS){
        Log("info","failed to create vulkan instance with error: %d\n", result);
    };
}
