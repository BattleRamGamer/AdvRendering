#ifndef DATATRACKER_HPP
#define DATATRACKER_HPP

#include <vector>
#include <string>

/**
 Stores data in the following order:
 AABB Collider amount
 Circle collider amount
 Ignore repeat collision checks
 Enable spatial partitioning
 Enable triple grid method
 Enable double dispatch
 Number of frames to test
 Number of cells in one Grid row/column
 */
class DataTracker {


public:
	DataTracker();
	virtual ~DataTracker();

	// Should be called at the end of every frame
	void StoreFrameData(int pFrameCount, float pFrameTime, float pElapsedTime, int pChecksPerformed, int pCollisions);

	// When the test is finished, write the data to the .csv file
	void WriteDataToFile();

protected:

	//int seed;
	std::string BoolToString(bool pBool);

	// Name of the .csv file to write to
	std::string _fileName;

	// Consistent data for every frame
	std::string _constantData;

	// This will eventually all get written to the .csv file
	std::vector<std::string> _data;



};







#endif // DATATRACKER_HPP
