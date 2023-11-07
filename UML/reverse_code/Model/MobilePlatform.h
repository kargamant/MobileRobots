/**
 * Project Untitled
 */


#ifndef _MOBILEPLATFORM_H
#define _MOBILEPLATFORM_H

#include "Robots/Platform.h"
#include "Moving.h"


class MobilePlatform: public Platform, public Moving {
public: 
    
/**
 * @param vector
 */
void move(std::pair vector);
};

#endif //_MOBILEPLATFORM_H