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
        float FoV = 60.0f; 
        float distance = 10.0f;
        Entity& viewer = world[0]; 
        std::vector<uint32_t> visible = VisibleEntities(viewer, pStart, pEnd, FoV, distance); //TODO: Unit Tests

        printf("Found %lu visible entities.\n", visible.size());
    }
    catch (std::exception& e) {
        fprintf(stderr, e.what());
        assert(false); 
    }
}

