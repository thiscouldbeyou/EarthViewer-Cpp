#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__

#include "Scenes/GameScene/GameScene.hpp"

enum class SceneLabel
{
    NONE,
    MAIN_SCENE,
    GAME_SCENE,
    MAX_SCENE_COUNT,
};

class SceneManager
{
private:
    std::vector<Scene *> mScenes{};
    SceneLabel mCurrentScene{};

public:
    SceneManager() = default;
    SceneManager(SceneLabel);
    ~SceneManager();

    auto SetScene(SceneLabel) -> void;

    auto Update(Timestep) -> void;
    auto Render() -> void;
};

#endif