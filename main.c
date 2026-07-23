#include "compute.h"
#include "device.h"
#include "instance.h"

int main( int argc, char** argv)
{
    CreateInstance();
    GetPhysicalDevice();
    CreateDeviceAndCommandQueue();
    CreateCommandPool();
    PrepareCommandBuffer();
    compute();
    DestroyCommandPoolAndLogicalDevice();
    return 0;
}
