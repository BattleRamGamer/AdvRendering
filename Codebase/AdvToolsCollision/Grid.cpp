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