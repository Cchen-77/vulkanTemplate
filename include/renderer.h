#ifndef RENDERER_H
#define RENDERER_H
#include"imgui.h"
#include"imgui_impl_vulkan.h"
#include"imgui_impl_sdl2.h"
#include"vulkan/vulkan.hpp"
#define SDL_MAIN_HANDLED
#include"SDL.h"
#include"SDL_vulkan.h"

#include<vector>
#include<optional>
struct QueueFamiliyIndices{
    std::optional<uint32_t> graphicQueueFamily;
    std::optional<uint32_t> computeQueueFamily;
    std::optional<uint32_t> presentQueueFamily;
    bool complete(){
        return graphicQueueFamily.has_value()&&computeQueueFamily.has_value()&&presentQueueFamily.has_value();
    }
};
struct SwapchainDetails{
    vk::SurfaceFormatKHR format;
    vk::SurfaceCapabilitiesKHR capabilities;
    vk::PresentModeKHR presentMode;
    vk::Extent2D extent;
};
class Renderer{
public:
    Renderer();
    ~Renderer();
public:
    void init();
    void tick();
    void cleanup();
private:
    void initSDL();
    void initVkInstance();
    void initDLD();
    void initDebugMessenger();
    void initSurface();
    void initLogicalDevice();
    void initSwapchain();
    void reinitSwapchain();
    void initCommandPool();
    void initDescriptorPool();
    void initRenderPass();
    void initFramebuffer();
    void initSyncObjects();
    void initImGui();
private:
    static void checkVkResult(VkResult result);
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugMessengerCallback(
    VkDebugUtilsMessageSeverityFlagBitsEXT           messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT                  messageTypes,
    const VkDebugUtilsMessengerCallbackDataEXT*      pCallbackData,
    void*                                            pUserData);
private:
    uint32_t getInstanceLayers(std::vector<const char*>& layers);
    uint32_t getInstanceExts(std::vector<const char*>& exts);
    void pickPhysicalDevice();
    bool checkPhysicalDevice(vk::PhysicalDevice pdevice);
    bool pickQueueFamilies(vk::PhysicalDevice pdevice);
    uint32_t getDeviceLayers(std::vector<const char*>& layers);
    uint32_t getDeviceExts(std::vector<const char*>& exts);
    void getDeviceFeatures(vk::PhysicalDeviceFeatures& features);
    void getSwapchainDetails();
    vk::ImageView createImageView(vk::Image image,vk::Format format,vk::ImageAspectFlags aspectMask);
private:
    SDL_Window* sdlWindow;
private:
    vk::DispatchLoaderDynamic dld;
    vk::Instance vkInstance;
    vk::SurfaceKHR surface;
    vk::DebugUtilsMessengerEXT debugMessenger;
    vk::PhysicalDevice pDevice;
    vk::Device lDevice;
    QueueFamiliyIndices queueFamilyIndices;
    vk::Queue graphicQueue;
    vk::Queue computeQueue;
    vk::Queue presentQueue;
    vk::SwapchainKHR swapchain;
    SwapchainDetails swapchainDetails;
    std::vector<vk::Image> swapchainImages;
    std::vector<vk::ImageView> swapchainImageViews;
    vk::CommandPool graphicCommandPool;
    vk::CommandPool computeCommandPool;
    vk::DescriptorPool descriptorPool;
    vk::RenderPass imguiRenderPass;
    std::vector<vk::Framebuffer> imguiFrameBuffers;

    vk::Semaphore imageAvaliable;
    vk::Semaphore renderingFinished;
    vk::Fence inflightFence;
};
#endif