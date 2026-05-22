#include "GridManager.hpp"

GridManager::GridManager() : GameObject("GridManager", glm::vec3(0, 0, 0)), grids_(0) {
	

	for (int i = 0; i < (IsTripleGrid() ? 3 : 1); i++) {
		// Add offsets for the triple grid
		grids_.push_back(new Grid(i));
	}
	
}

GridManager::~GridManager() {

}


void GridManager::update(float pStep)
{

	for (int i = 0; i < (IsTripleGrid() ? 3 : 1); i++) {
		grids_[i]->ResetColors();
	}


	handleCollisions();

}


void GridManager::Add(Collider* pCollider) {

	if (!IsTripleGrid()) {
		grids_[0]->Add(pCollider);
		return;
	}

	// Calculate position and assign grid


	glm::vec2 pos = ((MoveBehaviour*)pCollider->getBehaviour())->GetPosition();

	// 0 = grid with no offset		RED
	// 1 = grid with 1/3 offset		GREEN
	// 2 = grid with 2/3 offset		BLUE


	int gridX = GetChosenGrid(pos.x);
	int gridY = GetChosenGrid(pos.y);

	AddToGrid(pCollider, gridX, gridY);


}


void GridManager::CheckMovement(Collider* pCollider, glm::vec2 oldPos, glm::vec2 newPos) {

	if (!IsTripleGrid()) {
		grids_[0]->CheckMovement(pCollider, oldPos, newPos);
		return;
	}

	int oldGridX = GetChosenGrid(oldPos.x);
	int oldGridY = GetChosenGrid(oldPos.y);

	int newGridX = GetChosenGrid(newPos.x);
	int newGridY = GetChosenGrid(newPos.y);

	// If it's the same, return
	if (oldGridX == newGridX && oldGridY == newGridY) return;

	// Detatch from old Grid
	DetatchFromGrid(pCollider, oldGridX, oldGridY, oldPos);
	
	// Add to new grid
	AddToGrid(pCollider, newGridX, newGridY);

}


void GridManager::handleCollisions() {

	collisionTestCount = 0;
	numberOfCollisions = 0;
	//ResetColors();

	for (int i = 0; i < (IsTripleGrid() ? 3 : 1); i++) {
		handleGrid(i);
		collisionTestCount += grids_[i]->GetTestCount();
		numberOfCollisions += grids_[i]->GetCollisionCount();
	}
}


void GridManager::handleGrid(int pGridNr) {

	// For each cell in the grid

	for (int i = 0; i < config::GRID_CELL_COUNT; i++) {
		for (int j = 0; j < config::GRID_CELL_COUNT; j++) {

			// Tells a cell to check its own and surrounding cells
			handleCell(i, j, pGridNr);
		}
	}

}

void GridManager::handleCell(int pX, int pY, int pGridNr) {

	if (!IsTripleGrid()) {
		grids_[0]->handleCell(pX, pY);
		return;
	}

	Collider* collider = grids_[pGridNr]->cells_[pX][pY];

	if (collider == NULL) return;

	int otherGrid = (pGridNr + 1) % 3;
	int otherGridCellOffset = -1;

	bool canCheckHorizontal = pX > 0;
	bool canCheckVertical = pY > 0;

	if (pGridNr == 2) {
		// Blue grid: Check Grid[0], check the cells + 1
		otherGridCellOffset = 1;
		canCheckHorizontal = pX < config::GRID_CELL_COUNT - 1;
		canCheckVertical = pY < config::GRID_CELL_COUNT - 1;
	}


	while (collider != NULL)
	{
		// Collider checks own cell
		grids_[pGridNr]->handleCollider(collider);


		// Other grid, same cell coordinate
		grids_[pGridNr]->handleCollider(collider, grids_[otherGrid]->cells_[pX][pY]);
		
		// Other grid, cell horizontal offset
		if (canCheckHorizontal) grids_[pGridNr]->handleCollider(collider, grids_[otherGrid]->cells_[pX + otherGridCellOffset][pY]);
		
		// Other grid, cell vertical offset
		if (canCheckVertical) grids_[pGridNr]->handleCollider(collider, grids_[otherGrid]->cells_[pX][pY + otherGridCellOffset]);
		
		// Other grid, cell diagonal offset
		if (canCheckHorizontal && canCheckVertical) {
			grids_[pGridNr]->handleCollider(collider, grids_[otherGrid]->cells_[pX + otherGridCellOffset][pY + otherGridCellOffset]);
		}


		collider = collider->next_;
	}
}

void GridManager::AddToGrid(Collider* pCollider, int pGridX, int pGridY) {
	if ((pGridX + 2) % 3 == pGridY) {
		grids_[pGridY]->Add(pCollider, pGridX);
	}
	else {
		if (pGridX == 2 && pGridY == 0) {
			// ERROR IS OCCURING: This means that the Y cell needs to be decreased by 1
			// The 20 stands for X grid = 2, Y grid = 0
			grids_[pGridX]->Add(pCollider, 20);
		}
		else {
			grids_[pGridX]->Add(pCollider);
		}
	}
}

void GridManager::DetatchFromGrid(Collider* pCollider, int pGridX, int pGridY, glm::vec2 pPos) {

	if ((pGridX + 2) % 3 == pGridY) {
		grids_[pGridY]->Detatch(pCollider, pPos.x, pPos.y, pGridX);
	}
	else {
		if (pGridX == 2 && pGridY == 0) {
			// ERROR IS OCCURING: This means that the Y cell needs to be decreased by 1
			// The 20 stands for X grid = 2, Y grid = 0
			grids_[pGridX]->Detatch(pCollider, pPos.x, pPos.y, 20);
		}
		else {
			grids_[pGridX]->Detatch(pCollider, pPos.x, pPos.y);
		}
	}

}

int GridManager::GetTestCount() {
	return collisionTestCount;
}
int GridManager::GetCollisionCount() {
	return numberOfCollisions;
}


int GridManager::GetChosenGrid(float pPosition) {
	// Gets the local position in a cell, multiplies by 3 (because of 3 grids)
	float remainder30 = (float)((int)(pPosition * 3) % (int)(config::GRID_CELL_SIZE * 3));

	// Divide by the cell size and round down
	return (int)(remainder30 / config::GRID_CELL_SIZE);

}

bool GridManager::IsTripleGrid() {
	return (config::GRID_TRIPLE && config::USE_SPATIALPARTITIONING);
}