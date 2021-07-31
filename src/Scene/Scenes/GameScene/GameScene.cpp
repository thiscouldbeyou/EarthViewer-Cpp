#include "GameScene.hpp"

#include "Display/Display.hpp"

GameScene::GameScene()
    : mPlanet(),
      mFreeCamera(0, 0, 2, 0, 0, 0, 120, 720.0f / 480.0f, 0.01, 100),
      mPlanetShader(std::make_shared<PlanetShader>())
{
}

GameScene::~GameScene()
{
}

void GameScene::Attach()
{
}

void GameScene::Detach()
{
}

void GameScene::Update(Timestep timestep)
{
    Display &display = DisplayManager::GetDisplay();
    GLFWwindow *win = display.GetWindowHandle();
    mPlanet.Update(timestep);

    float speed = 0.5;
    if(glfwGetKey(win, GLFW_KEY_LEFT_CONTROL))
    {
        speed *= 10;
    }

    if (glfwGetKey(win, GLFW_KEY_W))
    {
        mFreeCamera.Move(0, 0, speed * timestep);
    }
    if (glfwGetKey(win, GLFW_KEY_S))
    {
        mFreeCamera.Move(0, 0, -speed * timestep);
    }
    if (glfwGetKey(win, GLFW_KEY_A))
    {
        mFreeCamera.Move(speed * timestep, 0, 0);
    }
    if (glfwGetKey(win, GLFW_KEY_D))
    {
        mFreeCamera.Move(-speed * timestep, 0, 0);
    }
    if (glfwGetKey(win, GLFW_KEY_SPACE))
    {
        mFreeCamera.Move(0, speed * timestep, 0);
    }
    if (glfwGetKey(win, GLFW_KEY_LEFT_SHIFT))
    {
        mFreeCamera.Move(0, -speed * timestep, 0);
    }

    static double x, y;
    static double ox, oy;
    static double dx, dy;
    glfwGetCursorPos(win, &x, &y);
    dx = x - ox;
    dy = y - oy;
    ox = x;
    oy = y;
    x = 0;
    y = 0;
    if (glfwGetMouseButton(win, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        float speed = 5;
        float scale = speed * timestep;
        mFreeCamera.Rotate(dy * scale, dx * scale, 0);
    }

    //mFreeCamera.Rotate(0, 0.1 * timestep, 0);
}

void GameScene::Render()
{
    mRenderer.RenderPlanet(mPlanet, mPlanetShader, mFreeCamera);
}