#ifndef FOLLOWBEHAVIOUR_HPP
#define FOLLOWBEHAVIOUR_HPP

#include "../../glm.hpp"
#include "AbstractBehaviour.hpp"

class FollowBehaviour : public AbstractBehaviour
{
	public:
		FollowBehaviour(GameObject* objToFollow, float offsetDistance);
		virtual ~FollowBehaviour();
		virtual void update( float pStep );

    private:
		GameObject* objToFollow;

		float distToObj;
		float zoomValue;
		const float rotLimit;
		float xAxisRot;
		float yAxisRot;

		float oldMouseX;
		float oldMouseY;
		bool mouseIsPressed;
		float xSensitivity;
		float ySensitivity;

};

#endif // FOLLOWBEHAVIOUR_HPP
