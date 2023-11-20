#ifndef __SOLVER_H
#define __SOLVER_H

#include <cstdint>
#include <vector>
#include "Vector2.h"

#include <fstream> 
#include <string>
#include <assert.h>

namespace Helpers{

    const Vector2 DirectionMappings[] = {
        {0.0f, 1.0f},   //NORTH
        {0.0f, -1.0f},  //SOUTH
        {1.0f, 0.0f},   //EAST
        {-1.0f, 0.0f}   //WEST
    };

    //Represents a Cardinal direction. 
    enum class EDirection{
        NORTH,
        SOUTH,
        EAST,
        WEST,
    };

    struct Entity{
        uint32_t ID;
        Vector2 position; 
        Vector2 direction; 
    };



    /* Loads Entity Data from a CSV file. 
     * note: No input validation is performed in this function. 
     */
    inline std::vector<Entity> LoadEntityData(const std::string& filePath) {
        printf("Loading file %s.\n", filePath.c_str());

        std::ifstream file(filePath);
        if (!file.is_open()) {
            throw std::runtime_error("[Error]\tUnable to open File!\n");
        }
        
        auto parse = [](std::string& str, char delimiter = ',') {
            //Read from the beginning of the string to the delimiter, and pop. 
            auto p = str.find(delimiter);
            std::string token = str.substr(0, p);
            str.erase(0, p + 1);    //Erase the extracted token + the delimiter from the string. 
            return token; 
        };

        std::vector<Entity> out;
        int idx = 1; //Line index 
        std::string line; 
        std::getline(file, line);   //Ignore the top row
        while (std::getline(file, line)) {  //Read each line of the CSV into the entity
            printf("[%d]\t%s\n", idx, line.c_str());
            Entity e{};

            e.position.x = std::stof(parse(line));
            e.position.y = std::stof(parse(line));
            e.ID = std::stoi(parse(line)); 
            e.direction = [&]() {
                const auto dir = parse(line); 
                if (dir == "North") {
                    return DirectionMappings[(int)EDirection::NORTH];
                }
                else if (dir == "South") {
                    return DirectionMappings[(int)EDirection::SOUTH];
                }
                else if (dir == "East") {
                    return DirectionMappings[(int)EDirection::EAST];
                }
                else if (dir == "West") {
                    return DirectionMappings[(int)EDirection::WEST];
                }
                return Vector2{ 0, 0 };
            }();

            out.push_back(e); 
            idx++; 
        }

        printf("Finished loading data.\n");
        return out; 

    }

    /* Computes which entities are within the field of view of a given entity. 
     * entity - The entity we're viewing the scene from. 
     * pStart - pointer to the start of the range of entities to check. 
     * pEnd - pointer to the end of the range of entities to check. 
     * FoVdegrees - The entity's field of view, in degrees. 
     * distance - The maximum distance the entity can see up to. 
     * outIDs - output array of visible Entity IDs
     * note: The use of input pointers is intended to enable the programmer to implement some sort of space partitioning algorithm, to reduce potential intersection tests. As well as to provide functionality for c-style arrays. 
     */
    inline std::vector<uint32_t> VisibleEntities(const Entity& entity, Entity* pStart, const Entity* pEnd, const float FoVdegrees, const float distance){
        
        std::vector<uint32_t> out{}; //Output vector


        //Rotate the Forwards Vector by -FoV / 2 radians. 
        const float FoVradians = DegToRad(FoVdegrees);
        const float halfFoVradians = DegToRad(FoVdegrees / 2.0f);
        const Vector2 arcStart = Vector2::Rotate(entity.direction, -(FoVdegrees / 2.0f)); 
        const float distSquared = distance * distance;
        float arcAngle = Vector2::ToRadians(arcStart); 

        //Iterate over each entity in the given range. 
        for(Entity* pOther = pStart; pOther < pEnd; pOther++){
            //Don't perform any checks against the same entity
            if(pOther == &entity){
                continue;
            }
           
            //If the other entity intersects with the bounding sphere centered on this entity, with radius = distance, continue. 
            Vector2 toOther = pOther->position - entity.position; 
            float distToOtherSquared = (toOther.x * toOther.x) + (toOther.y * toOther.y); //Avoid expensive sqrt, and compute overlap based on squares. 
            if(distToOtherSquared > distSquared){
               continue;    //The point lies outside of the sphere's radius. 
            }
            
            //Compare the angle between this entity and the other entity. 
            toOther = Vector2::Normalize(toOther);
                     
            //The angle (radians) between the start of the arc and the other entity. 
            float aDotOther = acosf(Vector2::Dot(arcStart, toOther));         
            float otherAngle = Vector2::ToRadians(toOther); 

          
            //If the angle (in radians) between the forwards vector and the object is within bounds, then a collision has occurred. 
            if(otherAngle >= arcAngle && aDotOther <= FoVradians){
                out.push_back(pOther->ID);
            }            

        }

        return out;
    }
    
}
#endif
