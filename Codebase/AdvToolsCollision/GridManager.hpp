#ifndef GRIDMANAGER_HPP
#define GRIDMANAGER_HPP

#include "mge/config.hpp"
#include "Collider.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "Grid.hpp"

class Collider;
class Grid;

class GridManager : public GameObject{

public:
	GridManager();
	~GridManager();

	void Add(Collider* pCollider);

	// First move the collider, then call this function
	void CheckMovement(Collider* pCollider, glm::vec2 oldPos, glm::vec2 newPos);

	void handleCollisions();

	void handleGrid(int pGridNr);

	// Insert the cell coordinates here
	void handleCell(int pX, int pY, int pGridNr);

	virtual void update(float pStep);

	int GetTestCount() const;
	int GetCollisionCount() const;

private:


	std::vector<Grid*> grids_;

	void AddToGrid(Collider* pCollider, int pGridX, int pGridY);
	void DetatchFromGrid(Collider* pCollider, int pGridX, int pGridY, glm::vec2 pPos);
	int GetChosenGrid(float pPosition) const;
	bool IsTripleGrid() const;



	int collisionTestCount = 0;
	int numberOfCollisions = 0;

};



#endif // GRIDMANAGER_HPP
