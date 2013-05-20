//
//  SFGamePlayer.h
//  ShakeForFood
//
//  Created by Yang David on 5/17/13.
//
//

#ifndef __ShakeForFood__SFGamePlayer__
#define __ShakeForFood__SFGamePlayer__

#include <iostream>
#include "cocos2d.h"
#include "SFGameSprite.h"

using namespace cocos2d;

class SFGamePlayer: public SFGameSprite {
    
private:
    
    float speed;
    
public:
    
    SFGamePlayer(void);
    ~SFGamePlayer(void);
    SFGamePlayer(const char * gameName);
    
    virtual void tick();
    virtual void setPosition(CCPoint inPoint);
    virtual bool collision();
    CCSize getSize();
    
    bool isCollision(SFGameSprite * inGameSprite);
    float getSpeed();
     
};


#endif /* defined(__ShakeForFood__SFGamePlayer__) */
