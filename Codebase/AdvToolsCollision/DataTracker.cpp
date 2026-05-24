#include "DataTracker.hpp"
#include <fstream>
#include "mge/config.hpp"
#include <time.h>


DataTracker::DataTracker() {
	// Set seed
	// Set fileName
	// Set constantData

    _fileName = "test-"
        + std::to_string(config::AABB_COLLIDER_AMOUNT)
        + "-" + std::to_string(config::CIRCLE_COLLIDER_AMOUNT)
        + "-" + BoolToString(config::USE_IGNOREHISTORY)
        + "-" + BoolToString(config::USE_SPATIALPARTITIONING)
        + "-" + BoolToString(config::GRID_TRIPLE)
        + "-" + BoolToString(config::USE_DOUBLEDISPATCH)
        + "-" + std::to_string(config::TEST_FRAME_COUNT)
        + "-" + std::to_string(config::GRID_CELL_COUNT);
    


    // Setting seed, NOT NECESSARY! Seed is always the same if you don't specify to randomize seed
    //srand(0);
    

}

DataTracker::~DataTracker() {
    _data.clear();
}

void DataTracker::StoreFrameData(int pFrameCount, float pFrameTime, float pElapsedTime, int pChecksPerformed, int pCollisions) {
    _data.push_back(
        std::to_string(pFrameCount) + "," +
        std::to_string(pFrameTime) + "," + 
        std::to_string(pElapsedTime) + "," +
        std::to_string(pChecksPerformed) + "," + 
        std::to_string(pCollisions));
}

void DataTracker::WriteDataToFile() {
    std::ofstream myfile;

    // Writing to fileName. Use std::ios::app to append the new results, ::out to override previous results
    myfile.open("../../Raw results/" + _fileName + ".csv", std::ios::app);

    myfile << "Frame count,Frame time(ms),Elapsed time(s),Checks performed,Collisions happening\n";

    for (int i = 0; i < _data.size(); i++) {

        // Add to new row: frame data and make the next one look at the next line
        myfile << _data[i] + "\n ";
    }

    myfile.close();
}


std::string DataTracker::BoolToString(bool pBool) {
    return pBool ? "true" : "false";
}