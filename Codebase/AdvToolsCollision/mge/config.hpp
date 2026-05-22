#ifndef CONFIG_HPP
#define CONFIG_HPP



#include <string>

namespace config {
    const std::string MGE_MODEL_PATH ("./mge/models/");
    const std::string MGE_TEXTURE_PATH ("./mge/textures/");
    const std::string MGE_SHADER_PATH ("./mge/shaders/");
    const std::string MGE_FONT_PATH ("./mge/fonts/");


    const int AABB_COLLIDER_AMOUNT(100);
    const int CIRCLE_COLLIDER_AMOUNT(100);

    // Ignore collision checks that already happened (Irrelevant if spatial partitioning is used)
    const bool USE_IGNOREHISTORY(true);

    // Use spatial partitioning. 
    const bool USE_SPATIALPARTITIONING(true);

    // Use my special implementation of spatial partitioning with three grids instead of one
    const bool GRID_TRIPLE(false);

    // Let C++ check what two collider types to check for (True) OR use an if-statement to check (False) 
    const bool USE_DOUBLEDISPATCH(true);

    
    // If triple grid, Boundary Size should be (Cell Count - 1) * Cell Size
    const float BOUNDARY_SIZE(40.0f);
    // Since the colliders are 2 big, the lowest this should go is 6
    const float GRID_CELL_SIZE(6.0f);
    // (Cell count - 1) * Cell size should be bigger than the boundary size
    const int GRID_CELL_COUNT(8);


    // Time in seconds to test for
    const int TEST_TIME(10);
    // Number of frames to test
    const int TEST_FRAME_COUNT(36000);
    // Test for a set amount of: True = Time, False = Frames. I'll use frames, so this should be false
    const bool USE_TEST_METHOD_TIME(false);


    // Remove the limit of 60 frames per second
    const bool REMOVE_FPS_CAP(true);





}

#endif // CONFIG_HPP