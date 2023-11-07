/**
 * Project Untitled
 */


#ifndef _ROBOTCOMMANDER_H
#define _ROBOTCOMMANDER_H

#include "Robots/Platform.h"
#include "Moving.h"
#include "Ruling.h"


class RobotCommander: public Platform, public Moving, public Ruling {
public: 
    
/**
 * ind - ind in platforms array of manage module settle on this robot commander
 * @param ind
 */
void getReport(int ind);
    
/**
 * ind - ind in platforms array of manage module settle on this robot commander
 * @param ind
 * @param vector
 */
void moveRobo(int ind, std::pair vector);
    
/**
 * move - moves with his subordinates
 * @param vector
 */
void move(std::pair vector);
    
/**
 * cant delete manage module
 * 
 * @param ind
 */
void deleteModule(int ind);
    
/**
 * cant place more than one manage module
 * @param ind
 */
void placeModule(int ind);
};

#endif //_ROBOTCOMMANDER_H