#include <cstdio>

#include "EarthViewer.hpp"

auto main() -> int
{
	GLFWLoader::Initialize();
	Ref<Display> display = DisplayManager::MakeDisplay(720, 480, "EarthViewer");

	GLEWLoader::Initialize();
	GLint MaxPatchVertices = 0;
	glGetIntegerv(GL_MAX_PATCH_VERTICES, &MaxPatchVertices);
	printf("Max # of patches: %d\n", MaxPatchVertices);
	glPatchParameteri(GL_PATCH_VERTICES, 4);

	EarthViewer game;
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
