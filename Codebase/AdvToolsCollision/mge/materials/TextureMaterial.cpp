#include "../../glm.hpp"

#include "TextureMaterial.hpp"
#include "../core/Texture.hpp"
#include "../core/Light.hpp"
#include "../core/World.hpp"
#include "../core/Mesh.hpp"
#include "../core/GameObject.hpp"
#include "../core/ShaderProgram.hpp"
#include "../config.hpp"
#include "../core/Camera.hpp"

ShaderProgram* TextureMaterial::_shader = NULL;

GLint TextureMaterial::_uMVPMatrix = 0;
GLint TextureMaterial::_uDiffuseTexture = 0;

GLint TextureMaterial::_uSplatTexture1 = 0;
GLint TextureMaterial::_uSplatTexture2 = 0;
GLint TextureMaterial::_uSplatTexture3 = 0;
GLint TextureMaterial::_uSplatTexture4 = 0;
GLint TextureMaterial::_uHeightmapTexture = 0;

GLint TextureMaterial::_aVertex = 0;
GLint TextureMaterial::_aNormal = 0;
GLint TextureMaterial::_aUV = 0;

TextureMaterial::TextureMaterial(Texture * pDiffuseTexture):_diffuseTexture(pDiffuseTexture) {
    // hard coding the textures
    addSplatTexture(Texture::load(config::MGE_TEXTURE_PATH + "diffuse1.jpg"), 0);
    addSplatTexture(Texture::load(config::MGE_TEXTURE_PATH + "diffuse2.jpg"), 1);
    addSplatTexture(Texture::load(config::MGE_TEXTURE_PATH + "diffuse3.jpg"), 2);
    addSplatTexture(Texture::load(config::MGE_TEXTURE_PATH + "diffuse4.jpg"), 3);
    _heightmapTexture = Texture::load(config::MGE_TEXTURE_PATH + "heightmap.png");
    _lazyInitializeShader();
}

TextureMaterial::~TextureMaterial() {}

void TextureMaterial::_lazyInitializeShader() {
    if (!_shader) {
        _shader = new ShaderProgram();
        _shader->addShader(GL_VERTEX_SHADER, config::MGE_SHADER_PATH+"texture.vert");
        _shader->addShader(GL_FRAGMENT_SHADER, config::MGE_SHADER_PATH+"texture.fs");
        _shader->finalize();

        //cache all the uniform and attribute indexes
        _uMVPMatrix = _shader->getUniformLocation("mvpMatrix");
        _uDiffuseTexture = _shader->getUniformLocation("diffuseTexture");

        _uSplatTexture1 = _shader->getUniformLocation("splatTexture1");
        _uSplatTexture2 = _shader->getUniformLocation("splatTexture2");
        _uSplatTexture3 = _shader->getUniformLocation("splatTexture3");
        _uSplatTexture4 = _shader->getUniformLocation("splatTexture4");
        _uHeightmapTexture = _shader->getUniformLocation("heightmap");


        _aVertex = _shader->getAttribLocation("vertex");
        _aNormal = _shader->getAttribLocation("normal");
        _aUV =     _shader->getAttribLocation("uv");

        printf("Vertex location: %i\n", _aVertex);
        printf("Normal location: %i\n", _aNormal);
        printf("UV location: %i\n", _aUV);

        //_aNormal = 1;
    }
}

void TextureMaterial::setDiffuseTexture (Texture* pDiffuseTexture) {
    _diffuseTexture = pDiffuseTexture;
}

void TextureMaterial::addSplatTexture(Texture* pTexture, int nr) {
    switch (nr) {
    case 0:
        _splatTexture1 = pTexture;
        break;
    case 1:
        _splatTexture2 = pTexture;
        break;
    case 2:
        _splatTexture3 = pTexture;
        break;
    case 3:
        _splatTexture4 = pTexture;
        break;
    }
}

void TextureMaterial::render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) {
    if (!_diffuseTexture) return;

    _shader->use();
    
    //Print the number of lights in the scene and the position of the first light.
    //It is not used, but this demo is just meant to show you THAT materials can access the lights in a world
    //if (pWorld->getLightCount() > 0) {
    //    std::cout << "TextureMaterial has discovered light is at position:" << pWorld->getLightAt(0)->getLocalPosition() << std::endl;
    //}


    int lightCount = pWorld->getLightCount();

    GLuint lCount = _shader->getUniformLocation("lightCount");
    glUniform1i(lCount, lightCount);


    for (int i = 0; i < lightCount; i++) 
    {
        GLuint lIntensity = _shader->getUniformLocation("lights[" + std::to_string(i) + "].ambientIntensity");
        GLuint lColor = _shader->getUniformLocation("lights[" + std::to_string(i) + "].lightColor");
        GLuint lPos = _shader->getUniformLocation("lights[" + std::to_string(i) + "].lightPos");


        float intensity = pWorld->getLightAt(i)->getAmbIntensity();
        glm::vec3 color = pWorld->getLightAt(i)->getColor();
        glm::vec3 pos = pWorld->getLightAt(i)->getLocalPosition();

        //color = glm::vec3(1, 1, .5f);
        //printf("%i\n", _aNormal);

        glUniform1f(lIntensity, intensity);
        glUniform3f(lColor, color.x, color.y, color.z);
        glUniform3f(lPos, pos.x, pos.y, pos.z);
        //glBindBuffer(GL_ARRAY_BUFFER, lColor);
        //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3), &color, GL_STATIC_DRAW);


    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);



    //setup texture slot 0
    glActiveTexture(GL_TEXTURE0);
    //bind the texture to the current active slot
    glBindTexture(GL_TEXTURE_2D, _diffuseTexture->getId());
    //tell the shader the texture slot for the diffuse texture is slot 0
    glUniform1i (_uDiffuseTexture, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _splatTexture1->getId());
    glUniform1i(_uSplatTexture1, 1);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, _splatTexture2->getId());
    glUniform1i(_uSplatTexture2, 2);
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, _splatTexture3->getId());
    glUniform1i(_uSplatTexture3, 3);
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, _splatTexture4->getId());
    glUniform1i(_uSplatTexture4, 4);

    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, _heightmapTexture->getId());
    glUniform1i(_uHeightmapTexture, 5);


    //pass in a precalculate mvp matrix (see texture material for the opposite)
    glm::mat4 mvpMatrix = pProjectionMatrix * pViewMatrix * pModelMatrix;
    glUniformMatrix4fv ( _uMVPMatrix, 1, GL_FALSE, glm::value_ptr(mvpMatrix));

    glUniformMatrix4fv(_shader->getUniformLocation("modelMatrix"), 1, GL_FALSE, glm::value_ptr(pModelMatrix));
    
    glm::vec3 camPos = pWorld->getMainCamera()->getWorldPosition();

    glUniform3f(_shader->getUniformLocation("camPos"), camPos.x, camPos.y, camPos.z);

    //now inform mesh of where to stream its data
    pMesh->streamToOpenGL(_aVertex, _aNormal, _aUV);
}
