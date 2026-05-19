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

	// First move the collider, then call this function
	void CheckMovement(Collider* pCollider, glm::vec2 oldPos, glm::vec2 newPos);

	void handleCollisions();

	// Insert the cell coordinates here
	void handleCell(int pX, int pY);

	void handleCollider(Collider* pCollider);
	// Assumes that pCollider is valid
	void handleCollider(Collider* pCollider, Collider* pOther);

	void ResetColors();

	int GetTestCount();
	int GetCollisionCount();

private:
	int GetChosenGrid(float pPosition);

	Collider* cells_[config::GRID_CELL_COUNT][config::GRID_CELL_COUNT];

	int collisionTestCount = 0;
	int numberOfCollisions = 0;

	int gridNr;

	ColorMaterial* redMaterialNoCol = new ColorMaterial(glm::vec3(1, 0, 0));
	ColorMaterial* greenMaterialYesCol = new ColorMaterial(glm::vec3(0, 1, 0));

};



#endif // GRID_HPP
