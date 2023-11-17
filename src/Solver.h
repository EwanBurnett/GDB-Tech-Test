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

            float fDotOther = Vector2::Dot(direction, toOther);

            //The start and end angles of the Field of View

            out.push_back(pOther->ID);

        }

        return out;
    }
    
}
#endif
