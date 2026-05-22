
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
#include "AABB.hpp"
#include "Sphere.hpp"
#include "CollisionManager.hpp"
#include "DataTracker.hpp"

#include <fstream>

//construct the game class into _window, _renderer and hud (other parts are initialized by build)
AdvToolsScene::AdvToolsScene() :AbstractGame(), _hud(0), _collisionManager(0), _dataTracker(0), _gridManager(), _frameCount(0), _timerFinished(false)
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

    _gridManager = new GridManager();


    _collisionManager = new CollisionManager();
    _dataTracker = new DataTracker();
    //MESHES

    //load a bunch of meshes we will be using throughout this demo
    //each mesh only has to be loaded once, but can be used multiple times:
    //F is flat shaded, S is smooth shaded (normals aligned or not), check the models folder!
    Mesh* planeMeshDefault = Mesh::load(config::MGE_MODEL_PATH + "plane.obj");
    Mesh* discMesh = Mesh::load(config::MGE_MODEL_PATH + "disk.obj");


    //MATERIALS
    // Not sharing any materials so each collider can show debug information
    //AbstractMaterial* colourMaterial = new ColorMaterial(glm::vec3(1, 0, 1));

    //SCENE SETUP

   //add camera first (it will be updated last)
    Camera* camera = new Camera("camera", glm::vec3(config::BOUNDARY_SIZE*.5f, 50, config::BOUNDARY_SIZE*.5f));
    camera->rotate(-glm::pi<float>()/2, glm::vec3(1, 0, 0));
    _world->add(camera);
    _world->setMainCamera(camera);


    _world->add(_gridManager);


    for (int i = 0; i < config::CIRCLE_COLLIDER_AMOUNT; i++) {
        
        float xPos = glm::linearRand(0.0f, config::BOUNDARY_SIZE);
        float zPos = glm::linearRand(0.0f, config::BOUNDARY_SIZE);
        float dir = glm::linearRand(0, 360);

        Sphere* collider = new Sphere(xPos, zPos, 1); 
        collider->setBehaviour(new MoveBehaviour(_gridManager, .1f, dir));
        collider->setMesh(discMesh);
        collider->setMaterial(new ColorMaterial(glm::vec3(1, 0, 1)));
        _world->add(collider);
        _collisionManager->addCollider(collider);

        _gridManager->Add(collider);

    }

    for (int i = 0; i < config::AABB_COLLIDER_AMOUNT; i++) {

        float xPos = glm::linearRand(0.0f, config::BOUNDARY_SIZE);
        float zPos = glm::linearRand(0.0f, config::BOUNDARY_SIZE);
        float dir = glm::linearRand(0, 360);

        AABB* collider = new AABB(xPos, zPos, 1); 
        collider->setBehaviour(new MoveBehaviour(_gridManager, .1f, dir));
        collider->setMesh(planeMeshDefault);
        collider->setMaterial(new ColorMaterial(glm::vec3(1, 0, 1)));
        _world->add(collider);
        _collisionManager->addCollider(collider);

        _gridManager->Add(collider);

    }

}

void AdvToolsScene::_update(float pStep) {
    AbstractGame::_update(pStep);
}

void AdvToolsScene::_render() {
    /**
    if (config::USE_SPATIALPARTITIONING) {
        //_gridManager->handleCollisions();
    }
    else {
        //_collisionManager->checkCollisions();
    }
    /**/
    AbstractGame::_render();
    _updateHud();
}

void AdvToolsScene::_updateHud() {
    std::string debugInfo = "";

    int colCount = 0;
    int testCount = 0;

    if (config::USE_SPATIALPARTITIONING) {
        colCount = _gridManager->GetCollisionCount();
        testCount = _gridManager->GetTestCount();

    }
    else {
        colCount = _collisionManager->checkCollisions();
        testCount = _collisionManager->getTestAmount();
    }

    //_collisionManager->checkCollisions();


    debugInfo += std::string("Frame count: ") + std::to_string(_frameCount) + "\n";
    debugInfo += std::string("FPS:") + std::to_string((int)_fps) + "\n";
    debugInfo += std::string("Number of collisions: ") + std::to_string(colCount) + "\n";
    debugInfo += std::string("Number of tests: ") + std::to_string(testCount);

    //printf("%f\n", clockTimer.restart().asSeconds());

    _checkTimer();

    if (_timerFinished) {
        debugInfo += "\nTest is done";
    }
    else {

        const auto t2 = std::chrono::high_resolution_clock::now();

        const std::chrono::duration<double, std::ratio<1>> fp_ms = t2 - _startTime;

        _dataTracker->StoreFrameData(
            _frameCount,
            clockTimer.restart().asSeconds(), 
            fp_ms.count(),
            testCount, 
            colCount);
    }
    

    _hud->setDebugInfo(debugInfo);
    _hud->draw();
}

void AdvToolsScene::_checkTimer() {
    
    if (_timerFinished) return;

    if (config::USE_TEST_METHOD_TIME) {

        const auto t2 = std::chrono::high_resolution_clock::now();

        // integral duration: requires duration_cast
        const auto int_ms = std::chrono::duration_cast<std::chrono::seconds>(t2 - _startTime);

        int seconds = int_ms.count();

        printf("%i\n", seconds);

        if (seconds >= config::TEST_TIME) {
            _timerFinished = true;
            _dataTracker->WriteDataToFile();
            _window->close();
        }
    }
    else {
        _frameCount++;
        if (_frameCount >= config::TEST_FRAME_COUNT) {
            _timerFinished = true;
            _dataTracker->WriteDataToFile();
            _window->close();
        }
    }

}

AdvToolsScene::~AdvToolsScene()
{
    //dtor
}