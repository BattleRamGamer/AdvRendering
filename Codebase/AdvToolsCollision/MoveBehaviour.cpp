#include "MoveBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "mge/config.hpp"

MoveBehaviour::MoveBehaviour(GridManager* pGridManager, float pMoveSpeed, float pMoveAngle) : AbstractBehaviour(), _gridManager(pGridManager), _moveSpeed(pMoveSpeed), _moveAngle(pMoveAngle), _moveDirection(glm::vec2(1, 0)), _estimatedPosition(glm::vec2(0, 0))
{
	_moveDirection = glm::vec2(cos(glm::radians(pMoveAngle)), sin(glm::radians(pMoveAngle)));
}

MoveBehaviour::~MoveBehaviour()
{
}

void MoveBehaviour::update(float pStep)
{
	glm::vec2 oldPos = _estimatedPosition;


	// If position + movement exceeds boundary,
	// Check what movement exceeds the boundary
	// Reverse that movement
	// THEN move
	float newX = _estimatedPosition.x + _moveDirection.x * _moveSpeed;
	float newY = _estimatedPosition.y + _moveDirection.y * _moveSpeed;

	if (newX < 0.0f && _moveDirection.x < 0 ||
		newX > config::BOUNDARY_SIZE && _moveDirection.x > 0) {
		_moveDirection.x *= -1;
	}

	if (newY < 0.0f && _moveDirection.y < 0 ||
		newY > config::BOUNDARY_SIZE && _moveDirection.y > 0) {
		_moveDirection.y *= -1;
	}



	_owner->translate(glm::vec3(_moveDirection.x, 0, _moveDirection.y) * _moveSpeed);

	_estimatedPosition += _moveDirection * _moveSpeed;

	if (config::USE_SPATIALPARTITIONING) {
		_gridManager->CheckMovement((Collider*)_owner, oldPos, _estimatedPosition);
	}




}

glm::vec2 MoveBehaviour::GetPosition() const{
	return _estimatedPosition;
}

void MoveBehaviour::setOwner(GameObject* pOwner) {
	AbstractBehaviour::setOwner(pOwner);
	glm::vec3 ownerPos = _owner->getWorldPosition();
	_estimatedPosition = glm::vec2(ownerPos.x, ownerPos.z);
}