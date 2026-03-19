#include <iostream>
#include <string>

#include "../glm.hpp"

#include "core/Renderer.hpp" //
#include "core/Mesh.hpp" //
#include "core/World.hpp" //
#include "core/Texture.hpp" //
#include "core/Light.hpp" //
#include "core/Camera.hpp"  //
#include "core/GameObject.hpp" //
#include "materials/AbstractMaterial.hpp" //
#include "materials/ColorMaterial.hpp" //
#include "materials/LightMaterial.hpp"
#include "materials/TextureMaterial.hpp" //
#include "behaviours/RotatingBehaviour.hpp" //
#include "behaviours/KeysBehaviour.hpp" //
#include "behaviours/FollowBehaviour.hpp"
#include "util/DebugHud.hpp" //
#include "config.hpp" //
#include "Assignment4.hpp" //

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
Assignment4::Assignment4() :AbstractGame(), _hud(0)
{
}

void Assignment4::initialize() {
    //setup the core part
    AbstractGame::initialize();

    //setup the custom part so we can display some text
    std::cout << "Initializing HUD" << std::endl;
    _hud = new DebugHud(_window);
    std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void Assignment4::_initializeScene()
{
    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
    Mesh* cubeMeshF = Mesh::load(config::MGE_MODEL_PATH + "cube_flat.obj");
    Mesh* sphereMeshS = Mesh::load(config::MGE_MODEL_PATH + "sphere_smooth.obj");
    //Mesh* teapotMesh = Mesh::load(config::MGE_MODEL_PATH + "Chaynik.obj");
    Mesh* bigPlaneMesh = Mesh::load(config::MGE_MODEL_PATH + "plane20x20_2048tris_aligned_uvs.obj");

    //MATERIALS

    //AbstractMaterial* lightMaterial = new ColorMaterial(glm::vec3(1, 1, 0));
    AbstractMaterial* lightMaterial = new LightMaterial(glm::vec3(1, 1, 0));
    AbstractMaterial* runicStoneMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "runicfloor.png"));
    AbstractMaterial* brickMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "bricks.jpg"));
    AbstractMaterial* colourMaterial = new ColorMaterial(glm::vec3(1, 0, 1));
    //AbstractMaterial* teapotMaterial = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "Chaynik.png"));
    AbstractMaterial* splatmap = new TextureMaterial(Texture::load(config::MGE_TEXTURE_PATH + "splatmap.png"));

    

    //SCENE SETUP

   //add camera first (it will be updated last)
    Camera* camera = new Camera("camera", glm::vec3(0, 0, 0));
    _world->add(camera);
    _world->setMainCamera(camera);

    //add the floor
    GameObject* plane = new GameObject("plane", glm::vec3(0, 0, 0));
    plane->scale(glm::vec3(1, 1, 1));
    plane->setMesh(bigPlaneMesh);
    plane->setMaterial(splatmap);
    _world->add(plane);

    // Sphere
    /**
    GameObject* sphere = new GameObject("sphere", glm::vec3(0, 0, 0));
    sphere->scale(glm::vec3(2.5, 2.5, 2.5));
    sphere->setMesh(sphereMeshS);
    sphere->setMaterial(runicStoneMaterial);
    sphere->setBehaviour(new RotatingBehaviour());
    _world->add(sphere);/**/

    // Light 1 (thing you control)
    Light* light = new Light("light", glm::vec3(0, 3, 0), glm::vec3(1.0f, 1.0f, 1.0f), 1);
    light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
    light->setMesh(cubeMeshF);
    light->setMaterial(lightMaterial);
    light->setBehaviour(new KeysBehaviour(25));
    _world->add(light);

    // Light 2
    /**
    Light* light2 = new Light("light2", glm::vec3(1, 4, 1), glm::vec3(.3f, .3f, .3f), 0.1f);
    light2->scale(glm::vec3(0.1f, 0.1f, 0.1f));
    light2->setMesh(cubeMeshF);
    light2->setMaterial(lightMaterial);
    _world->add(light2);/**/

    // Sphere below movable light
    GameObject* childSphere = new GameObject("childSphere", glm::vec3(0, -4, 0));
    childSphere->scale(glm::vec3(2.2f, 2.2f, 2.2f));
    childSphere->setMesh(sphereMeshS);
    childSphere->setMaterial(colourMaterial);
    childSphere->setParent(light);

    // Teapot
    /**
    GameObject* teapot = new GameObject("teapot", glm::vec3(0, 3, 5));
    teapot->scale(glm::vec3(10, 10, 10));
    teapot->setMesh(teapotMesh);
    teapot->setMaterial(teapotMaterial);
    _world->add(teapot);/**/

    camera->setBehaviour(new FollowBehaviour(light, 2));

}

void Assignment4::_render() {
    AbstractGame::_render();
    _updateHud();
}

void Assignment4::_updateHud() {
    std::string debugInfo = "";
    debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

Assignment4::~Assignment4()
{
    //dtor
}
