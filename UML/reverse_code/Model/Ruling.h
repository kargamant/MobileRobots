/**
 * Project Untitled
 */


#ifndef _RULING_H
#define _RULING_H

class Ruling {
public: 
    
/**
 * @param ind
 */
virtual void getReport(int ind) = 0;
    
/**
 * @param ind
 * @param vector
 */
virtual void moveRobo(int ind, std::pair vector) = 0;
};

#endif //_RULING_H