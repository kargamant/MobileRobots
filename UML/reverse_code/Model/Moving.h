/**
 * Project Untitled
 */


#ifndef _MOVING_H
#define _MOVING_H

class Moving {
public: 
    
/**
 * @param vector
 */
virtual void move(std::pair vector) = 0;
private: 
    int velocity;
};

#endif //_MOVING_H