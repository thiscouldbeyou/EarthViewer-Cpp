#include "SceneManager.hpp"

SceneManager::SceneManager(SceneLabel initial)
    : mScenes(),
      mCurrentScene(initial)
{
    mScenes.reserve((Size)SceneLabel::MAX_SCENE_COUNT);
    mScenes.push_back(nullptr);
    mScenes.push_back(nullptr /*Start Menu*/);
    mScenes.push_back(new GameScene());
}

SceneManager::~SceneManager()
{
    for (auto scene : mScenes)
        if (scene)
            delete scene;
}

auto SceneManager::SetScene(SceneLabel scene) -> void
{
    assert((Size)scene);
    assert((Size)mCurrentScene);
    mScenes[(Size)mCurrentScene]->Detach();
    mCurrentScene = scene;
    mScenes[(Size)scene]->Attach();
}

auto SceneManager::Update(Timestep timestep) -> void
{
    assert((Size)mCurrentScene);
    mScenes[(Size)mCurrentScene]->Update(timestep);
}

auto SceneManager::Render() -> void
{
    assert((Size)mCurrentScene);
    mScenes[(Size)mCurrentScene]->Render();
}