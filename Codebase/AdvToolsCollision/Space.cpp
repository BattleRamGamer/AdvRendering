#include "Space.hpp"
#include "mge/config.hpp"

Space::Space(int pDepthLeft, glm::vec2 pPosition, float pTotalWidth, float pTotalHeight) 
	: GameObject("Space"), depthLeft(pDepthLeft) {


	if (depthLeft > 0)
	{
		float newWidth = pTotalWidth / config::SPACE_PART_COLUMNS;
		float newHeight = pTotalHeight / config::SPACE_PART_ROWS;
		for (int i = 0; i < config::SPACE_PART_ROWS; i++)
		{
			for (int j = 0; j < config::SPACE_PART_COLUMNS; j++)
			{
				glm::vec2 newPos = glm::vec2(pPosition.x + j * newWidth, pPosition.y + i * newHeight);
				_spaces.push_back(new Space(depthLeft - 1, newPos, newWidth, newHeight));
			}
		}
	}
	else
	{
		//collisionManager things
		colManager = new CollisionManager();

	}


}

Space::~Space() {
	delete(colManager);

}

int Space::getCollisionNumber() {

	int colTotal = 0;
	if (depthLeft > 0)
	{
		for(int i = 0; i < _spaces.size(); i++)
		{
			colTotal += _spaces[i]->getCollisionNumber();
		}
	}
	else
	{
		colTotal = colManager->checkCollisions();
	}
	return colTotal;




}