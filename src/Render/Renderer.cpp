#include "Renderer.hpp"

auto Renderer::RenderPlanet(Planet &planet, Ref<PlanetShader> shader, OrbitalCamera &camera) -> void
{
    auto mesh = planet.GetMesh();

    // Setup flags
    glEnable(GL_DEPTH_TEST);
    
    mesh->Bind();
    shader->Start();

    camera.UpdateViewMatrix();
    //camera.UpdateProjMatrix();
    glm::mat4 model = planet.GenerateModelMatrix();
    shader->LoadMatrix4(shader->mModelLoc, model);
    shader->LoadMatrix4(shader->mViewLoc, camera.GetViewMatrix());
    shader->LoadMatrix4(shader->mProjLoc, camera.GetProjMatrix());
    shader->LoadMatrix4(shader->mReverseModelLoc, glm::inverse(model));
    shader->LoadFloat3(shader->mCameraPositionLoc, camera.GenerateCartesianPosition());

    glEnableVertexAttribArray(0);

    glPointSize(12);
    glPolygonMode(GL_FRONT_AND_BACK, GL_QUADS);
    glDrawElements(GL_PATCHES, mesh->mLength, GL_UNSIGNED_INT, NULL);

    glDisableVertexAttribArray(0);

    shader->Stop();
    mesh->Unbind();
}

auto Renderer::RenderSkybox() -> void
{
}

auto Renderer::RenderUI() -> void
{
}