#include "window_handler.hpp"

#ifdef _WIN32
#define GLFW_EXPOSE_NATIVE_WIN32
#endif

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <functional>
#include <vector>

namespace WindowHandler {
static GLFWwindow *window;

static std::vector<KeyCallbackPFN> keyCallbacks;
static std::vector<CursorPosCallbackPFN> cursorPosCallbacks;
static std::vector<MouseButtonCallbackPFN> mouseButtonCallbacks;

static bool *framebufferResizeCallbackSignal = nullptr;
static void framebufferResizeCallback(GLFWwindow *, int, int) {
  if (framebufferResizeCallbackSignal == nullptr)
    return;

  *framebufferResizeCallbackSignal = true;
}

static void KeyCallback(GLFWwindow *w, int key, int scancode, int action,
                        int mods) {
  for (size_t i = 0; i < keyCallbacks.size(); ++i)
    keyCallbacks[i](key, scancode, action, mods);
}

static void CursorPosCallback(GLFWwindow *w, double xpos, double ypos) {
  for (size_t i = 0; i < cursorPosCallbacks.size(); ++i)
    cursorPosCallbacks[i](xpos, ypos);
}

static void MouseButtonCallback(GLFWwindow *w, int button, int action,
                                int mods) {
  for (size_t i = 0; i < mouseButtonCallbacks.size(); ++i)
    mouseButtonCallbacks[i](button, action, mods);
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

  glfwSetKeyCallback(window, KeyCallback);
  glfwSetCursorPosCallback(window, CursorPosCallback);
  glfwSetMouseButtonCallback(window, MouseButtonCallback);
}

void GetFramebufferSize(int *width, int *height) {
  glfwGetFramebufferSize(window, width, height);
}

void SetFramebufferSizeCallbackSignal(bool *callback) {
  framebufferResizeCallbackSignal = callback;
}

void *GetHandle() { return getWindowHandle(); }

void AddKeyCallback(KeyCallbackPFN callback) {
  keyCallbacks.push_back(callback);
}

void RemoveKeyCallback(KeyCallbackPFN callback) {
  for (size_t i = 0; i < keyCallbacks.size(); ++i) {
    if (keyCallbacks[i] == callback) {
      keyCallbacks.erase(keyCallbacks.begin() + i);
      return;
    }
  }
}

void AddCursorPosCallback(CursorPosCallbackPFN callback) {
  cursorPosCallbacks.push_back(callback);
}

void RemoveCursorPosCallback(CursorPosCallbackPFN callback) {
  for (size_t i = 0; i < cursorPosCallbacks.size(); ++i) {
    if (cursorPosCallbacks[i] == callback) {
      cursorPosCallbacks.erase(cursorPosCallbacks.begin() + i);
      return;
    }
  }
}

void AddMouseButtonCallback(MouseButtonCallbackPFN callback) {
  mouseButtonCallbacks.push_back(callback);
}

void RemoveMouseButtonCallback(MouseButtonCallbackPFN callback) {
  for (size_t i = 0; i < mouseButtonCallbacks.size(); ++i) {
    if (mouseButtonCallbacks[i] == callback) {
      mouseButtonCallbacks.erase(mouseButtonCallbacks.begin() + i);
      return;
    }
  }
}

void CaptureMouse() {
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void HideMouse() { glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); }

void ReleaseMouse() {
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

bool Update() {
  glfwPollEvents();

  return !glfwWindowShouldClose(window);
}

void Shutdown() {
  glfwDestroyWindow(window);

  glfwTerminate();
}
} // namespace WindowHandler
