#include <cstdio>
#include "Vector2.h"
#include "MathsHelper.h"

using namespace Helpers;

int main(){
    printf("Hello, World!\n");

    //TODO: Test Cases
    Vector2 v = {-10.0f, 5.0f};
    Vector2 n = Vector2::Normalize(v); 
    float l = Vector2::Length(v); 
    float dot = Vector2::Dot(v, {1.0, 0.0});
    printf("Vector v = (%f, %f)\n\tNormalize = (%f, %f)\n\tLength = %f\n\tDot = %f\n", v.x, v.y, n.x, n.y, l, dot);
}
