#include "Light.hpp"
#include "World.hpp"

Light::Light(const std::string& pName, const glm::vec3& pPosition, const glm::vec3& aColor, const float& aIntensity)
    :GameObject(pName, pPosition), lightColor(aColor), ambientIntensity(aIntensity)
{}

Light::~Light() {
}

//Override setWorldRecursively to make sure we are registered
//to the world we are a part of.
void Light::_setWorldRecursively (World* pWorld) {

    //store the previous and new world before and after storing the given world
    World* previousWorld = _world;
    GameObject::_setWorldRecursively(pWorld);
    World* newWorld = _world;

    //check whether we need to register or unregister
    if (previousWorld != nullptr) previousWorld->unregisterLight(this);
	if (newWorld != nullptr) newWorld->registerLight(this);

}


glm::vec3 Light::getColor() const
{
    return lightColor;
}

float Light::getAmbIntensity() const 
{
    return ambientIntensity;
}
