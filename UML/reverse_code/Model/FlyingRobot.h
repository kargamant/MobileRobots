/**
 * Project Untitled
 */


#ifndef _FLYINGROBOT_H
#define _FLYINGROBOT_H

#include "Robots/Platform.h"
#include "Moving.h"


class FlyingRobot: public Platform, public Moving {
public: 
    
/**
 * Just flies by obstacle, if goes through
 * 
 * @param vector
 */
void move(std::pair vector);
};

#endif //_FLYINGROBOT_H