#ifndef __SOLVER_H
#define __SOLVER_H

#include <cstdint>
#include <vector>
#include "Vector2.h"

#include <fstream> 
#include <string>
#include <assert.h>

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


    /* Loads Entity Data from a CSV file. 
     * note: No input validation is performed in this function. 
     */
    std::vector<Entity> LoadEntityData(const std::string& filePath) {
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
                    return EDirection::NORTH;
                }
                else if (dir == "South") {
                    return EDirection::SOUTH; 
                }
                else if (dir == "East") {
                    return EDirection::EAST;
                }
                else if (dir == "West") {
                    return EDirection::WEST;
                }
                return EDirection::NONE;
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

            //Cull points that are behind this one. 
            if (Vector2::Dot(direction, toOther) < 0.0) {
                continue;   //The other point is behind this one.
            }

            //Rotate the Forwards Vector by -FoV / 2 radians. 
            const float FoVradians = DegToRad(FoVdegrees);
            const float halfFoVradians = DegToRad(FoVdegrees / 2.0f);
            const Vector2 arcStart = Vector2::Rotate(direction, -(FoVdegrees / 2.0f)); //BUG: There seems to be an error in this rotation.
            
            //The angle (radians) between the start of the arc and the other entity. 
            float fDotOther = Vector2::Dot(arcStart, toOther);


            //If the angle (in radians) between the forwards vector and the object is within bounds, then a collision has occurred. 
            if(fDotOther > 0.0 && fDotOther <= FoVradians){
                float af = Vector2::Dot(arcStart, direction);
                printf("FoV %.4fdeg (%.4frad)\nIntersection with Entity [%d] -> [%d]\n\tForwards Vector: (%f, %f) {%.4fdeg} {%.4frad}\n\tArc Start Vector: (%f, %f) {%.4fdeg} {%.4frad}\n\tArc -> [%d]: (%.4f, %.4f) {%.4fdeg} {%.4frad}\n", FoVdegrees, DegToRad(FoVdegrees), entity.ID, pOther->ID, direction.x, direction.y, 0.0f, 0.0f, arcStart.x, arcStart.y, RadToDeg(af), af, pOther->ID, toOther.x, toOther.y, RadToDeg(fDotOther), fDotOther);
                out.push_back(pOther->ID);
            }            

        }

        return out;
    }
    
}
#endif
