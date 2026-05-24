#ifndef GRID_HPP
#define GRID_HPP


#include "MoveBehaviour.hpp"
#include "Collider.hpp"
#include "mge/materials/ColorMaterial.hpp"

class Collider;
class Grid {

	friend class GridManager;

public:
	Grid(int pGridNr);
	~Grid();

	void Add(Collider* pCollider, int pGridOffsetNr = -1);

	void Detatch(Collider* pCollider, int pOldX, int pOldY, int pGridOffsetNr = -1);

	// This function is only called for the single grid system
	void CheckMovement(Collider* pCollider, glm::vec2 oldPos, glm::vec2 newPos);

	void handleCollisions();

	// Insert the cell coordinates here. Only called in a single grid system
	void handleCell(int pX, int pY);

	void handleCollider(Collider* pCollider);
	// Assumes that pCollider is valid
	void handleCollider(Collider* pCollider, Collider* pOther);

	void ResetColors();

	int GetTestCount();
	int GetCollisionCount();

private:
	int GetCellPos(float pPos) const;

	Collider* cells_[config::GRID_CELL_COUNT][config::GRID_CELL_COUNT];

	int collisionTestCount = 0;
	int numberOfCollisions = 0;

	int gridNr;

	// Memory gap filling
	int fillGap0 = 0;


};



#endif // GRID_HPP
