#pragma once

#ifdef WINDOW_HANDLER_DLL_EXPORTS
#define WINDOW_HANDLER_EXPORTS __declspec(dllexport)
#else
#define WINDOW_HANDLER_EXPORTS __declspec(dllimport)
#endif

#include <stdint.h>

namespace WindowHandler {

using KeyCallbackPFN = void (*)(int key, int scancode, int action, int mods);
using CursorPosCallbackPFN = void (*)(double xpos, double ypos);
using MouseButtonCallbackPFN = void (*)(int button, int action, int mods);

WINDOW_HANDLER_EXPORTS void Init(uint32_t width, uint32_t height);
WINDOW_HANDLER_EXPORTS bool Update();
WINDOW_HANDLER_EXPORTS void Shutdown();

WINDOW_HANDLER_EXPORTS void GetFramebufferSize(int *width, int *height);
WINDOW_HANDLER_EXPORTS void SetFramebufferSizeCallbackSignal(bool *callback);

WINDOW_HANDLER_EXPORTS void *GetHandle();

WINDOW_HANDLER_EXPORTS void AddKeyCallback(KeyCallbackPFN callback);
WINDOW_HANDLER_EXPORTS void RemoveKeyCallback(KeyCallbackPFN callback);

WINDOW_HANDLER_EXPORTS void AddCursorPosCallback(CursorPosCallbackPFN callback);
WINDOW_HANDLER_EXPORTS void
RemoveCursorPosCallback(CursorPosCallbackPFN callback);

WINDOW_HANDLER_EXPORTS void
AddMouseButtonCallback(MouseButtonCallbackPFN callback);
WINDOW_HANDLER_EXPORTS void
RemoveMouseButtonCallback(MouseButtonCallbackPFN callback);

WINDOW_HANDLER_EXPORTS void CaptureMouse();
WINDOW_HANDLER_EXPORTS void HideMouse();
WINDOW_HANDLER_EXPORTS void ReleaseMouse();

} // namespace WindowHandler
