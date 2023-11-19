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
            switch(pOther->direction){
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
            const float halfFoVradians = FoVdegrees * 0.5f;//(FoVdegrees * 0.5f) * 3.1415926 / 180.0; 
            const Vector2 arcStart = {
                direction.x * cosf(-halfFoVradians) + direction.y * (-sinf(-halfFoVradians)), 
                direction.x * sinf(-halfFoVradians) + direction.y * cosf(-halfFoVradians)
            };
            //The angle (radians) between the forwards vector and the other entity. 
            float fDotOther = Vector2::Dot(arcStart, toOther);


            //If the angle (in radians) between the forwards vector and the object is within bounds, then a collision has occurred. 
            if(fDotOther > 0.0 && fDotOther <= FoVdegrees * (3.1415926 / 180.0)){
            printf("arcStart = (%f, %f) [%fdeg]\nFdotOther = %.4frad (%.4fdeg)\tFoV = %.4frad (%.4f deg)\n ", fDotOther, arcStart.x, arcStart.y, atan(arcStart.y / arcStart.x), 180/3.1415926 * fDotOther, halfFoVradians, FoVdegrees / 2);
                out.push_back(pOther->ID);
            }            


            
            /*
            //The start and end angles of the Field of View``
            float FoVRadians = (FoVdegrees) * 3.1415926 / 180.0;
            
            Vector2 FoVOffset = Vector2::Normalize({cos(FoVRadians), sin(FoVRadians)});
            Vector2 FoVStart = Vector2::Normalize({direction.x - FoVOffset.x, direction.y - FoVOffset.y});
            
            printf("Offset: %f, %f (%f)\n", FoVStart.x, FoVStart.y, Vector2::Length(FoVStart));
            float rangeStart = atan2(FoVStart.x, FoVStart.y);           
            float rangeEnd = atan2(FoVOffset.x + direction.x, FoVOffset.y + direction.y);
            printf("[%p] %f - %f\n", pOther, rangeStart, rangeEnd);


            if(rangeStart < fDotOther && fDotOther < rangeEnd)
            */

        }

        return out;
    }
    
}
#endif
