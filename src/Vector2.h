#ifndef __VECTOR2_H
#define __VECTOR2_H

#include <cmath> 

namespace Helpers{
    struct Vector2{
        float x, y;
        

        Vector2 operator - (const Vector2& rhs){
            return {x - rhs.x, y - rhs.y};
        }

        static float Dot(const Vector2& a, const Vector2& b);
        static float Length(const Vector2& vec);
        static Vector2 Normalize(const Vector2& vec);
        static Vector2 Rotate(const Vector2& vec, const float angle);
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

    inline Vector2 Vector2::Rotate(const Vector2& vec, const float angle) {
        return{
                cosf(angle) * vec.x - sinf(angle) * vec.y, 
                sinf(angle) * vec.x + cosf(angle) * vec.y
            };
    }


}
#endif
