/**
 * Project Untitled
 */


#ifndef _ROBOTDESTROYER_H
#define _ROBOTDESTROYER_H

#include "Robots/Platform.h"
#include "Moving.h"
#include "Destroying.h"


class RobotDestroyer: public Platform, public Moving, public Destroying {
public: 
    
/**
 * Destroys an obstacle, when moving through
 * 
 * @param vector
 */
void move(std::pair vector);
    
/**
 * call sensor to find obstacles. shoot in chosen one
 * @param radius
 */
void Destroy(int radius);
};

#endif //_ROBOTDESTROYER_H