#include "GridManager.hpp"

GridManager::GridManager() : GameObject("GridManager", glm::vec3(0, 0, 0)), grids_(0) {
	
	/**/
	for (int i = 0; i < (config::GRID_TRIPLE ? 3 : 1); i++) {
		// Add offsets for the triple grid
		grids_.push_back(new Grid(i));
	}
	
	printf("First grid has number %i\n", grids_[0]->gridNr);
	printf("Second grid has number %i\n", grids_[1]->gridNr);
	printf("Third grid has number %i\n", grids_[2]->gridNr);

	printf("Chosen grid: %i", GetChosenGrid(25.274109f));

	/**
	for (int i = 0; i < config::GRID_CELL_COUNT; i++) {
		for (int j = 0; j < config::GRID_CELL_COUNT; j++) {
			cells_[i][j] = NULL;
		}
	}
	/**/
}

GridManager::~GridManager() {

}

/**/
void GridManager::update(float pStep)
{

	for (int i = 0; i < (config::GRID_TRIPLE ? 3 : 1); i++) {
		grids_[i]->ResetColors();
	}


	handleCollisions();
	/**
	for (int n = 0; n < (config::GRID_TRIPLE ? 3 : 1); n++) {
		// WATCH OUT: THIS ONLY WORKS FOR A SINGLE GRID
		for (int i = 0; i < config::GRID_CELL_COUNT; i++) {
			for (int j = 0; j < config::GRID_CELL_COUNT; j++) {

				// Tells a cell to check its own and surrounding cells
				handleCell(i, j, n);
			}
		}
		//grids_[n]->handleCollisions();
	}
	/**/

}


void GridManager::Add(Collider* pCollider) {

	if (!config::USE_SPATIALPARTITIONING || !config::GRID_TRIPLE) {
		grids_[0]->Add(pCollider);
		return;
	}

	// Calculate position and assign grid


	glm::vec2 pos = ((MoveBehaviour*)pCollider->getBehaviour())->GetPosition();

	// 0 = grid with negative offset	RED
	// 1 = grid with no offset			GREEN
	// 2 = grid with positive offset	BLUE


	int gridX = GetChosenGrid(pos.x);
	int gridY = GetChosenGrid(pos.y);


	/**
	//float xPos = pos.x;

	//
	//float xRemainder = (float)((int)(pos.x * 3) % (int)(config::GRID_CELL_SIZE * 3)) / 3.0f;

	//int gridX = (int)(xRemainder / config::GRID_CELL_SIZE * 3);


	//float yRemainder = (float)((int)(pos.y * 3) % (int)(config::GRID_CELL_SIZE * 3)) / 3.0f;

	//int gridY = (int)(yRemainder / config::GRID_CELL_SIZE * 3);

	//int cellX = (int)((( (float)pos.x % (int)config::GRID_CELL_SIZE) / config::GRID_CELL_SIZE) * 3);


	//int cellX = (int)(pos.x / config::GRID_CELL_SIZE * 3);

	//int chosenGridX = cellX % 3;


	//int cellY = (int)(pos.y / config::GRID_CELL_SIZE * 3);

	//int chosenGridY = cellY % 3;
	/**/

	// HOW DO I DO THE OFFSET
	if ((gridX + 2) % 3 == gridY) {
		grids_[gridY]->Add(pCollider, gridX);
	}
	else {
		if (gridX == 2 && gridY == 0) {
			// ERROR IS OCCURING: This means that the Y cell needs to be decreased by 1
			// The 20 stands for X grid = 2, Y grid = 0
			grids_[gridX]->Add(pCollider, 20);
		}
		else {
			grids_[gridX]->Add(pCollider);
		}
	}



	/**
	int chosenGrid = -1;

	switch (cellX % 3) {
	case (0): chosenGrid = 0;
		break;
	case (1): chosenGrid = 2;
		break;
	case (2): chosenGrid = 1;
		break;
	}
	/**/

}


