#ifndef CONFIG_HPP
#define CONFIG_HPP



#include <string>

namespace config {
    const std::string MGE_MODEL_PATH ("./mge/models/");
    const std::string MGE_TEXTURE_PATH ("./mge/textures/");
    const std::string MGE_SHADER_PATH ("./mge/shaders/");
    const std::string MGE_FONT_PATH ("./mge/fonts/");

    // Time in seconds to test for
    const int TEST_TIME(10);
    // Number of frames to test
    const int TEST_FRAME_COUNT(360);
    // Test for a set amount of: True = Time, False = Frames
    const bool USE_TEST_METHOD_TIME(false);

    const int CIRCLE_COLLIDER_AMOUNT(200);
    const int AABB_COLLIDER_AMOUNT(100);
    
    // If triple grid, Boundary Size should be (Cell Count - 1) * Cell Size
    const float BOUNDARY_SIZE(40.0f);
    const float GRID_CELL_SIZE(10.0f);
    const int GRID_CELL_COUNT(5);

    const int GRID_COLUMN_COUNT(5);
    const int GRID_ROW_COUNT(5);

    // Ignore collision checks that already happened
    const bool USE_IGNOREHISTORY(true);
    // Use spatial partitioning
    const bool USE_QUADTREE(false);
    // Let C++ check what two collider types to check for
    const bool USE_DOUBLEDISPATCH(true);


    // THIS IS NOT USED YET
    // 0 = no subdivision, 1 = only top space is divided, etc.
    const int SPACE_PART_DEPTH(1);
    const int SPACE_PART_ROWS(2);
    const int SPACE_PART_COLUMNS(2);
}

#endif // CONFIG_HPP