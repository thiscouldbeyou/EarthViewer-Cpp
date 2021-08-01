#ifndef __DISPlAY__
#define __DISPlAY__

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "EVSystem.hpp"
#include "Utilities/ResourseLoader.hpp"
#include "Events/Event.hpp"

using EventHandlerFn = std::function<void(Event &)>;

struct DisplaySize
{
    int mWidth;
    int mHeight;
};

class Display
{
private:
    GLFWwindow *mWindow{};

public:
    Display() = default;
    Display(GLFWwindow *window) : mWindow(window) {}

    auto Clear() -> void;
    auto Update() -> void;

    auto SetVisable(bool) -> void;
    auto SetSize(int, int) -> void;

    auto ShouldClose() const -> bool;
    auto GetSize() const -> DisplaySize;
    auto GetAspectRatio() const -> float;

    auto GetWindowHandle() -> GLFWwindow * { return mWindow; };
};

class DisplayManager
{
private:
    static std::shared_ptr<Display> sDisplay;
    static EventHandlerFn sEventHandler;

    static auto AttachCallbacks(GLFWwindow *) -> void;

    static auto WindowCloseCallback(GLFWwindow *) -> void;
    static auto WindowResizeCallback(GLFWwindow *, int, int) -> void;
    static auto WindowFramebufferResizeCallback(GLFWwindow *, int, int) -> void;
    static auto WindowContentScaleCallback(GLFWwindow *, float, float) -> void;
    static auto WindowPositionCallback(GLFWwindow *, int, int) -> void;
    static auto WindowIconifyCallback(GLFWwindow *, int) -> void;
    static auto WindowMaximizedCallback(GLFWwindow *, int) -> void;
    static auto WindowFocusCallback(GLFWwindow *, int) -> void;
    static auto WindowRefreshCallback(GLFWwindow *) -> void;
    static auto KeyCallback(GLFWwindow *, int, int, int, int) -> void;
    static auto TextCallback(GLFWwindow *, unsigned int) -> void;
    static auto CursorPositionCallback(GLFWwindow *, double, double) -> void;
    static auto CursorEnterCallback(GLFWwindow *, int) -> void;
    static auto MouseButtonCallback(GLFWwindow *, int, int, int) -> void;
    static auto ScrollCallback(GLFWwindow *, double, double) -> void;

    static auto HandleEvent(Event &) -> void;

public:
    static auto MakeDisplay(int, int, const std::string &) -> Ref<Display>;
    static auto GetDisplay(int = 0) -> Display &;
    static auto SetEventHandler(EventHandlerFn) -> void;
};

#endif