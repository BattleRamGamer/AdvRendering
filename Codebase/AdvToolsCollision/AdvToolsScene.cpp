
#include <iostream>
#include <string>

#include "glm.hpp"

#include "mge/core/Renderer.hpp" //
#include "mge/core/Mesh.hpp" //
#include "mge/core/World.hpp" //
#include "mge/core/Texture.hpp" //
#include "mge/core/Light.hpp" //
#include "mge/core/Camera.hpp"  //
#include "mge/core/GameObject.hpp" //
#include "mge/materials/AbstractMaterial.hpp" //
#include "mge/materials/ColorMaterial.hpp" //
#include "mge/materials/TextureMaterial.hpp" //
#include "mge/behaviours/RotatingBehaviour.hpp" //
#include "mge/behaviours/KeysBehaviour.hpp" //
#include "mge/behaviours/FollowBehaviour.hpp"
#include "mge/util/DebugHud.hpp" //
#include "mge/config.hpp" //
#include "AdvToolsScene.hpp"
#include "MoveBehaviour.hpp"
#include "Collider.hpp"
#include "CollisionManager.hpp"
#include "DataTracker.hpp"

#include <fstream>

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
AdvToolsScene::AdvToolsScene() :AbstractGame(), _hud(0), _collisionManager(0), _dataTracker(0)
{
}

void AdvToolsScene::initialize() {

    //setup the core part
    AbstractGame::initialize();

    //setup the custom part so we can display some text
    std::cout << "Initializing HUD" << std::endl;
    _hud = new DebugHud(_window);
    std::cout << "HUD initialized." << std::endl << std::endl;
}

//build the game _world
void AdvToolsScene::_initializeScene()
{




    _collisionManager = new CollisionManager();
    _dataTracker = new DataTracker();
    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
    Mesh* discMesh = Mesh::load(config::MGE_MODEL_PATH + "disk.obj");


    //MATERIALS

    AbstractMaterial* colourMaterial = new ColorMaterial(glm::vec3(1, 0, 1));

    //SCENE SETUP

   //add camera first (it will be updated last)
    Camera* camera = new Camera("camera", glm::vec3(0, 50, 0));
    camera->rotate(-glm::pi<float>()/2, glm::vec3(1, 0, 0));
    _world->add(camera);
    _world->setMainCamera(camera);

    for (int i = 0; i < config::CIRCLE_COLLIDER_AMOUNT; i++) {
        
        float xPos = glm::linearRand(-config::BOUNDARY_POSITION, config::BOUNDARY_POSITION);
        float zPos = glm::linearRand(-config::BOUNDARY_POSITION, config::BOUNDARY_POSITION);
        float dir = glm::linearRand(0, 360);

        GameObject* obj = new GameObject("col", glm::vec3(xPos, 0, zPos));
        obj->scale(glm::vec3(1, 1, 1));
        obj->setBehaviour(new MoveBehaviour(.1f, dir));
        _world->add(obj);

        Collider* collider = new Collider(1, false); // false
        collider->setMesh(discMesh);                // discMesh
        collider->setMaterial(colourMaterial);
        collider->setParent(obj);
        _collisionManager->addCollider(collider);
    }

    for (int i = 0; i < config::AABB_COLLIDER_AMOUNT; i++) {

        float xPos = glm::linearRand(-config::BOUNDARY_POSITION, config::BOUNDARY_POSITION);
        float zPos = glm::linearRand(-config::BOUNDARY_POSITION, config::BOUNDARY_POSITION);
        float dir = glm::linearRand(0, 360);

        GameObject* obj = new GameObject("col", glm::vec3(xPos, 0, zPos));
        obj->scale(glm::vec3(1, 1, 1));
        obj->setBehaviour(new MoveBehaviour(.1f, dir));
        _world->add(obj);

        Collider* collider = new Collider(1, true); // false
        collider->setMesh(planeMeshDefault);                // discMesh
        collider->setMaterial(colourMaterial);
        collider->setParent(obj);
        _collisionManager->addCollider(collider);
    }

    /**
    //add the floor
    GameObject* disc = new GameObject("disc", glm::vec3(0, 0, 0));
    disc->scale(glm::vec3(1, 1, 1));
    disc->setMesh(discMesh);
    disc->setMaterial(colourMaterial);
    disc->setBehaviour(new MoveBehaviour(.1f, 90));
    _world->add(disc);

    Collider* collider = new Collider(1);
    collider->setParent(disc);
    _collisionManager->addCollider(collider);



    GameObject* polygon = new GameObject("polygon", glm::vec3(0, 0, 0));
    polygon->scale(glm::vec3(1, 1, 1));
    polygon->setMesh(planeMeshDefault);
    polygon->setMaterial(lightMaterial);
    _world->add(polygon);

    Collider* collider2 = new Collider(1);
    collider2->setParent(polygon);
    _collisionManager->addCollider(collider2);
    /**/
    
    /**
    //add a spinning sphere
    GameObject* sphere = new GameObject("sphere", glm::vec3(0, 0, 0));
    sphere->scale(glm::vec3(2.5, 2.5, 2.5));
    sphere->setMesh(sphereMeshS);
    sphere->setMaterial(runicStoneMaterial);
    sphere->setBehaviour(new RotatingBehaviour());
    _world->add(sphere);
    /**/

    /**
    Light* light = new Light("light", glm::vec3(0, 3, 0));
    light->scale(glm::vec3(0.1f, 0.1f, 0.1f));
    light->setMesh(cubeMeshF);
    light->setMaterial(lightMaterial);
    light->setBehaviour(new KeysBehaviour(25));
    _world->add(light);


    GameObject* childSphere = new GameObject("childSphere", glm::vec3(0, -4, 0));
    childSphere->scale(glm::vec3(2.2f, 2.2f, 2.2f));
    childSphere->setMesh(sphereMeshS);
    childSphere->setMaterial(colourMaterial);
    childSphere->setParent(light);

    /**/

    //DataTracker dTracker = DataTracker();
    //camera->setBehaviour(new FollowBehaviour(light, 2));

}

void AdvToolsScene::_update(float pStep) {
    AbstractGame::_update(pStep);
}

void AdvToolsScene::_render() {
    AbstractGame::_render();
    _updateHud();
}

void AdvToolsScene::_updateHud() {
    std::string debugInfo = "";

    int colCount = _collisionManager->checkCollisions();
    int testCount = _collisionManager->getTestAmount();
    debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";
    debugInfo += std::string("Number of collisions: ") + std::to_string(colCount) + "\n";
    debugInfo += std::string("Number of tests: ") + std::to_string(testCount);

    //printf("%f\n", clockTimer.restart().asSeconds());
    _dataTracker->StoreFrameData(clockTimer.restart().asSeconds(), colCount, testCount);

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

AdvToolsScene::~AdvToolsScene()
{
    //dtor
    _dataTracker->WriteDataToFile();
}