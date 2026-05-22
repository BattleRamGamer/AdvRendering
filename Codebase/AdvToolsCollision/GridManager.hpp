#ifndef GRIDMANAGER_HPP
#define GRIDMANAGER_HPP

#include "mge/config.hpp"
#include "Collider.hpp"
#include "mge/materials/ColorMaterial.hpp"
#include "Grid.hpp"
//#include "MoveBehaviour.hpp"

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

	// Assumes that pCollider is valid
	//void handleCollider(Collider* pCollider, Collider* pOther);

	//void ResetColors();

	//virtual void update(float pStep);
	virtual void update(float pStep);

	int GetTestCount();
	int GetCollisionCount();

private:

	//Grid* grids_[config::GRID_TRIPLE ? 3 : 1];

	std::vector<Grid*> grids_;

	void AddToGrid(Collider* pCollider, int pGridX, int pGridY);
	void DetatchFromGrid(Collider* pCollider, int pGridX, int pGridY, glm::vec2 pPos);
	int GetChosenGrid(float pPosition);
	bool IsTripleGrid();


	//Collider* cells_[config::GRID_CELL_COUNT][config::GRID_CELL_COUNT];

	int collisionTestCount = 0;
	int numberOfCollisions = 0;

	AbstractMaterial* redMaterialNoCol = new ColorMaterial(glm::vec3(1, 0, 0));
	AbstractMaterial* greenMaterialYesCol = new ColorMaterial(glm::vec3(0, 1, 0));

};



#endif // GRIDMANAGER_HPP
