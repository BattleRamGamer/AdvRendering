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
    

    // Add cell size and stuff?


    //_constantData = std::string config::AABB_COLLIDER_AMOUNT;
    // 
    // set seed
    //srand(0);
    
    //seed = 0;
    //printf("%s;%d",_fileName.c_str(), rand()%15);
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
    myfile.open("../../Raw results/" + _fileName + ".csv", std::ios::out);

    myfile << "Frame time,Elapsed time,Checks performed,Collisions happening\n";

    for (int i = 0; i < _data.size(); i++) {

        // Add to new row: frame data and make the next one look at the next line
        myfile << _data[i] + "\n ";
    }
    /**
    myfile << "This is the first cell in the first column.\n";
    myfile << "a,b,c,\n";
    myfile << "c,s,v,\n";
    myfile << "1,2,3.456\n";
    myfile << "semi;colon";
    /**/
    myfile.close();
}


std::string DataTracker::BoolToString(bool pBool) {
    return pBool ? "true" : "false";
}