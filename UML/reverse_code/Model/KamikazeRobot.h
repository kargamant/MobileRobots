/**
 * Project Untitled
 */


#ifndef _KAMIKAZEROBOT_H
#define _KAMIKAZEROBOT_H

#include "Destroying.h"
#include "Robots/Platform.h"


class KamikazeRobot: public Destroying, public Platform {
public: 
    
/**
 * destroys EVERYTHING(including kamikaze robot itslef) in a certain radius.
 * @param radius
 */
void Destroy(int radius);
private: 
    /**
 * Maximum radius of explotion
 */
int maxRadius;
};

#endif //_KAMIKAZEROBOT_H