// KytyPS5-Lite — Vulkan Host GPU Backend
// Targets Vulkan 1.3

#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <string>

namespace kyty {

class HostGPU {
public:
    HostGPU();
    ~HostGPU();

    bool Initialize();
    void Shutdown();
    void Present();

    // Shader recompilation entry point
    bool RecompileShader(const uint8_t* spirv, size_t size);

private:
    VkInstance instance_ = VK_NULL_HANDLE;
    VkPhysicalDevice physical_device_ = VK_NULL_HANDLE;
    VkDevice device_ = VK_NULL_HANDLE;
    VkQueue graphics_queue_ = VK_NULL_HANDLE;
    VkSwapchainKHR swapchain_ = VK_NULL_HANDLE;

    std::vector<VkImage> swapchain_images_;
    VkFormat swapchain_format_ = VK_FORMAT_B8G8R8A8_SRGB;
    VkExtent2D swapchain_extent_ = {1280, 720};

    bool CreateInstance();
    bool PickPhysicalDevice();
    bool CreateLogicalDevice();
    bool CreateSwapchain();
};

} // namespace kyty
