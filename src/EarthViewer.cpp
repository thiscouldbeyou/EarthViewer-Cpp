#include "EarthViewer.hpp"

EarthViewer::EarthViewer()
    : mSceneManager(SceneLabel::GAME_SCENE)
{
}

EarthViewer::~EarthViewer()
{
}

auto EarthViewer::Update(Timestep Timestep) -> void
{
    mSceneManager.Update(Timestep);
}

void EarthViewer::Render()
{
    mSceneManager.Render();
}