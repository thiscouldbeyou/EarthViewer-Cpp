#include "Display.hpp"

#include "EarthViewer.hpp"
#include "Events/Event.hpp"

std::shared_ptr<Display> DisplayManager::sDisplay{};
EventHandlerFn DisplayManager::sEventHandler{};

auto DisplayManager::HandleEvent(Event &event) -> void
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowResizeEvent>(
        [&](WindowResizeEvent &event) -> bool
        {
            printf("Screen Resize Event: [%d, %d]\n", event.mWidth, event.mHeight);
            glViewport(0, 0, event.mWidth, event.mHeight);
            return false;
        });
    sEventHandler(event);
}

auto DisplayManager::MakeDisplay(int width, int height, const std::string &title) -> Ref<Display>
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    GLFWwindow *window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == nullptr)
    {
        fprintf(stderr, "Failed to open GLFW window!\n");
        glfwTerminate();
        exit(1);
    }

    glfwMakeContextCurrent(window);

    AttachCallbacks(window);

    sDisplay = std::make_shared<Display>(window);
    sDisplay->SetVisable(true);
    return sDisplay;
}

auto DisplayManager::GetDisplay(int id) -> Display &
{
    return *sDisplay.get();
}

auto DisplayManager::SetEventHandler(EventHandlerFn func) -> void
{
    sEventHandler = func;
}

auto Display::Clear() -> void
{
    //glClearColor(0.2, 0.4, 0.8, 1.0);
    glClearColor(0.1, 0.1, 0.1, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

auto Display::Update() -> void
{
    glfwPollEvents();
    glfwSwapBuffers(mWindow);
}

auto Display::SetVisable(bool visible) -> void
{
    if (visible)
        glfwShowWindow(mWindow);
    else
        glfwHideWindow(mWindow);
}

auto Display::SetSize(int width, int height) -> void
{
    glfwSetWindowSize(mWindow, width, height);
}

auto Display::ShouldClose() const -> bool
{
    return glfwWindowShouldClose(mWindow);
}

auto Display::GetSize() const -> DisplaySize
{
    DisplaySize res;
    glfwGetWindowSize(mWindow, &res.mWidth, &res.mHeight);
    return res;
}

auto Display::GetAspectRatio() const -> float
{
    DisplaySize size = GetSize();
    return (float) size.mWidth / (float) size.mHeight;
}