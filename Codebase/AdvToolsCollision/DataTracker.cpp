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
        + "-" + std::to_string(config::USE_IGNOREHISTORY)
        + "-" + std::to_string(config::USE_QUADTREE)
        + "-" + std::to_string(config::USE_DOUBLEDISPATCH);

    //_constantData = std::string config::AABB_COLLIDER_AMOUNT;
    // 
    // set seed
    //srand(0);
    
    seed = 0;
    printf("%s;%d",_fileName.c_str(), rand()%15);
}

DataTracker::~DataTracker() {

}

void SetData() {

}

void DataTracker::StoreFrameData() {

}

void DataTracker::WriteDataToFile() {
    std::ofstream myfile;

    // Writing to fileName
    myfile.open("../../Raw results/" + _fileName, std::ios::app);

    myfile << "Order";

    for (int i = 0; i < _data.size(); i++) {

        // Add to new row: Constant data, frame data and make the next one look at the next line
        myfile << _constantData + _data[i] + "\n ";
    }

    myfile << "This is the first cell in the first column.\n";
    myfile << "a,b,c,\n";
    myfile << "c,s,v,\n";
    myfile << "1,2,3.456\n";
    myfile << "semi;colon";
    myfile.close();
}