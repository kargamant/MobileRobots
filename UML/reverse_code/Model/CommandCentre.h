/**
 * Project Untitled
 */


#ifndef _COMMANDCENTRE_H
#define _COMMANDCENTRE_H

#include "Robots/Platform.h"
#include "Ruling.h"


class CommandCentre: public Platform, public Ruling {
public: 
    
/**
 * ind - ind in platforms array of manage module settle on this robot commander
 * @param ind
 * @param vector
 */
void moveRobo(int ind, std::pair vector);
    
/**
 * ind - ind in platforms array of manage module settle on this robot commander
 * @param ind
 */
void getReport(int ind);
    
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

#endif //_COMMANDCENTRE_H