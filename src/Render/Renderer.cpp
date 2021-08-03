#include "Renderer.hpp"

#include "Resourses/Textures/Texture.hpp"

auto Renderer::RenderPlanet(Planet &planet, Ref<PlanetShader> shader, OrbitalCamera &camera) -> void
{
    auto mesh = planet.GetMesh();

    // Setup flags
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    mesh->Bind();
    shader->Start();

    glm::mat4 model = planet.GenerateModelMatrix();
    shader->LoadMatrix4(shader->mModelLoc, model);
    shader->LoadMatrix4(shader->mViewLoc, camera.GetViewMatrix());
    shader->LoadMatrix4(shader->mProjLoc, camera.GetProjMatrix());
    shader->LoadMatrix4(shader->mReverseModelLoc, glm::inverse(model));
    shader->LoadFloat3(shader->mCameraPositionLoc, camera.GenerateCartesianPosition());
    shader->LoadInt(shader->mAlbetoSamplerLoc, 0);

    glActiveTexture(GL_TEXTURE0);
    auto texture = TextureManager::GetTexture(AppTextures2D::STONE_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, texture->GetTextureHandle());

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glPointSize(12);
    glPolygonMode(GL_FRONT_AND_BACK, GL_QUADS);
    glDrawElements(GL_PATCHES, mesh->GetLength(), GL_UNSIGNED_INT, NULL);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    shader->Stop();
    mesh->Unbind();
}

auto Renderer::RenderSkybox(Skybox &skybox, Ref<SkyboxShader> shader, OrbitalCamera &camera) -> void
{
    auto mesh = skybox.GetMesh();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader->Start();
    mesh->Bind();

    //const glm::mat4 model = skybox.GenerateModelMatrix();
    //shader->LoadMatrix4(shader->mModelLoc, model);
    glm::mat4 view_without_translation = glm::mat4(glm::mat3(camera.GetViewMatrix()));
    shader->LoadMatrix4(shader->mViewLoc, view_without_translation);
    shader->LoadMatrix4(shader->mProjLoc, camera.GetProjMatrix());
    shader->LoadInt(shader->mAlbetoSamplerLoc, 0);

    glActiveTexture(GL_TEXTURE0);
    auto texture = TextureManager::GetTexture(AppTexturesCubemap::GALAXY_CUBEMAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture->GetTextureHandle());

    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, mesh->GetLength());

    glDisableVertexAttribArray(0);

    shader->Stop();
    mesh->Unbind();
}

auto Renderer::RenderUI() -> void
{
}