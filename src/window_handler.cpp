#include "window_handler.hpp"

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

namespace WindowHandler {
static GLFWwindow *window;

static bool *framebufferResizeCallbackSignal = nullptr;
static void framebufferResizeCallback(GLFWwindow *, int, int) {
  if (framebufferResizeCallbackSignal == nullptr)
    return;

  *framebufferResizeCallbackSignal = true;
}

static void *getWindowHandle();

#ifdef _WIN32
void *getWindowHandle() { return glfwGetWin32Window(window); }
#endif

void Init(uint32_t width, uint32_t height) {
  glfwInit();

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  window = glfwCreateWindow(width, height, "Vulkan", nullptr, nullptr);
  glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void GetFramebufferSize(int *width, int *height) {
  glfwGetFramebufferSize(window, width, height);
}

void SetFramebufferSizeCallbackSignal(bool *callback) {
  framebufferResizeCallbackSignal = callback;
}

void *GetHandle() { return getWindowHandle(); }

bool Update() {
  glfwPollEvents();

  return !glfwWindowShouldClose(window);
}

void Shutdown() {
  glfwDestroyWindow(window);

  glfwTerminate();
}
} // namespace WindowHandler