void GridManager::CheckMovement(Collider* pCollider, glm::vec2 oldPos, glm::vec2 newPos) {

	if (!config::GRID_TRIPLE) {
		grids_[0]->CheckMovement(pCollider, oldPos, newPos);
		return;
	}


	int oldGridX = GetChosenGrid(oldPos.x);
	int oldGridY = GetChosenGrid(oldPos.y);

	int newGridX = GetChosenGrid(newPos.x);
	int newGridY = GetChosenGrid(newPos.y);

	// Get old cell
	//int oldGridX = (int)(oldPos.x / config::GRID_CELL_SIZE * 3) % 3;
	//int oldGridY = (int)(oldPos.y / config::GRID_CELL_SIZE * 3) % 3;

	// Get new cell
	//int newGridX = (int)(newPos.x / config::GRID_CELL_SIZE * 3) % 3;
	//int newGridY = (int)(newPos.y / config::GRID_CELL_SIZE * 3) % 3;

	// If it's the same, return
	if (oldGridX == newGridX && oldGridY == newGridY) return;


	// Call old Grid to detatch
	
	if ((oldGridX + 2) % 3 == oldGridY) {
		grids_[oldGridY]->Detatch(pCollider, oldPos.x, oldPos.y, oldGridX);
	}
	else {
		if (oldGridX == 2 && oldGridY == 0) {
			// ERROR IS OCCURING: This means that the Y cell needs to be decreased by 1
			// The 20 stands for X grid = 2, Y grid = 0
			grids_[oldGridX]->Detatch(pCollider, oldPos.x, oldPos.y, 20);
		}
		else {
			grids_[oldGridX]->Detatch(pCollider, oldPos.x, oldPos.y);
		}
	}

	// Just directly add to new grid
	if ((newGridX + 2) % 3 == newGridY) {
		grids_[newGridY]->Add(pCollider, newGridX);
	}
	else {
		if (newGridX == 2 && newGridY == 0) {
			// ERROR IS OCCURING: This means that the Y cell needs to be decreased by 1
			// The 20 stands for X grid = 2, Y grid = 0
			grids_[newGridX]->Add(pCollider, 20);
		}
		else {
			grids_[newGridX]->Add(pCollider);
		}
	}

}


