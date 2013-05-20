//
//  SFGameSprite.h
//  ShakeForFood
//  
//  Created by Yang David on 5/17/13.
//  
//  @auther weflytotti@qq.com

#ifndef __ShakeForFood__SFGameSprite__
#define __ShakeForFood__SFGameSprite__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

/* ------------------------------------------------------------------
 *
 * ! Game Sprite base class
 *
 * ------------------------------------------------------------------*/

class SFGameSprite :public CCNode {
     
protected:
    
    CCSprite * gameSprite;
    int state;
    
public:
    
    SFGameSprite(void);
    ~SFGameSprite(void);
    SFGameSprite(char * name);
    
    virtual void tick();
    virtual void setPosition(CCPoint inPoint);
    virtual bool collision();
    virtual CCSize getSize();
    
    CCSprite * getSprite();
    bool isCollision(SFGameSprite * collisionSprite);
    void setState(int inState);
    int getState();
    

};

#endif /* defined(__ShakeForFood__SFGameSprite__) */
