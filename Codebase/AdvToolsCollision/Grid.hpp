#ifndef GRID_HPP
#define GRID_HPP


#include "Collider.hpp"


class Grid {

public:
	Grid();
	~Grid();


private:
	Collider* cells_[config::GRID_COLUMN_COUNT][config::GRID_ROW_COUNT];


};




#endif // !GRID_HPP
