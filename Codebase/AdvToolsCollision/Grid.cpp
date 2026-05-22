#include "Grid.hpp"

Grid::Grid(int pGridNr) : gridNr(pGridNr) {
	for (int i = 0; i < config::GRID_CELL_COUNT; i++) {
		for (int j = 0; j < config::GRID_CELL_COUNT; j++) {
			cells_[i][j] = NULL;
		}
	}
}

Grid::~Grid() {

}

void Grid::Add(Collider* pCollider, int pGridOffsetNr) {

	glm::vec2 pos = ((MoveBehaviour*)pCollider->getBehaviour())->GetPosition();

	int cellX = GetCellPos(pos.x);
	int cellY = GetCellPos(pos.y);


	if (config::GRID_TRIPLE) {
		cellX++;
		cellY++;
		if (pGridOffsetNr == 0) cellX--;
		// Bad code: If GridX == 2 and GridY == 0, cellY needs to be decreased
		if (pGridOffsetNr == 20) cellY--;
	}

	pCollider->prev_ = NULL;
	pCollider->next_ = cells_[cellX][cellY];


	cells_[cellX][cellY] = pCollider;

	if (pCollider->next_ != NULL) {
		pCollider->next_->prev_ = pCollider;
	}




}

void Grid::Detatch(Collider* pCollider, int pOldX, int pOldY, int pGridOffsetNr) {

	if (pCollider->prev_ != NULL) {
		pCollider->prev_->next_ = pCollider->next_;
	}

	if (pCollider->next_ != NULL) {
		pCollider->next_->prev_ = pCollider->prev_;
	}

	int cellX = GetCellPos(pOldX);
	int cellY = GetCellPos(pOldY);
	if (config::GRID_TRIPLE) {
		cellX++;
		cellY++;
		if (pGridOffsetNr == 0) cellX--;
		// Bad code: If GridX == 2 and GridY == 0, cellY needs to be decreased
		if (pGridOffsetNr == 20) cellY--;
	}
	if (cells_[cellX][cellY] == pCollider) {
		cells_[cellX][cellY] = pCollider->next_;
	}

}


void Grid::CheckMovement(Collider* pCollider, glm::vec2 oldPos, glm::vec2 newPos) {
	// THIS FUNCTION IS ONLY CALLED FOR A SINGLE GRID SYSTEM: NO NEED TO BOTHER WITH TRIPLE GRID HERE
	int oldCellX = GetCellPos(oldPos.x);
	int oldCellY = GetCellPos(oldPos.y);

	int newCellX = GetCellPos(newPos.x);
	int newCellY = GetCellPos(newPos.y);



	if (oldCellX == newCellX && oldCellY == newCellY) return;

	Detatch(pCollider, oldPos.x, oldPos.y);

	Add(pCollider);
}


void Grid::handleCollisions() {

	collisionTestCount = 0;
	numberOfCollisions = 0;
	ResetColors();

	for (int i = 0; i < config::GRID_CELL_COUNT; i++) {
		for (int j = 0; j < config::GRID_CELL_COUNT; j++) {

			// Tells a cell to check its own and surrounding cells
			handleCell(i, j);
		}
	}
}

void Grid::handleCell(int pX, int pY) {
	
	Collider* collider = cells_[pX][pY];

	while (collider != NULL)
	{
		// Collider checks own cell
		handleCollider(collider, collider->next_);
		

		// Checking the grid spaces around. THIS IS THE SITE'S IMPLEMENTATION
		if (pX > 0 && pY > 0)	handleCollider(collider, cells_[pX - 1][pY - 1]);	// Diagonal Top left
		if (pX > 0)				handleCollider(collider, cells_[pX - 1][pY    ]);	// Left
		if (pY > 0)				handleCollider(collider, cells_[pX    ][pY - 1]);	// Above
		if (pX > 0 && pY < config::GRID_CELL_COUNT - 1) {
								handleCollider(collider, cells_[pX - 1][pY + 1]);	// Diagonal Bottom left
		}


		collider = collider->next_;
	}
}

void Grid::handleCollider(Collider* pCollider) {
	handleCollider(pCollider, pCollider->next_);
}

void Grid::handleCollider(Collider* pCollider, Collider* pOther) {

	while (pOther != NULL) {

		// Increase collision checks by 1
		collisionTestCount++;
		
		if (pCollider->checkCollision(pOther)) {
			// Increase collisions measured by 1
			numberOfCollisions++;

			pCollider->isColliding = true;
			pOther->isColliding = true;

			pCollider->ReloadMaterial();
			pOther->ReloadMaterial();

		}

		pOther = pOther->next_;
	}


}


void Grid::ResetColors() {

	// Go through all colliders and set their material 
	for (int i = 0; i < config::GRID_CELL_COUNT; i++) {
		for (int j = 0; j < config::GRID_CELL_COUNT; j++) {

			Collider* collider = cells_[i][j];

			while (collider != NULL) {

				collider->cellX = i;
				collider->cellY = j;
				collider->gridNr = gridNr;
				collider->isColliding = false;

				collider->ReloadMaterial();

				collider = collider->next_;

			}

		}
	}


}



int Grid::GetTestCount() {
	int testCount = collisionTestCount;
	collisionTestCount = 0;
	return testCount;
}
int Grid::GetCollisionCount() {
	int colCount = numberOfCollisions;
	numberOfCollisions = 0;
	return colCount;
}

int Grid::GetCellPos(float pPos) {
	return (int)(pPos / config::GRID_CELL_SIZE);
}