//
//  SFGameBullet.cpp
//  ShakeForFood
//
//  Created by Yang David on 5/17/13.
//
//

#include "SFGameBullet.h"
#include <cmath>

SFGameBullet::SFGameBullet(void){
    
}

SFGameBullet::~SFGameBullet(void){
    
}

SFGameBullet::SFGameBullet(const char * s){
    
    gameSprite = new CCSprite();
    if (gameSprite && gameSprite->initWithFile(s)) {
        state =0;
        gameSprite->autorelease();
        return;
    }
    CC_SAFE_DELETE(gameSprite);
}

void SFGameBullet::tick(){
    
    switch (type) {
        case 0:
            switch (state) {
                case 0:
                {
                    CCPoint pp = gameSprite->getPosition();
                    gameSprite->setPosition(ccp(pp.x+3,pp.y));
                }
                    break;
                    
                default:
                    break;
            }
            break;
        case 1:
            switch (state) {
                case 0:
                {
                    CCPoint pp = gameSprite->getPosition();
                    gameSprite->setPosition(ccp(pp.x-3,pp.y));
                }
                    break;
                    
                default:
                    break;
            }
            
        default:
            break;
    }
}

void SFGameBullet::setType(int inType){
    type = inType;
}

int SFGameBullet::getType(){
    return type;
}

void SFGameBullet::setPosition(CCPoint inPoint){
    
    gameSprite->setPosition(inPoint);
    
}

CCMotionStreak * SFGameBullet::getStreak(){
    
    return streak;
}

bool SFGameBullet::collision(SFGamePlayer * play){
    return false;
}

CCSize SFGameBullet::getSize(){
    
    return gameSprite->getContentSize();
    
}

