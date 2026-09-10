#include "compute.h"
#include "device.h"
#include "instance.h"
#include "pipeline.h"
int main( int argc, char** argv)
{
    CreateInstance();
    GetPhysicalDevice();
    CreateDeviceAndCommandQueue();
    CreatePipeline();
    CreateCommandPool();
    PrepareCommandBuffer();
    compute();
    DestroyPipeline();
    DestroyCommandPoolAndLogicalDevice();
    return 0;
}
