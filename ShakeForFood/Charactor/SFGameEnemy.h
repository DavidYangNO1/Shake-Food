//
//  SFGameEnemy.h
//  ShakeForFood
//
//  Created by Yang David on 5/17/13.
//
//

#ifndef __ShakeForFood__SFGameEnemy__
#define __ShakeForFood__SFGameEnemy__

#include <iostream>
#include "cocos2d.h"
#include "SFGameSprite.h"

using namespace cocos2d;

class SFGameBullet;
class SFGamePlayer;

class SFGameEnemy : public SFGameSprite {
    
private:
    
    CCMotionStreak * streak;
    
public:
    
    SFGameEnemy(void);
    ~SFGameEnemy(void);
    SFGameEnemy(const char * s);
    
    void setDead();
    void restart();
    
    virtual void tick();
    virtual void setPosition(CCPoint inPoint);
   
    bool collision(SFGamePlayer * collisionPlayer);
    CCSize getSize();
    
    bool collisionWithBullet(SFGameBullet * collisionBullet);
    bool isCollision(SFGameSprite * collisionSprite);
    
    CCMotionStreak * getStreak();
    void chooseFlyType();
    
};

#endif /* defined(__ShakeForFood__SFGameEnemy__) */
