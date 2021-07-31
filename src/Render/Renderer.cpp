#include "Renderer.hpp"

auto Renderer::RenderPlanet(Planet &planet, Ref<PlanetShader> shader, FreeCamera camera) -> void
{
    auto mesh = planet.GetMesh();

    glEnable(GL_DEPTH_TEST);
    
    shader->Start();
    mesh->Bind();

    camera.UpdateViewMatrix();
    camera.UpdateProjMatrix();
    shader->LoadMatrix4(shader->mModelLoc, planet.GenerateModelMatrix());
    shader->LoadMatrix4(shader->mViewLoc, camera.GetViewMatrix());
    shader->LoadMatrix4(shader->mProjLoc, camera.GetProjMatrix());
    shader->LoadFloat3(shader->mCameraPositionLoc, camera.GetPosition());

    glEnableVertexAttribArray(0);

    glPointSize(12);
    glPolygonMode(GL_FRONT_AND_BACK, GL_QUADS);
    glDrawElements(GL_PATCHES, mesh->mLength, GL_UNSIGNED_INT, NULL);
    //glDrawElements(GL_TRIANGLES, mesh->mLength, GL_UNSIGNED_INT, NULL);

    glDisableVertexAttribArray(0);

    mesh->Unbind();
    shader->Stop();
}

auto Renderer::RenderSkybox() -> void
{
}

auto Renderer::RenderUI() -> void
{
}