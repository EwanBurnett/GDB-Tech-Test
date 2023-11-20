/* Games Development Bootcamp Technical Test
 * Ewan Burnett - 2023
 * Computes the intersection between a Circle Segment and a number of points,
 * based on Field of View and distance. 
 * The actual implementation of the function can be found within Solver.h
 */

#include <cstdio>
#include <vector>
#include "Vector2.h"
#include "Solver.h"

using namespace Helpers;

int main(){
    try {
        printf("The Developer Academy Game Development Bootcamp Technical Challenge\nEwan Burnett - 2023\n");

        std::vector<Helpers::Entity> world = Helpers::LoadEntityData("Data/TestData.csv");
        printf("Testing %lu entites.\n", world.size());

        Entity* pStart = &*world.begin(); 
        Entity* pEnd = &*world.begin() + world.size(); 
        float FoV = 45.0f; 
        float distance = 20.0f;
        Entity& viewer = world[0]; 
        std::vector<uint32_t> visible = VisibleEntities(viewer, pStart, pEnd, FoV, distance); 

        printf("Found %lu visible entities.\n", visible.size());
    }
    catch (std::exception& e) {
        fprintf(stderr, e.what());
        assert(false); 
    }
}

