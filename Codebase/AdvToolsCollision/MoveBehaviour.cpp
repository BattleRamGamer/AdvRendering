#include "MoveBehaviour.hpp"
#include "mge/core/GameObject.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "mge/config.hpp"

MoveBehaviour::MoveBehaviour(float pMoveSpeed, float pMoveAngle) : AbstractBehaviour(), _moveSpeed(pMoveSpeed), _moveAngle(pMoveAngle), _moveDirection(glm::vec2(1, 0)), _estimatedPosition(glm::vec2(0,0))
{
	_moveDirection = glm::vec2(cos(glm::radians(pMoveAngle)), sin(glm::radians(pMoveAngle)));
}

MoveBehaviour::~MoveBehaviour()
{
}

void MoveBehaviour::update(float pStep)
{
	
	_owner->translate(glm::vec3(_moveDirection.x, 0, _moveDirection.y) * _moveSpeed);

	_estimatedPosition += _moveDirection * _moveSpeed;

	float x = _estimatedPosition.x;
	float z = _estimatedPosition.y;

	//float x = _owner->getWorldPosition().x;
	//float z = _owner->getWorldPosition().z;

	if (x < -config::BOUNDARY_POSITION && _moveDirection.x < 0 || 
		x >  config::BOUNDARY_POSITION && _moveDirection.x > 0) 
		_moveDirection.x *= -1;

	if (z < -config::BOUNDARY_POSITION && _moveDirection.y < 0 || 
		z >  config::BOUNDARY_POSITION && _moveDirection.y > 0)
		_moveDirection.y *= -1;

}

void MoveBehaviour::setOwner(GameObject* pOwner) {
	AbstractBehaviour::setOwner(pOwner);
	glm::vec3 ownerPos = _owner->getWorldPosition();
	_estimatedPosition = glm::vec2(ownerPos.x, ownerPos.z);
}