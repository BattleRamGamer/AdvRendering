#include "../../glm.hpp"

#include "LightMaterial.hpp"
#include "../core/Texture.hpp"
#include "../core/Light.hpp"
#include "../core/World.hpp"
#include "../core/Mesh.hpp"
#include "../core/GameObject.hpp"
#include "../core/ShaderProgram.hpp"
#include "../config.hpp"

ShaderProgram* LightMaterial::_shader = NULL;

GLint LightMaterial::_uMVPMatrix = 0;
GLint LightMaterial::_uDiffuseColor = 0;

GLint LightMaterial::_aVertex = 0;
GLint LightMaterial::_aNormal = 0;
GLint LightMaterial::_aUV = 0;

LightMaterial::LightMaterial(glm::vec3 pDiffuseColor):_diffuseColor(pDiffuseColor) {
    _lazyInitializeShader();
}

LightMaterial::~LightMaterial() {}

void LightMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"light.vert");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"light.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
        _uDiffuseColor = _shader->getUniformLocation("diffuseColor");

        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");
    }
}

void LightMaterial::setDiffuseColor(glm::vec3 pDiffuseColor) {
    _diffuseColor = pDiffuseColor;
}

void LightMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    //if (!_diffuseTexture) return;

    _shader->use();

    //Print the number of lights in the scene and the position of the first light.
    //It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
    //if (pWorld->getLightCount() > 0) {
    //    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
    //}

    /**
    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    //bind the texture to the current active slot
    glBindTexture(GL_TEXTURE_2D, _diffuseColor->getId());
    //tell the shader the texture slot for the diffuse texture is slot 0
    glUniform1i (_uDiffuseColor, 0);/**/

    glUniform3f(_uDiffuseColor, _diffuseColor.r, _diffuseColor.g, _diffuseColor.b);


    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
    glUniformMatrix4fv ( _uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
