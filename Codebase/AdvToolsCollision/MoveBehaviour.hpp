#ifndef MOVEBEHAVIOUR_HPP
#define MOVEBEHAVIOUR_HPP

#include <vector>
#include "glm.hpp"
#include "mge/behaviours/AbstractBehaviour.hpp"


class MoveBehaviour : public AbstractBehaviour
{
public:
	//move speed is in units per second, turnspeed in degrees per second
	MoveBehaviour(float pMoveSpeed = 5, float pMoveAngle = 45);
	virtual ~MoveBehaviour();
	virtual void update(float pStep);

	virtual void setOwner(GameObject* pGameObject);

protected:
	glm::vec2 _moveDirection;
	glm::vec2 _estimatedPosition;

private:
	float _moveSpeed;
	float _moveAngle;
};

#endif // MOVEBEHAVIOUR_HPP