void GridManager::handleCollisions() {

	collisionTestCount = 0;
	numberOfCollisions = 0;
	//ResetColors();

	for (int i = 0; i < (config::GRID_TRIPLE ? 3 : 1); i++) {
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

	if (!config::GRID_TRIPLE) {
		grids_[0]->handleCell(pX, pY);
		return;
	}

	Collider* collider = grids_[pGridNr]->cells_[pX][pY];

	while (collider != NULL)
	{
		// Collider checks own cell
		grids_[pGridNr]->handleCollider(collider);


		int otherGrid = (pGridNr + 1) % 3;
		int otherGridCellOffset = -1;

		bool canCheckHorizontal = pX > 0;
		bool canCheckVertical = pY > 0;

		if (pGridNr == 2) {
			// Blue grid: Check Grid[0], check the cells + 1
			otherGridCellOffset = 1;
			canCheckHorizontal = pX <= config::GRID_CELL_COUNT - 1;
			canCheckVertical = pY <= config::GRID_CELL_COUNT - 1;
		}

		// Other grid, same cell
		grids_[pGridNr]->handleCollider(collider, grids_[otherGrid]->cells_[pX][pY]);
		
		// Other grid, cell horizontal offset
		if (canCheckHorizontal) grids_[pGridNr]->handleCollider(collider, grids_[otherGrid]->cells_[pX + otherGridCellOffset][pY]);
		
		// Other grid, cell vertical offset
		if (canCheckVertical) grids_[pGridNr]->handleCollider(collider, grids_[otherGrid]->cells_[pX][pY + otherGridCellOffset]);
		
		// Other grid, cell diagonal offset
		if (canCheckHorizontal && canCheckVertical) {
			grids_[pGridNr]->handleCollider(collider, grids_[otherGrid]->cells_[pX + otherGridCellOffset][pY + otherGridCellOffset]);
		}

		/**
		// Checking the grid spaces around. THIS IS THE SITE'S IMPLEMENTATION
		if (pX > 0 && pY > 0)	handleCollider(collider, grids_[pGridNr]->cells_[pX - 1][pY - 1]);	// Diagonal Top left
		if (pX > 0)				handleCollider(collider, grids_[pGridNr]->cells_[pX - 1][pY]);		// Left
		if (pY > 0)				handleCollider(collider, grids_[pGridNr]->cells_[pX][pY - 1]);		// Above
		if (pX > 0 && pY < config::GRID_CELL_COUNT - 1) {
								handleCollider(collider, grids_[pGridNr]->cells_[pX - 1][pY + 1]);	// Diagonal Bottom left
		}
		/**/

		collider = collider->next_;
	}
}


int GridManager::GetTestCount() {
	return collisionTestCount;
}
int GridManager::GetCollisionCount() {
	return numberOfCollisions;
}


int GridManager::GetChosenGrid(float pPosition) {

	float asdfd = (float)((int)(pPosition * 3) % (int)(config::GRID_CELL_SIZE * 3));

	float jkl = asdfd / config::GRID_CELL_SIZE;

	int qwer = (int)jkl;

	return qwer;

	return (int)(asdfd / config::GRID_CELL_SIZE);

	float remainder = (float)((int)(pPosition * 3) % (int)(config::GRID_CELL_SIZE * 3)) / 3.0f;

	if (remainder > 6.666f) return 2;

	return (int)( (remainder / config::GRID_CELL_SIZE) * 3);
}

/**/
/**

void GridManager::Add(Collider* pCollider) {

	glm::vec2 pos = ((MoveBehaviour*)pCollider->getBehaviour())->GetPosition();




	int cellX = (int)(pos.x / config::GRID_CELL_SIZE * 3);

	int chosenGrid = -1;

	switch (cellX % 3) {
	case (0): chosenGrid = 0;
		break;
	case (1): chosenGrid = 2;
		break;
	case (2): chosenGrid = 1;
		break;
	}



	int cellY = (int)(pos.y / config::GRID_CELL_SIZE * 3);

	if ((cellY % 3) + chosenGrid == 2) {
		chosenGrid = (chosenGrid + 1) % 3;
	}




	// Cell x =
	// Get Collider x position
	// Divide by width of cell

	pCollider->prev_ = NULL;
	pCollider->next_ = cells_[cellX][cellY];
	cells_[cellX][cellY] = pCollider;

	if (pCollider->next_ != NULL) {
		pCollider->next_->prev_ = pCollider;
	}



}


void GridManager::CheckMovement(Collider* pCollider, glm::vec2 oldPos, glm::vec2 newPos) {

	int oldCellX = (int)(oldPos.x / config::GRID_CELL_SIZE);
	int oldCellY = (int)(oldPos.y / config::GRID_CELL_SIZE);

	int newCellX = (int)(newPos.x / config::GRID_CELL_SIZE);
	int newCellY = (int)(newPos.y / config::GRID_CELL_SIZE);

	if (oldCellX == newCellX && oldCellY == newCellY) return;


	if (pCollider->prev_ != NULL) {
		pCollider->prev_->next_ = pCollider->next_;
	}

	if (pCollider->next_ != NULL) {
		pCollider->next_->prev_ = pCollider->prev_;
	}

	if (cells_[oldCellX][oldCellY] == pCollider) {
		cells_[oldCellX][oldCellY] = pCollider->next_;
	}

	Add(pCollider);
}


void GridManager::handleCollisions() {

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

void GridManager::handleCell(int pX, int pY) {

	Collider* collider = cells_[pX][pY];

	while (collider != NULL)
	{
		// Collider checks own cell
		handleCollider(collider, collider->next_);


		// Checking the grid spaces around. THIS IS THE SITE'S IMPLEMENTATION
		if (pX > 0 && pY > 0)	handleCollider(collider, cells_[pX - 1][pY - 1]);	// Diagonal Top left
		if (pX > 0)				handleCollider(collider, cells_[pX - 1][pY]);	// Left
		if (pY > 0)				handleCollider(collider, cells_[pX][pY - 1]);	// Above
		if (pX > 0 && pY < config::GRID_CELL_COUNT - 1) {
			handleCollider(collider, cells_[pX - 1][pY + 1]);	// Diagonal Bottom left
		}


		collider = collider->next_;
	}
}

void GridManager::handleCollider(Collider* pCollider, Collider* pOther) {

	while (pOther != NULL) {

		// Increase collision checks by 1
		collisionTestCount++;

		if (pCollider->checkCollision(pOther)) {
			// Increase collisions measured by 1
			numberOfCollisions++;

			// Setting the material to the colliding colors
			pCollider->setMaterial(greenMaterialYesCol);
			pOther->setMaterial(greenMaterialYesCol);
		}

		pOther = pOther->next_;
	}


}


void GridManager::ResetColors() {

	// Go through all colliders and set their material 
	for (int i = 0; i < config::GRID_CELL_COUNT; i++) {
		for (int j = 0; j < config::GRID_CELL_COUNT; j++) {

			Collider* collider = cells_[i][j];

			while (collider != NULL) {

				collider->setMaterial(redMaterialNoCol);

				collider = collider->next_;

			}

		}
	}


}


/**/