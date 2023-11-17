#ifndef __VECTOR2_H
#define __VECTOR2_H

#include <cmath> 

namespace Helpers{
    struct Vector2{
        float x, y;
        
        static float Dot(const Vector2& a, const Vector2& b);
        static float Length(const Vector2& vec);
        static Vector2 Normalize(const Vector2& vec);
    };

    //Returns the Dot Product of two vectors. 
    //This value gives the angle between two vectors, in radians. 
    inline float Vector2::Dot(const Vector2& a, const Vector2& b){
        return (a.x * b.x) + (a.y * b.y); 
    }

    //Returns the Length (or modulus) of a 2D Vector. 
    inline float Vector2::Length(const Vector2& vec){
        return sqrtf((vec.x * vec.x) + (vec.y * vec.y)); 
    }

    //Normalizes a Vector. 
    inline Vector2 Vector2::Normalize(const Vector2& vec){
        const float length = Vector2::Length(vec);
        return {vec.x / length, vec.y / length}; 
    } 


}
#endif
