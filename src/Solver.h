#ifndef __SOLVER_H
#define __SOLVER_H

#include <cstdint>
#include <vector>
#include "Vector2.h"

namespace Helpers{

    //Represents a Cardinal direction. 
    enum class EDirection{
        NONE = 0,
        NORTH,
        SOUTH,
        EAST,
        WEST,
    };

    struct Entity{
        uint32_t ID;
        Vector2 position; 
        EDirection direction; 
    };

    const float PI = 3.14159265; 

    float DegToRad(float degrees) {
        return degrees * (PI / 180.0f); 
    }

    float RadToDeg(float radians) {
        return radians * (180.0f / PI);
    }

    /* Computes which entities are within the field of view of a given entity. 
     * entity - The entity we're viewing the scene from. 
     * pStart - pointer to the start of the range of entities to check. 
     * pEnd - pointer to the end of the range of entities to check. 
     * FoVdegrees - The entity's field of view, in degrees. 
     * distance - The maximum distance the entity can see up to. 
     * outIDs - output array of visible Entity IDs
     */
    inline std::vector<uint32_t> VisibleEntities(const Entity& entity, Entity* pStart, const Entity* pEnd, const float FoVdegrees, const float distance){

        std::vector<uint32_t> out{}; //Output vector

        //Iterate over each entity in the given range. 
        for(Entity* pOther = pStart; pOther < pEnd; pOther++){
            //Don't perform any checks against the same entity
            if(pOther == &entity){
                continue;
            }
           
            //If the other entity intersects with the bounding sphere centered on this entity, with radius = distance, continue. 
            Vector2 toPoint = pOther->position - entity.position; 
            if(Vector2::Length(toPoint) > distance){
               continue;    //The point lies outside of the sphere's radius. 
            }
            
            //Compare the angle between this entity and the other entity. 
            Vector2 toOther = Vector2::Normalize(pOther->position - entity.position);
            Vector2 direction = {};
            switch(entity.direction){
                case EDirection::NORTH:
                    direction = {0.0f, 1.0f};
                    break;
                case EDirection::SOUTH:
                    direction = {0.0f, -1.0f};
                    break;
                case EDirection::EAST:
                    direction={1.0f, 0.0f};
                    break;
                case EDirection::WEST:
                    direction={-1.0f, 0.0f};
                    break;
                case EDirection::NONE:
                default:
                    break;
            }

            //Rotate the Forwards Vector by -FoV / 2 radians. 
            const float FoVradians = DegToRad(FoVdegrees);
            const float halfFoVradians = FoVradians / 2.0f;
            const Vector2 arcStart = {
                direction.x * cosf(halfFoVradians) + direction.y * (-sinf(halfFoVradians)), 
                direction.x * sinf(halfFoVradians) + direction.y * cosf(halfFoVradians)
            };

            //The angle (radians) between the start of the arc and the other entity. 
            float fDotOther = Vector2::Dot(arcStart, toOther);


            if (Vector2::Dot(direction, toOther) < 0.0) {
                continue;   //The other point is behind this one.
            }

            //If the angle (in radians) between the forwards vector and the object is within bounds, then a collision has occurred. 
            if(fDotOther > 0.0 && fDotOther <= FoVradians){
                printf("FoV %.4fdeg (%.4frad)\nIntersection with Entity [%d] -> [%d]\n\tForwards Vector: (%f, %f) {%.4fdeg} {%.4frad}\n\tArc Start Vector: (%f, %f) {%.4fdeg} {%.4frad}\n\tArc -> [%d]: (%.4f, %.4f) {%.4fdeg} {%.4frad}\n", FoVdegrees, DegToRad(FoVdegrees), entity.ID, pOther->ID, direction.x, direction.y, 0.0f, 0.0f, arcStart.x, arcStart.y, 0.0f, 0.0f, pOther->ID, toOther.x, toOther.y, RadToDeg(fDotOther), fDotOther);
                out.push_back(pOther->ID);
            }            

        }

        return out;
    }
    
}
#endif
