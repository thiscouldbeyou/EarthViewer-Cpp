#include <cstdio>

#include "EarthViewer.hpp"
#include "Resourses/Textures/Texture.hpp"

/*
	- Maintence
	- Textures
	- Frame Buffers
	- Normals
	- Skybox
*/

auto main() -> int
{
	GLFWLoader::Initialize();
	Ref<Display> display = DisplayManager::MakeDisplay(720, 480, "EarthViewer");

	GLEWLoader::Initialize();
	GLEWLoader::SetPatchVertices(4);

	TextureManager::Initialize();

	EarthViewer game;
	DisplayManager::SetEventHandler([&game](Event &event) -> void {
		game.HandleEvent(event);
	});
	double previous = glfwGetTime();
	while (!display->ShouldClose())
	{
		double current = glfwGetTime();
		display->Clear();

		game.Update((Timestep)(current - previous));
		game.Render();

		display->Update();
		previous = current;
	}

	return 0;
}
