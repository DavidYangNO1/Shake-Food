//
//  SFGameEnemy.cpp
//  ShakeForFood
//
//  Created by Yang David on 5/17/13.
//
//

#include "SFGameEnemy.h"
#include "SFGamePlayer.h"
#include "SFGameBullet.h"
#include <cmath>

SFGameEnemy::SFGameEnemy(void){
    
}

SFGameEnemy::~SFGameEnemy(void){
    
}

SFGameEnemy::SFGameEnemy(const char * s ){
    
    gameSprite = new CCSprite();
    if (gameSprite && gameSprite->initWithFile(s)) {
        chooseFlyType();
        state = 0;
        gameSprite->autorelease();
        return;
    }
    CC_SAFE_DELETE(gameSprite);
}

void SFGameEnemy::setDead(){
    
    gameSprite->stopAllActions();
    
    gameSprite->setIsVisible(false);
    
    state =-1;
}

void SFGameEnemy::chooseFlyType(){
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCSize psize = gameSprite->getContentSize();
    
    float minHeight = 90 + psize.height /2;
    float maxHeight = size.height - psize.height/2;
    float x = size.width + psize.width/2;
    float y = CCRANDOM_0_1() * (maxHeight-minHeight) + minHeight;
    gameSprite->setPosition(ccp(x, y));
    
    CCActionInterval * actionTo = CCMoveBy::actionWithDuration(2, ccp(-(size.width+gameSprite->getContentSize().width), 0));
    gameSprite->runAction(CCSequence::actions(actionTo,NULL));
    
}

void SFGameEnemy::restart(){
    
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    int x = size.width;
    int y = CCRANDOM_0_1()*(float)size.height;
    gameSprite->setPosition(ccp(x,y));
    gameSprite->setIsVisible(true);
    chooseFlyType();
    state =0;
}

void SFGameEnemy::tick(){
    
}

void SFGameEnemy::setPosition(CCPoint point){
    gameSprite->setPosition(point);
}

CCMotionStreak * SFGameEnemy::getStreak(){
    return streak;
}

bool SFGameEnemy::isCollision(SFGameSprite * collisionSprite){
    
    CCSize gameSize = gameSprite->getContentSize();
    CCSize collisionSize = collisionSprite->getSize();
    CCPoint gamePoint = gameSprite->getPosition();
    CCPoint collisionPoint = collisionSprite->getSprite()->getPosition();
    if (abs(gamePoint.x - collisionPoint.x)<= (gameSize.width/2 + collisionSize.width/2) && abs(gamePoint.y - collisionPoint.y) <= (gameSize.height/2 + collisionSize.height/2)) {
        return true;
    }
    return false;
}


bool SFGameEnemy::collision(SFGamePlayer * collisionPlayer){
    
    CCSize ownsize = gameSprite->getContentSize();
	CCSize othersize = collisionPlayer->getSize();
    
	CCPoint ownp = gameSprite->getPosition();
	CCPoint otherp = (collisionPlayer->getSprite())->getPosition();
    
	if(abs(ownp.x - otherp.x) <= ownsize.width/2 + othersize.width/2 && abs(ownp.y - otherp.y) <= ownsize.height/2 + othersize.height/2){
        
		if(ownp.y + ownsize.height/2 >= otherp.y - othersize.height/2 && ownp.y - ownsize.height/2 <= otherp.y - othersize.height/2){
			otherp.y = ownp.y + ownsize.height/2 + othersize.height/2;
			collisionPlayer->setPosition(ccp(otherp.x,otherp.y));
			return true;
	    }
		if(ownp.y + ownsize.height/2 >= otherp.y + othersize.height/2 && ownp.y - ownsize.height/2 <= otherp.y + othersize.height/2){
            otherp.y = ownp.y - ownsize.height/2 - othersize.height/2;
            collisionPlayer->setPosition(ccp(otherp.x,otherp.y));
            return true;
	    }
		if(ownp.x + ownsize.width/2 >= otherp.x - othersize.width/2 && ownp.x - ownsize.width/2 <= otherp.x - othersize.width/2){
			otherp.x = ownp.x + ownsize.width/2 + othersize.width/2;
			collisionPlayer->setPosition(ccp(otherp.x,otherp.y));
			return true;
	    }
		if(ownp.x + ownsize.width/2 >= otherp.x + othersize.width/2 && ownp.x - ownsize.width/2 <= otherp.x + othersize.width/2){
            otherp.x = ownp.x - ownsize.width/2 - othersize.width/2;
            collisionPlayer->setPosition(ccp(otherp.x,otherp.y));
            return true;
	    }
	}
	return false;
    
}

bool SFGameEnemy::collisionWithBullet(SFGameBullet * testsprite){
    
    CCSize ownsize = gameSprite->getContentSize();
	CCSize othersize = testsprite->getSize();
	CCPoint ownp = gameSprite->getPosition();
	CCPoint otherp = (testsprite->getSprite())->getPosition();
	if(abs(ownp.x - otherp.x) <= ownsize.width/2 + othersize.width/2 && abs(ownp.y - otherp.y) <= ownsize.height/2 + othersize.height/2){
		return true;
	}
	return false;
}

CCSize SFGameEnemy::getSize(){
    
    return gameSprite->getContentSize();
    
}

