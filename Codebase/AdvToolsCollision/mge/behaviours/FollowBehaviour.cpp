#include "FollowBehaviour.hpp"
#include "../core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics.hpp>
#include <glm/gtx/string_cast.hpp>

FollowBehaviour::FollowBehaviour(GameObject* objToFollow, float offsetDistance): 
	AbstractBehaviour(), distToObj(offsetDistance), rotLimit(glm::pi<float>() / 4.0f)
{
	this->objToFollow = objToFollow;
	xSensitivity = 100.0f;
	ySensitivity = 100.0f;
	zoomValue = 0.99f;

	xAxisRot = 0;
	yAxisRot = glm::pi<float>();
	oldMouseX = 0;
	oldMouseY = 0;
	mouseIsPressed = false;
}

FollowBehaviour::~FollowBehaviour()
{
}

void FollowBehaviour::update( float pStep )
{
	// First reset the position and rotation
	_owner->setTransform(glm::mat4(1));

	// Translate to the position of the followed object
	_owner->translate(objToFollow->getWorldPosition());
	
	// rotate() only affects look rotation and doesn't affect position
	_owner->rotate(yAxisRot, glm::vec3(0, 1, 0));
	_owner->rotate(xAxisRot, glm::vec3(1, 0, 0));
	
	// Applying offset using local right, up and forward vector. This means the z influences zoom, 
	// while x and y influence the distance between the target's center on screen and the screen center
	_owner->translate(glm::vec3(0, 0, distToObj));
	

	// Mouse controls. Hold LMB and move the mouse to rotate
	sf::Vector2i mousePos = sf::Mouse::getPosition();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		if (mouseIsPressed) {
			yAxisRot -= (mousePos.x - oldMouseX) / xSensitivity;
			xAxisRot -= (mousePos.y - oldMouseY) / ySensitivity;
		}
		else {
			mouseIsPressed = true;
		}
		oldMouseX = mousePos.x;
		oldMouseY = mousePos.y;
	}
	else {
		mouseIsPressed = false;
	}


	// Applying zoom by changing distToObj. J to zoom in, K to zoom out
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) distToObj *= zoomValue;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) distToObj /= zoomValue;


	// Limiting vertical angle using radians. Using (-)0.5PI means it's limited to straight up or down
	// (-)0.25PI gives a max of 45 degrees difference from no rotation
	xAxisRot = glm::clamp(xAxisRot, -rotLimit, rotLimit);

	// Prevent absurdly high numbers when rotating for a while because 2PI is a full rotation
	yAxisRot = glm::mod(yAxisRot, 2*glm::pi<float>());

	
}
