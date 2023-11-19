#include <cstdio>
#include <vector>
#include "Vector2.h"
#include "Solver.h"

using namespace Helpers;

int main(){
    printf(">> %f\n", atan2(cos(0), sin(0)) * 180.0/3.14159);
    printf("The Developer Academy Game Development Bootcamp Technical Challenge\nEwan Burnett - 2023\n");

    std::vector<Helpers::Entity> world(20);  //TODO: I/O
    for(int i = 0; i < 20; i++){
        world[i].ID = i; 
        world[i].direction = Helpers::EDirection((i % 4) + 1);
        world[i].position = {0.0f, i * 1.0f};//{1.5f * i, -1.5f * (i % 3)};
    }
    printf("Testing %lu entites.\n", world.size());


    std::vector<uint32_t> visible = VisibleEntities(world[1], &*world.begin(), &*world.end(), 60.0f, 100.0f);

    printf("Found %lu visible entities.\n", visible.size());
}

