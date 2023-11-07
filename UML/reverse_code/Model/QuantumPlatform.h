/**
 * Project Untitled
 */


#ifndef _QUANTUMPLATFORM_H
#define _QUANTUMPLATFORM_H

#include "Robots/Platform.h"


class QuantumPlatform: public Platform {
public: 
    
/**
 * @param platform
 */
void link(QuantumPlatform& platform);
    
/**
 * @param ind
 */
void teleport(int ind);
    
/**
 * cant delete energy generators(cause platform can be too far away)
 * 
 * 
 * @param ind
 */
void deleteModule(int ind);
    
/**
 * cant place manage modules
 * @param ind
 */
void placeModule(int ind);
private: 
    int linked;
    int linkageRadius;
    QuantumPlatform* platforms;
};

#endif //_QUANTUMPLATFORM_H