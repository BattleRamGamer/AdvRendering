#ifndef SPACE_HPP
#define SPACE_HPP

#include "mge/core/GameObject.hpp"
#include "CollisionManager.hpp"

class Space : public GameObject {


public:
	Space(int pDepthLeft, glm::vec2 pPosition, float pTotalWidth, float pTotalHeight);
	~Space();

	int getCollisionNumber();

private:

	std::vector<Space*> _spaces;
	int depthLeft;

	CollisionManager* colManager;

};

#endif // SPACE_HPP
