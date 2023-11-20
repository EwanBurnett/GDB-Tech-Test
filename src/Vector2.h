#ifndef __VECTOR2_H
#define __VECTOR2_H

#include <cmath> 

namespace Helpers{
    const double PI = 3.14159265359; 

    float DegToRad(float degrees) {
        return degrees * (PI / 180.0); 
    }

    float RadToDeg(float radians) {
        return radians * (180.0 / PI);
    }

    struct Vector2{
        float x, y;

        Vector2 operator + (const Vector2& rhs){
            return {x + rhs.x, y + rhs.y};
        }


        Vector2 operator - (const Vector2& rhs){
            return {x - rhs.x, y - rhs.y};
        }

        static float Dot(const Vector2& a, const Vector2& b);
        static float Length(const Vector2& vec);
        static Vector2 Normalize(const Vector2& vec);
        static Vector2 Rotate(const Vector2& vec, const float angle);
        static float ToDegrees(const Vector2& vec);
        static float ToRadians(const Vector2& vec);
    };

    //Returns the Dot Product of two vectors. 
    //This value gives the cosine of the angle between two vectors. 
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

    //Rotates a Vector clockwise
    inline Vector2 Vector2::Rotate(const Vector2& vec, const float angle) {
        const float radians = DegToRad(angle);     //This matrix rotates anticlockwise, so negate the angle for a clockwise rotation.
        return{
            (vec.x * cosf(radians)) + (vec.y * (sinf(radians))),
            (vec.x * -sinf(radians)) + (vec.y * cosf(radians))   
        };
    }

    //Converts a Vector2 to degrees. 
    inline float Vector2::ToDegrees(const Vector2& vec)
    {
        return RadToDeg(atan2(vec.x, vec.y));
    }

    //Converts a Vector2 to radians. 
    inline float Vector2::ToRadians(const Vector2& vec)
    {
        return atan2(vec.x, vec.y);
    }


}
#endif
