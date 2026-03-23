#include <string>

namespace config {
    const std::string MGE_MODEL_PATH ("./mge/models/");
    const std::string MGE_TEXTURE_PATH ("./mge/textures/");
    const std::string MGE_SHADER_PATH ("./mge/shaders/");
    const std::string MGE_FONT_PATH ("./mge/fonts/");


    const int CIRCLE_COLLIDER_AMOUNT(20);
    const int AABB_COLLIDER_AMOUNT(10);
    const float BOUNDARY_POSITION(20.0f);

    // Ignore collision checks that already happened
    const bool USE_IGNOREHISTORY(true);
    // Use spatial partitioning
    const bool USE_QUADTREE(false);
    // Let C++ check what two collider types to check for
    const bool USE_DOUBLEDISPATCH(false);



    // THIS IS NOT USED YET
    // 0 = no subdivision, 1 = only top space is divided, etc.
    const int SPACE_PART_DEPTH(1);
    const int SPACE_PART_ROWS(2);
    const int SPACE_PART_COLUMNS(2);
}
