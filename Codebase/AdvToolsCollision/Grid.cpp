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
	if (pCollider == pCollider->next_) {
		printf("Something went really wrong");
	}
	// Cell x =
	// Get Collider x position
	// Divide by width of cell
	int cellX = (int)(pos.x / config::GRID_CELL_SIZE);
	int cellY = (int)(pos.y / config::GRID_CELL_SIZE);


	if (config::GRID_TRIPLE) {
		cellX++;
		cellY++;
		if (pGridOffsetNr == 0) cellX--;
		// Bad code: If GridX == 2 and GridY == 0, cellY needs to be decreased
		if (pGridOffsetNr == 20) cellY--;
		//if (pGridOffsetNr > 0) cellY++;
	}

	pCollider->prev_ = NULL;
	pCollider->next_ = cells_[cellX][cellY];

	if (pCollider == pCollider->next_) {
		printf("Something went really wrong");
	}
	cells_[cellX][cellY] = pCollider;
	if (pCollider == pCollider->next_) {
		printf("Something went really wrong");
	}
	if (pCollider->next_ != NULL) {
		pCollider->next_->prev_ = pCollider;
	}

	if (pCollider == pCollider->next_) {
		printf("Something went really wrong");
	}


}

void Grid::Detatch(Collider* pCollider, int pOldX, int pOldY, int pGridOffsetNr) {

	if (pCollider->prev_ != NULL) {
		pCollider->prev_->next_ = pCollider->next_;
	}

	if (pCollider->next_ != NULL) {
		pCollider->next_->prev_ = pCollider->prev_;
	}

	int cellX = (int)(pOldX / config::GRID_CELL_SIZE);
	int cellY = (int)(pOldY / config::GRID_CELL_SIZE);
	if (config::GRID_TRIPLE) {
		cellX++;
		cellY++;
		if (pGridOffsetNr == 0) cellX--;
		// Bad code: If GridX == 2 and GridY == 0, cellY needs to be decreased
		if (pGridOffsetNr == 20) cellY--;
		//if (pGridOffsetNr > 0) cellY++;
	}
	if (cells_[cellX][cellY] == pCollider) {
		cells_[cellX][cellY] = pCollider->next_;
	}

}


void Grid::CheckMovement(Collider* pCollider, glm::vec2 oldPos, glm::vec2 newPos) {

	int oldCellX = (int)(oldPos.x / config::GRID_CELL_SIZE);
	int oldCellY = (int)(oldPos.y / config::GRID_CELL_SIZE);

	int newCellX = (int)(newPos.x / config::GRID_CELL_SIZE);
	int newCellY = (int)(newPos.y / config::GRID_CELL_SIZE);

	int oldChosenGridX = GetChosenGrid(oldPos.x);
	int oldChosenGridY = GetChosenGrid(oldPos.y);

	int newChosenGridX = GetChosenGrid(newPos.x);
	int newChosenGridY = GetChosenGrid(newPos.y);

	int oldGrid = -1;
	int newGrid = -1;

	if ((oldChosenGridX + 2) % 3 == oldChosenGridY) oldGrid = oldChosenGridY;
	else oldGrid = oldChosenGridX;

	// Just directly add to new grid
	if ((newChosenGridX + 2) % 3 == newChosenGridY) newGrid = newChosenGridY;
	else newGrid = newChosenGridX;


	if (oldCellX == newCellX && oldCellY == newCellY && oldGrid == newGrid) return;


	if (pCollider->prev_ != NULL) {
		pCollider->prev_->next_ = pCollider->next_;
	}

	if (pCollider->next_ != NULL) {
		pCollider->next_->prev_ = pCollider->prev_;
	}
	if (config::GRID_TRIPLE) {
		oldCellX++;
		oldCellY++;

		if (oldChosenGridX == 2 && oldChosenGridY == 0) oldCellY--;
	}

	if (cells_[oldCellX][oldCellY] == pCollider) {
		cells_[oldCellX][oldCellY] = pCollider->next_;
	}

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

	int oldCellX = (int)(pCollider->getWorldPosition().x / config::GRID_CELL_SIZE);
	int oldCellY = (int)(pCollider->getWorldPosition().z / config::GRID_CELL_SIZE);
	while (pOther != NULL) {

		// Increase collision checks by 1
		collisionTestCount++;
		
		if (pCollider->checkCollision(pOther)) {
			// Increase collisions measured by 1
			numberOfCollisions++;

			// Setting the material to the colliding colors


			pCollider->isColliding = true;
			pOther->isColliding = true;

			pCollider->ReloadMaterial();
			pOther->ReloadMaterial();


			//int newCellX = (int)(pOther->getWorldPosition().x / config::GRID_CELL_SIZE);
			//int newCellY = (int)(pOther->getWorldPosition().z / config::GRID_CELL_SIZE);
			
			
			//pCollider->SetColMaterial(1, oldCellX / 5.0f, oldCellY / 5.0f, 1);
			//pOther->SetColMaterial(1, newCellX / 5.0f, newCellY / 5.0f, 1);
			//((ColorMaterial*)pCollider->getMaterial())->setDiffuseColor(glm::vec3(1, oldCellX / 5.0f, oldCellY / 5.0f));

			//greenMaterialYesCol->setDiffuseColor(glm::vec3(1, oldCellX / 5.0f, oldCellY / 5.0f));
			//pCollider->setMaterial(greenMaterialYesCol);
			//pOther->setMaterial(greenMaterialYesCol);
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

				//collider->SetColMaterial(1, 1, 1, 1);
				//collider->setMaterial(redMaterialNoCol);

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

int Grid::GetChosenGrid(float pPosition) {

	float asdfd = (float)((int)(pPosition * 3) % (int)(config::GRID_CELL_SIZE * 3));

	float jkl = asdfd / config::GRID_CELL_SIZE;

	int qwer = (int)jkl;

	return qwer;

	return (int)(asdfd / config::GRID_CELL_SIZE);

	float remainder = (float)((int)(pPosition * 3) % (int)(config::GRID_CELL_SIZE * 3)) / 3.0f;

	if (remainder > 6.666f) return 2;

	return (int)((remainder / config::GRID_CELL_SIZE) * 3);
}