#pragma once

//TODO Handle window_handler as a separate lib
//include vulkan based on macro

#ifdef WINDOW_HANDLER_DLL_EXPORTS
#define WINDOW_HANDLER_EXPORTS __declspec(dllexport)
#else
#define WINDOW_HANDLER_EXPORTS __declspec(dllimport)
#endif

#include <stdint.h>

namespace WindowHandler {
void Init(uint32_t width, uint32_t height);
bool Update();
void Shutdown();

void GetFramebufferSize(int *width, int *height);
void SetFramebufferSizeCallbackSignal(bool *callback);
} // namespace WindowHandler
