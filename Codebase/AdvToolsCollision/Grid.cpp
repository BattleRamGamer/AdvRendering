#include "Grid.hpp"

Grid::Grid() {
	for (int i = 0; i < config::GRID_COLUMN_COUNT; i++) {
		for (int j = 0; j < config::GRID_ROW_COUNT; j++) {
			cells_[i][j] = NULL;
		}
	}
}

Grid::~Grid() {

}

void Grid::Add(Collider* pCollider) {

	glm::vec2 pos = ((MoveBehaviour*)pCollider->getBehaviour())->GetPosition();

	// Cell x =
	// Get Collider x position
	// Divide by width of cell
	int cellX = (int)(pos.x / config::GRID_CELL_SIZE);
	int cellY = (int)(pos.y / config::GRID_CELL_SIZE);

	pCollider->prev_ = NULL;
	pCollider->next_ = cells_[cellX][cellY];
	cells_[cellX][cellY] = pCollider;

	if (pCollider->next_ != NULL) {
		pCollider->next_->prev_ = pCollider;
	}



}

void Grid::handleCollisions() {
	for (int i = 0; i < config::GRID_CELL_COUNT; i++) {
		for (int j = 0; j < config::GRID_CELL_COUNT; j++) {

			// Only handles own cell!
			handleCell(cells_[i][j]);
		}
	}
}

void Grid::handleCell(Collider* pCollider) {
	while (pCollider != NULL)
	{
		Collider* other = pCollider->next_;
		while (other != NULL)
		{

			pCollider->checkCollision(other);

			other = other->next_;
		}

		pCollider = pCollider->next_;
	}
}