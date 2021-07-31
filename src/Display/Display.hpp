#ifndef __DISPlAY__
#define __DISPlAY__

#include "EVSystem.hpp"
#include "Utilities/ResourseLoader.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

    auto GetWindowHandle() -> GLFWwindow * { return mWindow; };
};

class DisplayManager
{
private:
    static std::shared_ptr<Display> sDisplay;

    static auto AttachCallbacks(GLFWwindow *) -> void;
    static auto ResizeCallback(GLFWwindow *, int, int) -> void;

public:
    static auto MakeDisplay(int, int, const std::string &) -> Ref<Display>;
    static auto GetDisplay(int = 0) -> Display &;
};

#endif