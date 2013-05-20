//
//  SFGameBullet.h
//  ShakeForFood
//
//  Created by Yang David on 5/17/13.
//
//

#ifndef __ShakeForFood__SFGameBullet__
#define __ShakeForFood__SFGameBullet__

#include <iostream>
#include "SFGameSprite.h"
#include "cocos2d.h"

using namespace cocos2d;

class SFGamePlayer;

class SFGameBullet : public SFGameSprite {
     
private:
    
    CCMotionStreak * streak;
    
    int type;
    
public:
    
    SFGameBullet(void);
    ~SFGameBullet();
    SFGameBullet(const char * s);
    
    virtual void tick();
    virtual void setPosition(CCPoint inPoint);
    virtual bool collision(SFGamePlayer * play);
    virtual CCSize getSize();
    
    CCMotionStreak * getStreak();
    void setType(int inType);
    int getType();
    
     
};

#endif /* defined(__ShakeForFood__SFGameBullet__) */
