#ifndef LIGHTMATERIAL_HPP
#define LIGHTMATERIAL_HPP

#include <GL/glew.h>
#include "AbstractMaterial.hpp"

class ShaderProgram;
class Texture;

/**
 * This material is already a little bit more complicated, instead of a color we can pass in a texture,
 * all attributes and uniforms are cached and we precompute the MVP matrix passing it in as one entity.
 */
class LightMaterial : public AbstractMaterial
{
    public:
        LightMaterial (glm::vec3 pDiffuseColor);
        virtual ~LightMaterial ();

        virtual void render(World* pWorld, Mesh* pMesh, const glm::mat4& pModelMatrix, const glm::mat4& pViewMatrix, const glm::mat4& pProjectionMatrix) override;

        void setDiffuseColor (glm::vec3 pDiffuseColor);

    protected:
    private:
        static ShaderProgram* _shader;
        static void _lazyInitializeShader();

        //in this example we cache all identifiers for uniforms & attributes
        static GLint _uMVPMatrix;
        static GLint _uDiffuseColor;

        static GLint _aVertex ;
        static GLint _aNormal;
        static GLint _aUV ;

        glm::vec3 _diffuseColor;
        //Texture* _diffuseTexture;

        LightMaterial(const LightMaterial&);
        LightMaterial& operator=(const LightMaterial&);

};

#endif // TEXTUREMATERIAL_HPP
