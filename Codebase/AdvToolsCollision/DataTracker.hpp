#ifndef DATATRACKER_HPP
#define DATATRACKER_HPP

#include <vector>
#include <string>


class DataTracker {


public:
	DataTracker();
	virtual ~DataTracker();

	// Should be called at the end of every frame
	void StoreFrameData();

	// When the test is finished, write the data to the .csv file
	void WriteDataToFile();

protected:

	int seed;


	// Name of the .csv file to write to
	std::string _fileName;

	// Consistent data for every frame
	std::string _constantData;

	// This will eventually all get written to the .csv file
	std::vector<std::string> _data;



};







#endif // DATATRACKER_HPP
