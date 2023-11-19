#include <cstdio>
#include <vector>
#include "Vector2.h"
#include "Solver.h"

using namespace Helpers;

int main(){
    printf("The Developer Academy Game Development Bootcamp Technical Challenge\nEwan Burnett - 2023\n");

    std::vector<Helpers::Entity> world(20);  //TODO: I/O
    for(int i = 0; i < 20; i++){
        world[i].ID = i; 
        world[i].direction = Helpers::EDirection((i % 4) + 1);
        world[i].position = {(i % 4) * 5.5f * (i - 5), (i - 10) * 1.0f};//{1.5f * i, -1.5f * (i % 3)};
    }
    printf("Testing %lu entites.\n", world.size());

    std::vector<uint32_t> visible = VisibleEntities(world[12], &*world.begin(), &*world.begin() + 20, 90.0f, 5.0f);

    printf("Found %lu visible entities.\n", visible.size());
}

