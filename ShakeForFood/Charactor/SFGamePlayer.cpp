//
//  SFGamePlayer.cpp
//  ShakeForFood
//
//  Created by Yang David on 5/17/13.
//
//

#include "SFGamePlayer.h"


SFGamePlayer::SFGamePlayer(void){
    
}

SFGamePlayer::~SFGamePlayer(void){
    
}

SFGamePlayer::SFGamePlayer(const char * gameName){

    gameSprite = new CCSprite();
    
    if (gameSprite && gameSprite->initWithFile(gameName)) {
        speed = 3.0;
        gameSprite->autorelease();
        return;
    }
    CC_SAFE_DELETE(gameSprite);
    
}

void SFGamePlayer::tick(){
    
}

float SFGamePlayer::getSpeed(){
    return speed;
}

void SFGamePlayer::setPosition(CCPoint inPoint){
    gameSprite->setPosition(inPoint);
}

bool SFGamePlayer::isCollision(SFGameSprite * collisionSprite){
    
    CCSize gameSize = gameSprite->getContentSize();
    CCSize collisionSize = collisionSprite->getSize();
    
    CCPoint gamePoint = gameSprite->getPosition();
    CCPoint collisionPoint = collisionSprite->getSprite()->getPosition();
    
    if ( ( abs((int)gamePoint.x - (int)collisionPoint.x) <= gameSize.width/2 + collisionSize.width/2 ) && ( abs((int)gamePoint.y - (int)collisionPoint.y)<= gameSize.height/2+collisionSize.height/2 )) {
        
        return true;
    }
	return false;
    
}

bool SFGamePlayer::collision(){
    
    return false;
}

CCSize SFGamePlayer::getSize(){
    
    return gameSprite->getContentSize();
    
}

