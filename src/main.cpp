#include <cstdio>
#include <vector>
#include "Vector2.h"
#include "Solver.h"

using namespace Helpers;

int main(){
    //printf(">> %f\n", atan2(1.0f, 3.0f) * 180.0/3.14159);
    printf("The Developer Academy Game Development Bootcamp Technical Challenge\nEwan Burnett - 2023\n");

    std::vector<Helpers::Entity> world(20);  //TODO: I/O
    printf("Testing %d entites.\n", world.size());


    std::vector<uint32_t> visible = VisibleEntities(world[0], &*world.begin(), &*world.end(), 60.0f, 10.0f);

    printf("Found %d visible entities.\n", visible.size());
}

